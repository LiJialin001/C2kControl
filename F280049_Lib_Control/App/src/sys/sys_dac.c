/*
 * sys_dac.c
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#include "sys_dac.h"

void InitDacb(void) {
//  Note: DAC-B����Ϊʹ��VREFHI�ڲ���ѹ�ο���  Ϊ����ȷ��������������ADC-B��ADC-C�Ĳο�ģʽ��
//  ��ʹ��3.3V���ڲ���׼ʱ��Ӧ��DAC��������Ϊx2��
//  �����DAC-Bʹ���ⲿ���ã�ɾ�����������ADC_setVREF������DAC_setGainMode���������С�

    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-B VREF �ڲ� 3.3V
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-C VREF �ڲ� 3.3V
    DAC_setGainMode(DACB_BASE, DAC_GAIN_TWO);                               // DAC-B x2 gain

//  ��VREFHI����ΪDAC�ο���ѹ
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

//  ���ü���ģʽ
    DAC_setLoadMode(DACB_BASE, DAC_LOAD_SYSCLK);    // ������һ��SYSCLK����ʹ��DAC PWMSYNC�źţ�

//  ��DAC-B�������Ϊ�е�
    DAC_setShadowValue(DACB_BASE, 0x0800);          // DACVALS = bits 11-0, bits 15-12 reserved; 0x0800 = 2048

//  ����DAC-B���
    DAC_enableOutput(DACB_BASE);
    DEVICE_DELAY_US(10);                            // DAC�ϵ���ӳ�

}
