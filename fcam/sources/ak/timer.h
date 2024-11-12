//=============================================================================
//    A C T I V E    K E R N E L    L I N U X
//=============================================================================
// Project   :  Event driven
// Author    :  ThanNT
// Date      :  12/01/2017
// Brief     :  Timer
//=============================================================================
#ifndef __TIMER_H
#define __TIMER_H

#include "message.h"

/*----------------------------------------------------------------------------*
 *  DECLARE: Common definitions
 *  Note:
 *----------------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/
extern q_msg_t timerMailbox;

/* Function prototypes -------------------------------------------------------*/
extern void *TaskTimerEntry(void *);

#endif
