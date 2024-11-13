#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "app_dbg.h"
#include "task_list.h"
#include "timer.h"

#include "giec_api_gpio.h"
#include "app_bsp.h"

q_msg_t gw_task_sys_mailbox;

static pthread_t pthread_btn_polling;

static void *thread_btn_polling(void *arg);

void *gw_task_sys_entry(void *) {
    ak_msg_t *msg = AK_MSG_NULL;
    wait_all_tasks_started();
    APP_DBG("[STARTED] gw_task_sys_entry\n");

    pthread_create(&pthread_btn_polling, NULL, thread_btn_polling, NULL);
    pthread_setname_np(pthread_btn_polling, "button task");
    while (1) {
        /* get messge */
        msg = ak_msg_rev(GW_TASK_SYS_ID);

        switch (msg->header->sig) {
            default:
                break;
        }

        /* free message */
        ak_msg_free(msg);
    }

    return (void *)0;
}

void *thread_btn_polling(void *arg) {
    (void)arg;
    APP_DBG("POLLING BUTTON \n");
	appBtnInit();
    while (1) {
        // appBtnPolling();
        usleep(10000);
    }

    return (void *)0;
}