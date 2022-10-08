/*
 * sys.h
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_H_
#define APP_INC_SYS_H_

// 常量定义
#define FILTER_LEN          5               // 滤波长度
#define SINE_PTS            25              // 正弦波中采样点数

#if !defined(__TMS320C28XX_CLA__)
    #include <string.h>
#endif

#if !defined(__TMS320C28XX_CLA__)
    #include "driverlib.h"
    #include "device.h"
#else
    #include "hw_types.h"
#endif



// 全局变量引用
extern float32_t xDelay[FILTER_LEN];
extern float32_t coeffs[FILTER_LEN];
extern uint16_t ClaFilteredOutput;
extern uint16_t DacOffset;
extern uint16_t DacOutput;
extern uint32_t PwmDuty;
extern uint32_t PwmPeriod;
extern uint16_t DEBUG_TOGGLE;
extern uint16_t SINE_ENABLE;
extern uint16_t PWM_MODULATE;
extern int QuadratureTable[SINE_PTS];



// 函数原型-ISR声明
extern interrupt void wakeISR(void);              // 1.8 - Watchdog Wake Interrupt
extern interrupt void dmaCh1ISR(void);            // 7.1 - DMA Channel 1 Interrupt


// 链接器命令文件中定义的全局符号
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;



// 延时内联函数
static inline void Delay_us(uint16_t us) {
    DEVICE_DELAY_US(us);
}
static inline void Delay_ms(uint16_t ms) {
    uint16_t i = 10;
    for(; i>0; i--)
        Delay_us(1000);
}



// Timer 相关
void initCPUTimers(void);
void configCPUTimer(uint32_t cpuTimer, float freq, float period);


// 看门狗
void InitWatchdog(void);



#endif /* APP_INC_SYS_H_ */
