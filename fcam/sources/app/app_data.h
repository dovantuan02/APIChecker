#ifndef __APP_DATA_H__
#define __APP_DATA_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "giec_api_video.h"
#include "SocketHelper.h"

enum GROUPSOCK_ENUMERATES {
	GROUPSOCK_VIDEO_CHANNEL0 = 0,
	GROUPSOCK_VIDEO_CHANNEL1,
	GROUPSOCK_AUDIO_CHANNEL0,
};

extern GroupsockHelp_t groupsockHelpers[3];

extern void video_main_handler(const fca_video_in_frame_t *video_frame);
extern void video_sub_handler(const fca_video_in_frame_t *video_frame);

#ifdef __cplusplus
}
#endif

#endif /* __APP_DATA_H__ */
