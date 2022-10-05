/*
 * sys.h
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_H_
#define APP_INC_SYS_H_

#include "device.h"
#include "driverlib.h"

// 延时内联函数
static inline void Delay_us(uint16_t us) {
    DEVICE_DELAY_US(us);
}
static inline void Delay_ms(uint16_t ms) {
    uint16_t i = 10;
    for(; i>0; i--)
        Delay_us(1000);
}


//Timer相关
void initCPUTimers(void);
void configCPUTimer(uint32_t cpuTimer, float freq, float period);


#endif /* APP_INC_SYS_H_ */
