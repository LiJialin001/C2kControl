/*
 * sys_adc.c
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#include "sys_adc.h"


// ��ʼ�� ADC-A
void InitAdca(void) {
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);     // Reset ADC

//  ����ADC-A��ַ�Ĵ���
    ADC_disableConverter(ADCA_BASE);                                     // �ر�ADC��Դ��������
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);  // VREF�ڲ�3.3V
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);                        // ADCʱ��Ԥ��Ƶ��=CPUCLK/4
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);         // �ڲɼ�����ʱINT��������

//  SOC0����-ʹ��ePWM1 ADCSOCA������ת��ͨ��ADCINA0���ɼ�����=8������
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 8);

//  ��ADC�жϴ���SOC0��TRIGSEL��SOC����������ADCINT1��ADCINT2��
    ADC_setInterruptSOCTrigger(ADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);

    ADC_setSOCPriority(ADCA_BASE, ADC_PRI_ALL_ROUND_ROBIN);             // ��ѭ��ģʽ���������SOC

//  ADCA1�ж�����
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);                       // �ж����壬�����Ǳ�־״̬
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);        // EOC0�����ж�
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);                            // ����ADC�е��ж�

//  ����ADCA1�ж�
    Interrupt_register(INT_ADCA1, &adcA1ISR);    // ����ӳ��ADCA1�ж��ź��Ե���ISR����
//  Interrupt_enable(INT_ADCA1);                 // ��PIE��1������ADCA1������IER������INT1������PIE��1

//  Finish up
    ADC_enableConverter(ADCA_BASE);             // Power up the ADC
    DEVICE_DELAY_US(1000);                      // Wait 1 ms after power-up before using the ADC
}
