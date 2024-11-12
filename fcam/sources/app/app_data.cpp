#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <openssl/sha.h>

#include "ak.h"
#include "app_data.h"
#include "giec_api_video.h"

GroupsockHelp_t groupsockHelpers[3] = {
	{-1, 1111},
	{-1, 2222},
	{-1, 3333},
};


void video_main_handler(const fca_video_in_frame_t *video_frame) {
    SocketHelperDatagramWrite(groupsockHelpers[GROUPSOCK_VIDEO_CHANNEL0], video_frame->data, video_frame->size);
	return;
}   

void video_sub_handler(const fca_video_in_frame_t *video_frame) {
	SocketHelperDatagramWrite(groupsockHelpers[GROUPSOCK_VIDEO_CHANNEL1], video_frame->data, video_frame->size);
	return;
}