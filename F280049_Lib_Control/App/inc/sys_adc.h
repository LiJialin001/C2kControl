/*
 * sys_adc.h
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_ADC_H_
#define APP_INC_SYS_ADC_H_

#include "driverlib.h"
#include "device.h"


// 常量定义
#define ADC_BUF_LEN         50              // ADC缓冲区长度
#define ADC_SAMPLE_PERIOD   1999            // 1999 = 50 kHz sampling w/ 100 MHz ePWM clock


// 全局变量引用
extern uint16_t AdcBuf[ADC_BUF_LEN];
extern uint16_t AdcBufFiltered[ADC_BUF_LEN];
extern uint16_t AdcBufRaw[2*ADC_BUF_LEN];

// 函数原型-ISR声明
extern interrupt void adcA1ISR(void);             // 1.1 - ADCA 中断 1


// ADC 初始化
void InitAdca(void);

#endif /* APP_INC_SYS_ADC_H_ */
