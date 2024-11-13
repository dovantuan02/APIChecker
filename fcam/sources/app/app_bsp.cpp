#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ak.h"
#include "message.h"
#include "timer.h"

#include "fca_button.h"

#include "app_data.h"
#include "app_bsp.h"
#include "app_dbg.h"
#include "sys_dbg.h"
#include "task_list.h"
#include "app.h"

#define TAG "appBsp"

/* Private variables ---------------------------------------------------------*/
static button_t button;

/* Private function prototypes -----------------------------------------------*/
static void btnCallback(void *);

/* Function implementation ---------------------------------------------------*/
void appBtnInit() {
	fca_buttonInit(&button, 10, BUTTON_MODE_ID, readButton, btnCallback);
	fca_buttonEnable(&button);
}

void appBtnPolling() {
	fca_buttonTimerPolling(&button);
}

/*----------------------------------------------------------------------------*/
void btnCallback(void *b) {
	button_t *me_b = (button_t *)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		APP_DBG("BUTTON_SW_STATE_PRESSED\n");
	} break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		APP_DBG("BUTTON_SW_STATE_LONG_PRESSED\n");
		// task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_RESET_WIFI_REQ);
	} break;

	case BUTTON_SW_STATE_RELEASED: {
		APP_DBG("BUTTON_SW_STATE_RELEASED\n");
	} break;

	default:
		break;
	}
}
