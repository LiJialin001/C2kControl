/*
 * sys_eCap.h
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_ECAP_H_
#define APP_INC_SYS_ECAP_H_

#include "driverlib.h"
#include "device.h"

// ����ԭ��-ISR����
extern interrupt void ecap1ISR(void);             // 4.1 - eCAP1 Interrupt

// ��������
void InitECap(void);


#endif /* APP_INC_SYS_ECAP_H_ */
