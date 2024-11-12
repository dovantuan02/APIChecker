#ifndef __APP_BSP_H
#define __APP_BSP_H

#include "fca_button.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*
 *  DECLARE: Common definitions
 *  Note:
 *----------------------------------------------------------------------------*/
#define BUTTON_MODE_ID (0x01)
#define BUTTON_UP_ID   (0x02)
#define BUTTON_DOWN_ID (0x03)

/* Typedef -------------------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/
extern bool isButtonLocked;

/* Function prototypes -------------------------------------------------------*/
extern void appBtnInit();
extern void appBtnPolling(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_BSP_H */
