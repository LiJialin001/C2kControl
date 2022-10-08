/*
 * sys_adc.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#include "sys_adc.h"


// 初始化 ADC-A
void InitAdca(void) {
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);     // Reset ADC

//  配置ADC-A基址寄存器
    ADC_disableConverter(ADCA_BASE);                                     // 关闭ADC电源进行配置
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);  // VREF内部3.3V
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);                        // ADC时钟预分频器=CPUCLK/4
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);         // 在采集结束时INT脉冲生成

//  SOC0配置-使用ePWM1 ADCSOCA触发；转换通道ADCINA0；采集窗口=8个周期
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 8);

//  无ADC中断触发SOC0（TRIGSEL由SOC决定，而非ADCINT1或ADCINT2）
    ADC_setInterruptSOCTrigger(ADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);

    ADC_setSOCPriority(ADCA_BASE, ADC_PRI_ALL_ROUND_ROBIN);             // 以循环模式处理的所有SOC

//  ADCA1中断配置
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);                       // 中断脉冲，不考虑标志状态
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);        // EOC0触发中断
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);                            // 启用ADC中的中断

//  启用ADCA1中断
    Interrupt_register(INT_ADCA1, &adcA1ISR);    // 重新映射ADCA1中断信号以调用ISR功能
//  Interrupt_enable(INT_ADCA1);                 // 在PIE组1中启用ADCA1，并在IER中启用INT1以启用PIE组1

//  Finish up
    ADC_enableConverter(ADCA_BASE);             // Power up the ADC
    DEVICE_DELAY_US(1000);                      // Wait 1 ms after power-up before using the ADC
}
