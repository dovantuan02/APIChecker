#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "ak.h"
#include "timer.h"
#include "app.h"
#include "app_dbg.h"
#include "app_data.h"
#include "task_list.h"

q_msg_t gw_task_network_mailbox;

void *gw_task_network_entry(void *) {
	ak_msg_t *msg = AK_MSG_NULL;
	wait_all_tasks_started();
	APP_DBG_NET("[STARTED] gw_task_network_entry\n");

	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_NETWORK_ID);

		switch (msg->header->sig) {
		case GW_NET_WATCHDOG_PING_REQ: {
			task_post_pure_msg(GW_TASK_NETWORK_ID, GW_TASK_SYS_ID, GW_SYS_WATCH_DOG_PING_NEXT_TASK_RES);
		} break;

		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}
	return (void *)0;
}