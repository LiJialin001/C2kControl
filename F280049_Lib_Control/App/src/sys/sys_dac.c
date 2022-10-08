/*
 * sys_dac.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#include "sys_dac.h"

void InitDacb(void) {
//  Note: DAC-B配置为使用VREFHI内部电压参考。  为了正确操作，必须配置ADC-B和ADC-C的参考模式。
//  当使用3.3V的内部基准时，应将DAC增益设置为x2。
//  如果对DAC-B使用外部引用，删除下面的两个ADC_setVREF（）和DAC_setGainMode（）代码行。

    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-B VREF 内部 3.3V
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-C VREF 内部 3.3V
    DAC_setGainMode(DACB_BASE, DAC_GAIN_TWO);                               // DAC-B x2 gain

//  将VREFHI设置为DAC参考电压
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

//  设置加载模式
    DAC_setLoadMode(DACB_BASE, DAC_LOAD_SYSCLK);    // 加载下一个SYSCLK（不使用DAC PWMSYNC信号）

//  将DAC-B输出设置为中档
    DAC_setShadowValue(DACB_BASE, 0x0800);          // DACVALS = bits 11-0, bits 15-12 reserved; 0x0800 = 2048

//  启用DAC-B输出
    DAC_enableOutput(DACB_BASE);
    DEVICE_DELAY_US(10);                            // DAC上电的延迟

}
