#include "timer.h"

#include "task_list.h"

ak_task_t task_list[] = {
	/* SYSTEM TASKS */
	{	AK_TASK_TIMER_ID,	   	TASK_PRI_LEVEL_1, 	TaskTimerEntry,			  	&timerMailbox,			  		"timer service"	 	},

 /* APP TASKS */
 #ifdef TERMINAL
	{	GW_TASK_IF_CONSOLE_ID, 	TASK_PRI_LEVEL_8, 	gw_task_if_console_entry, 	&gw_task_if_console_mailbox, 	"terminal gate"		},
	{	GW_TASK_CONSOLE_ID,	 	TASK_PRI_LEVEL_8, 	gw_task_console_entry,	  	&gw_task_console_mailbox,		"console task"		},
#endif
	{	GW_TASK_CLOUD_ID,	   	TASK_PRI_LEVEL_1, 	gw_task_cloud_entry,	  	&gw_task_cloud_mailbox,	  		"cloud task"	  	},
	{	GW_TASK_SYS_ID,		 	TASK_PRI_LEVEL_1, 	gw_task_sys_entry,		  	&gw_task_sys_mailbox,			"sys task"		  	},
	{	GW_TASK_NETWORK_ID,	 	TASK_PRI_LEVEL_1, 	gw_task_network_entry,	  	&gw_task_network_mailbox,		"network task"	  	},
	{	GW_TASK_FW_ID,			TASK_PRI_LEVEL_1, 	gw_task_fw_entry,			&gw_task_fw_mailbox,		 	"fw task"		  	},
	{	GW_TASK_GPIO_ID,		TASK_PRI_LEVEL_1, 	gw_task_gpio_entry,			&gw_task_gpio_mailbox,		 	"gpio task"		  	},
	{	GW_TASK_IRCUT_ID,		TASK_PRI_LEVEL_1, 	gw_task_ircut_entry,		&gw_task_ircut_mailbox,		 	"ircut task"		  	},
	{	GW_TASK_VIDEO_ID,		TASK_PRI_LEVEL_1, 	gw_task_video_entry,		&gw_task_video_mailbox,		 	"video task"		  	}
};
