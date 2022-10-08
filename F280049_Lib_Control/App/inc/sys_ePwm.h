/*
 * sys_ePwm.h
 *
 *  Created on: 2022年10月7日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_EPWM_H_
#define APP_INC_SYS_EPWM_H_

#include "driverlib.h"
#include "device.h"


// 常量定义
#define PWM_HALF_PERIOD     200             // 250kHz 的半周期
#define PWM_DUTY_CYCLE      50              // 25%占空比
#define PWM_MIN_DUTY        20              // PWM调制的10%占空比
#define PWM_MAX_DUTY        180             // PWM调制的90%占空比
#define PWM_STEP            2               // PWM调制的增量



// 函数声明
void InitEPwm(void);


#endif /* APP_INC_SYS_EPWM_H_ */
