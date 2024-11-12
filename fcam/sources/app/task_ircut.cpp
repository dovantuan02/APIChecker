#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ak.h"
#include "timer.h"
#include "app.h"
#include "app_dbg.h"
#include "app_data.h"
#include "task_list.h"

q_msg_t gw_task_ircut_mailbox;

void *gw_task_ircut_entry(void *) {
	ak_msg_t *msg = AK_MSG_NULL;
	wait_all_tasks_started();
	APP_DBG("[STARTED] gw_task_ircut_entry\n");

	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_IRCUT_ID);

		switch (msg->header->sig) {
		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}

	return (void *)0;
}

