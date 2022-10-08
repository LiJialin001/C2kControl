/*
 * sys_ePwm.c
 *
 *  Created on: 2022年10月7日
 *      Author: Lijialin001
 */

#include "sys_ePwm.h"



void InitEPwm(void) {
    // 禁用ePWM模块的时钟，才能同步所有ePWM模块
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


//---------------------------------------------------------------------
// 配置ePWM2以50 kHz速率触发ADC SOCA
//---------------------------------------------------------------------
//  SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM2);    // 重置 ePWM2
//
//  EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);             // 禁用定时器
//  EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);   // TBCLK = EPWMCLK
//  EPWM_setSyncOutPulseMode(EPWM2_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);                 // 禁用同步输出
//  EPWM_setEmulationMode(EPWM2_BASE, EPWM_EMULATION_FREE_RUN);                         // 仿真输出
//
//  EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);                        // 清定时器计数
//  EPWM_setTimeBasePeriod(EPWM2_BASE, ADC_SAMPLE_PERIOD);          // 设置定时器周期
//  EPWM_setPhaseShift(EPWM2_BASE, 0U);                             // 设置相移
//  EPWM_disablePhaseShiftLoad(EPWM2_BASE);                         // 禁用相移
//
//  EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);
//  EPWM_setADCTriggerSource(EPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
//  EPWM_setADCTriggerEventPrescale(EPWM2_BASE, EPWM_SOC_A, 1);
//
//  EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);


//---------------------------------------------------------------------
//  为EPWM1A引脚上的250kHz对称PWM配置ePWM1
//---------------------------------------------------------------------
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM1);

    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setSyncOutPulseMode(EPWM1_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);

    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
    EPWM_setTimeBasePeriod(EPWM1_BASE, PWM_HALF_PERIOD);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);

    // 设置pwm占空比
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);

    // 零负载或PRD匹配
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);


    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

//  启用死区
//    EPWM_setDeadBandDelayMode(EPWM1_BASE, EPWM_DB_RED, true);

//  禁用、PWM斩波器和所有跳闸区和直流比较动作
    EPWM_setDeadBandDelayMode(EPWM1_BASE, EPWM_DB_RED, false);
    EPWM_disableChopper(EPWM1_BASE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_DISABLE);
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DC_DISABLED);
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_A2, EPWM_TZ_EVENT_DC_DISABLED);
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DC_DISABLED);
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_B2, EPWM_TZ_EVENT_DC_DISABLED);

//  设置计时器模式
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);


//---------------------------------------------------------------------
//  启用ePWM模块的时钟
// Note: 这应该在配置所有ePWM模块后完成，以确保ePWM之间的同步。
//---------------------------------------------------------------------
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);   // 启用TBCLK至ePWM模块

}
