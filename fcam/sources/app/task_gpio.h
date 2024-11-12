#ifndef __TASK_GPIO_H__
#define __TASK_GPIO_H__

#include "message.h"

extern q_msg_t gw_task_gpio_mailbox;
extern void *gw_task_gpio_entry(void *);

#endif	  //__TASK_GPIO_H__