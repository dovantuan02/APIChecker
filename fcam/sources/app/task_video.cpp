#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "SocketHelper.h"
#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "app_dbg.h"
#include "giec_api_common.h"
#include "giec_api_video.h"
#include "task_list.h"
#include "timer.h"

q_msg_t gw_task_video_mailbox;

static void groupsockHelpersInit();

void *gw_task_video_entry(void *) {
    ak_msg_t *msg = AK_MSG_NULL;
    wait_all_tasks_started();
    APP_DBG("[STARTED] gw_task_video_entry\n");

    fca_video_in_config_t config_sub, config_main;
    fca_sdk_init();  // init sdk here
    fca_video_in_init();

    task_post_pure_msg(GW_TASK_VIDEO_ID, GW_VIDEO_INIT_REQ);
    groupsockHelpersInit();
    while (1) {
        /* get messge */
        msg = ak_msg_rev(GW_TASK_VIDEO_ID);

        switch (msg->header->sig) {
            case GW_VIDEO_INIT_REQ: {
                config_main.codec = FCA_CODEC_VIDEO_H265;
                config_main.width = 2304;
                config_main.height = 1296;
                config_main.fps = 13;
                config_main.encoding_mode = FCA_VIDEO_ENCODING_MODE_AVBR;
                config_main.gop = 40;
                config_main.bitrate_target = 2048;
                config_main.bitrate_max = 2048;
                config_main.max_qp = 50;
                config_main.min_qp = 20;

                config_sub.codec = FCA_CODEC_VIDEO_H264;
                config_sub.width = 1280;
                config_sub.height = 720;
                config_sub.fps = 13;
                config_sub.encoding_mode = FCA_VIDEO_ENCODING_MODE_CBR;
                config_sub.gop = 30;
                config_sub.bitrate_target = 1024;
                config_sub.bitrate_max = 1024;
                config_sub.max_qp = 50;
                config_sub.min_qp = 20;
                fca_video_in_set_config(0, &config_main);
                fca_video_in_set_config(1, &config_sub);

                fca_video_in_config_t config_sub_2;
                config_sub_2.codec = FCA_CODEC_VIDEO_H264;
                config_sub_2.width = 1280;  // Must be the same as sub
                config_sub_2.height = 720;  // Must be the same as sub
                config_sub_2.fps = 13;      // Must be the same as sub
                config_sub_2.encoding_mode = FCA_VIDEO_ENCODING_MODE_AVBR;
                config_sub_2.gop = 30;
                config_sub_2.bitrate_target = 512;
                config_sub_2.bitrate_max = 512;
                config_sub_2.max_qp = 50;
                config_sub_2.min_qp = 25;
                fca_video_in_set_config(
                    2, &config_sub_2);  // Must set sub before set sub_2

                fca_video_in_config_t tmp;
                // fca_video_in_get_config(0, )
                timer_set(GW_TASK_VIDEO_ID, GW_VIDEO_START_REQ, 100,
                          TIMER_ONE_SHOT);
            } break;

            case GW_VIDEO_START_REQ: {
                fca_video_in_start_callback(0, video_main_handler);
                fca_video_in_start_callback(1, video_sub_handler);
            } break;

            case GW_VIDEO_STOP_REQ: {
                for (uint8_t id = 0; id < 3; ++id) {
                    SocketHelperClose(groupsockHelpers[id]);
                }

            } break;

            default:
                break;
        }

        /* free message */
        ak_msg_free(msg);
    }

    return (void *)0;
}

void groupsockHelpersInit() {
    for (uint8_t id = 0; id < 3; ++id) {
        groupsockHelpers[id].fSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (groupsockHelpers[id].fSocket < 0) {
            APP_DBG("Can't open datagram socket on port %d\r\n",
                    groupsockHelpers[id].fPort);
            exit(EXIT_FAILURE);
        }
    }
}

void printEncodeConfig(fca_video_in_config_t extra_video,
                       fca_video_in_config_t main_video) {
    APP_DBG(
        "[VIDEO] --------------------- Main channel ---------------------\n");

    APP_DBG("[VIDEO] Compression: %d\n", main_video.codec);
    APP_DBG("[VIDEO] Resolution: %d x %d \n", main_video.width,
            main_video.height);
    APP_DBG("[VIDEO] FPS: %d\n", main_video.fps);
    APP_DBG("[VIDEO] Encode Mode: %d\n", main_video.encoding_mode);
    APP_DBG("[VIDEO] GOP: %d\n", main_video.gop);
    APP_DBG("[VIDEO] BitRate: target [%d] - max [%d] \n",
            main_video.bitrate_target, main_video.bitrate_max);
    APP_DBG("[VIDEO] Quality: (%d -> %d)\n", main_video.min_qp,
            main_video.max_qp);

    APP_DBG(
        "[VIDEO] --------------------- Sub channel ---------------------\n");
    APP_DBG("[VIDEO] Compression: %d\n", extra_video.codec);
    APP_DBG("[VIDEO] Resolution: %d x %d \n", extra_video.width,
            extra_video.height);
    APP_DBG("[VIDEO] FPS: %d\n", extra_video.fps);
    APP_DBG("[VIDEO] Encode Mode: %d\n", extra_video.encoding_mode);
    APP_DBG("[VIDEO] GOP: %d\n", extra_video.gop);
    APP_DBG("[VIDEO] BitRate: target [%d] - max [%d] \n",
            extra_video.bitrate_target, extra_video.bitrate_max);
    APP_DBG("[VIDEO] Min:%d - Max:%d \n", extra_video.min_qp,
            extra_video.max_qp);
}