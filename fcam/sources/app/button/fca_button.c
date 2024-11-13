#include <stdio.h>
#include <stdint.h>

#include "fca_button.h"
#include "app_dbg.h"
#include "giec_api_gpio.h"

struct rts_gpio *rts_gpio = NULL;

uint8_t fca_buttonInit(button_t *button, uint32_t u, uint8_t id, pf_button_read read, pf_button_callback callback) {
	button->enable	= BUTTON_DISABLE;
	button->id		= id;
	button->counter = 0;
	button->unit	= u;
	button->state	= BUTTON_SW_STATE_RELEASED;

	button->read	 = read;
	button->callback = callback;

	if (!button->read) {
		return BUTTON_DRIVER_NG;
	}

	if (!button->callback) {
		return BUTTON_DRIVER_NG;
	}
	GIEC_GPIO_KEY_CB_PARAM key_cfg = {
		.key_reset_longpress_cb_func = NULL,
		.key_reset_shortpress_cb_func = NULL,
		.key_call_longpress_cb_func = NULL,
		.key_call_shortpress_cb_func = NULL,
		.key_longpress_ms = 0,
		.key_shortpress_ms = 0
	};
	giec_gpio_key_init(&key_cfg);
	return BUTTON_DRIVER_OK;
}

void fca_buttonEnable(button_t *button) {
	button->enable = BUTTON_ENABLE;
}

void fca_buttonDisable(button_t *button) {
	button->enable = BUTTON_DISABLE;
}

void fca_buttonTimerPolling(button_t *button) {
	uint8_t hw_button_state;
	if (button->enable == BUTTON_ENABLE) {
		hw_button_state = button->read();

		/* hard button pressed */
		if (hw_button_state == FCA_BTN_STATUS_PRESS) {
			if (button->counter_enable == BUTTON_ENABLE) {
				/* increase button counter */
				button->counter += button->unit;

				/* check long press */
				if (button->counter == BUTTON_LONG_PRESS_TIME && button->state != BUTTON_SW_STATE_LONG_PRESSED) {
					button->enable = BUTTON_DISABLE;
					button->state  = BUTTON_SW_STATE_LONG_PRESSED;
					button->callback(button);
					button->state  = BUTTON_SW_STATE_PRESSED;
					button->enable = BUTTON_ENABLE;
				}
				/* check short press */
				else if (button->counter >= BUTTON_SHORT_PRESS_MIN_TIME && button->state != BUTTON_SW_STATE_PRESSED) {
					button->enable = BUTTON_DISABLE;
					button->state  = BUTTON_SW_STATE_PRESSED;
					button->callback(button);
					button->enable = BUTTON_ENABLE;
				}
			}
		}
		/* hard button released */
		else {
			button->state = BUTTON_SW_STATE_RELEASED;

			/* check released */
			if (button->counter > BUTTON_SHORT_PRESS_MIN_TIME) {
				button->enable = BUTTON_DISABLE;
				button->callback(button);
			}

			/* reset button */
			button->counter		   = 0;
			button->counter_enable = BUTTON_ENABLE;
			button->enable		   = BUTTON_ENABLE;
		}
	}
}

uint8_t readButton() {
	FCA_BTN_STATUS status;
	fca_get_button_status(FCA_BTN_RESET, &status);
	return status;
}
