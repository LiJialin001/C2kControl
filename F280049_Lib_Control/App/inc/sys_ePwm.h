/*
 * sys_ePwm.h
 *
 *  Created on: 2022��10��7��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_EPWM_H_
#define APP_INC_SYS_EPWM_H_

#include "driverlib.h"
#include "device.h"


// ��������
#define PWM_HALF_PERIOD     200             // 250kHz �İ�����
#define PWM_DUTY_CYCLE      50              // 25%ռ�ձ�
#define PWM_MIN_DUTY        20              // PWM���Ƶ�10%ռ�ձ�
#define PWM_MAX_DUTY        180             // PWM���Ƶ�90%ռ�ձ�
#define PWM_STEP            2               // PWM���Ƶ�����



// ��������
void InitEPwm(void);


#endif /* APP_INC_SYS_EPWM_H_ */
