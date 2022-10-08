/*
 * sys_adc.h
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_ADC_H_
#define APP_INC_SYS_ADC_H_

#include "driverlib.h"
#include "device.h"


// ��������
#define ADC_BUF_LEN         50              // ADC����������
#define ADC_SAMPLE_PERIOD   1999            // 1999 = 50 kHz sampling w/ 100 MHz ePWM clock


// ȫ�ֱ�������
extern uint16_t AdcBuf[ADC_BUF_LEN];
extern uint16_t AdcBufFiltered[ADC_BUF_LEN];
extern uint16_t AdcBufRaw[2*ADC_BUF_LEN];

// ����ԭ��-ISR����
extern interrupt void adcA1ISR(void);             // 1.1 - ADCA �ж� 1


// ADC ��ʼ��
void InitAdca(void);

#endif /* APP_INC_SYS_ADC_H_ */
