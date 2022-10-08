/*
 * sys_Init.h
 *
 *  Created on: 2022Äê10ÔÂ7ÈÕ
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_INIT_H_
#define APP_INC_SYS_INIT_H_

#include "device.h"
#include "driverlib.h"

#include "board.h"

#include "sys.h"
#include "sys_ePwm.h"
#include "sys_adc.h"
#include "sys_dac.h"
#include "sys_eCap.h"
#include "sys_cla.h"

void sys_per_init(void);
void sys_init(void);


#endif /* APP_INC_SYS_INIT_H_ */
