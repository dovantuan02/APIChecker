#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "ak.h"
#include "app.h"
#include "app_dbg.h"
#include "app_config.h"
#include "app_data.h"
#include "task_list.h"

#ifdef FEATURE_BBCRY
#include "bbc_dt.h"
#endif

void exit_app(int ret);

void task_init() {
	signal(SIGINT, exit_app);
	signal(SIGQUIT, exit_app);
	signal(SIGTERM, exit_app);
	signal(SIGKILL, exit_app);

	// create folder save jpeg motion tmp
	struct stat st;
	if (stat(FCA_JPEG_MOTION_TMP_PATH, &st) == -1) {
		mkdir(FCA_JPEG_MOTION_TMP_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	if (stat(FCA_MEDIA_MP4_PATH, &st) == -1) {
		mkdir(FCA_MEDIA_MP4_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	if (stat(FCA_SDCARD_CHECKSUM_FILE_PATH, &st) == -1) {
		mkdir(FCA_SDCARD_CHECKSUM_FILE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	if (stat(FCA_LOG_FILE_PATH, &st) == -1) {
		mkdir(FCA_LOG_FILE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
}

void exit_app(int ret) {
	APP_DBG("App exit \n");
	task_post_pure_msg(GW_TASK_VIDEO_ID, GW_VIDEO_STOP_REQ);
	exit(ret);
}
