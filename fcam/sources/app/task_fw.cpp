#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>
#include <pthread.h>

#include "ak.h"
#include "timer.h"
#include "app.h"
#include "app_dbg.h"
#include "app_data.h"
#include "task_list.h"
#include "utils.h"
#include "ota.h"

q_msg_t gw_task_fw_mailbox;

void *gw_task_fw_entry(void *) {
	ak_msg_t *msg = AK_MSG_NULL;
	wait_all_tasks_started();

	APP_DBG_OTA("[STARTED] gw_task_upload_entry\n");

	bool isOtaRunning = false;

	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_FW_ID);

		switch (msg->header->sig) {
		case GW_FW_WATCHDOG_PING_REQ: {
			task_post_pure_msg(GW_TASK_FW_ID, GW_TASK_SYS_ID, GW_SYS_WATCH_DOG_PING_NEXT_TASK_RES);
		} break;

		case GW_FW_GET_URL_REQ: {
		} break;

		case GW_FW_DOWNLOAD_START_REQ: {
			APP_DBG_SIG("GW_OTA_DOWNLOAD_START\n");
		} break;

		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}

	return (void *)0;
}
