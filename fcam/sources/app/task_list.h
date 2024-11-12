#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "ak.h"
#include "message.h"
#include "app_data.h"

#ifdef TERMINAL
#include "if_console.h"
#endif

#include "task_console.h"
#include "task_cloud.h"
#include "task_sys.h"
#include "task_fw.h"
#include "task_network.h"
#include "task_video.h"
#include "task_gpio.h"
#include "task_ircut.h"

/** default if_des_type when get pool memory
 * this define MUST BE coresponding with app.
 */
#define AK_APP_TYPE_IF 101

enum {
	/* SYSTEM TASKS */
	AK_TASK_TIMER_ID,

	/* APP TASKS */
#ifdef TERMINAL
	GW_TASK_IF_CONSOLE_ID,
	GW_TASK_CONSOLE_ID,
#endif
	GW_TASK_CLOUD_ID,
	GW_TASK_SYS_ID,
	GW_TASK_NETWORK_ID,
	GW_TASK_FW_ID,
	GW_TASK_IRCUT_ID,
	GW_TASK_GPIO_ID,
	GW_TASK_VIDEO_ID,

	/* EOT task ID */
	AK_TASK_LIST_LEN,
};

extern ak_task_t task_list[];

#endif	  //__TASK_LIST_H__
