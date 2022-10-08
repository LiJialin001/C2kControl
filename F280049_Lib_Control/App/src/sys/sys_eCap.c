/*
 * sys_eCap.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */
#include "sys_eCap.h"


void InitECap(void) {
//  配置eCAP1单元以进行捕获

    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);        // Reset eCAP1

//  禁用所有捕获中断并清除所有捕获标志
    ECAP_disableInterrupt(ECAP1_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP1_BASE,
                        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE));

    // 禁用CAP1-CAP4寄存器加载
    ECAP_disableTimeStampCapture(ECAP1_BASE);
    // 停止计数器
    ECAP_stopCounter(ECAP1_BASE);
    // 选择Input X-BAR INPUT7作为eCAP1的源
    ECAP_selectECAPInput(ECAP1_BASE, ECAP_INPUT_INPUTXBAR7);

//  配置eCAP1  启用捕获模式
    ECAP_enableCaptureMode(ECAP1_BASE);
    // 连续模式，4次捕获后换行
    ECAP_setCaptureMode(ECAP1_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);

    // 在上升沿捕获事件1
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_RISING_EDGE);
    // 在下降边缘捕获事件2
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_FALLING_EDGE);

    // 捕获事件1时不重置计数器（绝对时间戳）
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);

    // 捕获事件3中断已启用
    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);

//  启用eCAP1中断  重新映射ECAP1中断信号以调用ISR功能
    Interrupt_register(INT_ECAP1, &ecap1ISR);
    // 在PIE组4中启用ECAP1，并在IER中启用INT4以启用PIE组
    Interrupt_enable(INT_ECAP1);


    ECAP_enableTimeStampCapture(ECAP1_BASE);                // 启用CAP1-CAP4寄存器加载
    ECAP_startCounter(ECAP1_BASE);                          // 启动计数

}
