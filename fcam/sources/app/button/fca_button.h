#ifndef __FCA_BUTTON_H__
#define __FCA_BUTTON_H__

#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define BUTTON_DRIVER_OK (0x00)
#define BUTTON_DRIVER_NG (0x01)

#define BUTTON_SHORT_PRESS_MIN_TIME (20)   /* 20ms */
#define BUTTON_LONG_PRESS_TIME		(5000) /* 6s */

#define BUTTON_DISABLE (0x00)
#define BUTTON_ENABLE  (0x01)

/*
 * This define depend on hardware circuit.
 * Note: please change it for respective.
 */

#define BUTTON_SW_STATE_PRESSED		 (0x00)
#define BUTTON_SW_STATE_LONG_PRESSED (0x01)
#define BUTTON_SW_STATE_RELEASED	 (0x02)

typedef void (*pf_button_ctrl)();
typedef uint8_t (*pf_button_read)();
typedef void (*pf_button_callback)(void *);

typedef struct {
	uint8_t id;
	uint8_t enable;
	uint8_t state;
	uint8_t counter_enable;

	uint32_t counter;
	uint32_t unit;

	pf_button_ctrl init;
	pf_button_read read;

	pf_button_callback callback;
} button_t;

extern uint8_t fca_buttonInit(button_t *button, uint32_t u, uint8_t id, pf_button_read read, pf_button_callback callback);
extern void fca_buttonEnable(button_t *button);
extern void fca_buttonDisable(button_t *button);
extern void fca_buttonTimerPolling(button_t *button);
extern uint8_t readButton();

#ifdef __cplusplus
}
#endif
#endif /*__FCA_BUTTON_H__*/
