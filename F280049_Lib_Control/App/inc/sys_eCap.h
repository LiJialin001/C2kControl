/*
 * sys_eCap.h
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_ECAP_H_
#define APP_INC_SYS_ECAP_H_

#include "driverlib.h"
#include "device.h"

// 函数原型-ISR声明
extern interrupt void ecap1ISR(void);             // 4.1 - eCAP1 Interrupt

// 函数声明
void InitECap(void);


#endif /* APP_INC_SYS_ECAP_H_ */
