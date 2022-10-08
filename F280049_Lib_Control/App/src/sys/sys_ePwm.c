/*
 * sys_ePwm.c
 *
 *  Created on: 2022��10��7��
 *      Author: Lijialin001
 */

#include "sys_ePwm.h"



void InitEPwm(void) {
    // ����ePWMģ���ʱ�ӣ�����ͬ������ePWMģ��
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


//---------------------------------------------------------------------
// ����ePWM2��50 kHz���ʴ���ADC SOCA
//---------------------------------------------------------------------
//  SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM2);    // ���� ePWM2
//
//  EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);             // ���ö�ʱ��
//  EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);   // TBCLK = EPWMCLK
//  EPWM_setSyncOutPulseMode(EPWM2_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);                 // ����ͬ�����
//  EPWM_setEmulationMode(EPWM2_BASE, EPWM_EMULATION_FREE_RUN);                         // �������
//
//  EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);                        // �嶨ʱ������
//  EPWM_setTimeBasePeriod(EPWM2_BASE, ADC_SAMPLE_PERIOD);          // ���ö�ʱ������
//  EPWM_setPhaseShift(EPWM2_BASE, 0U);                             // ��������
//  EPWM_disablePhaseShiftLoad(EPWM2_BASE);                         // ��������
//
//  EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);
//  EPWM_setADCTriggerSource(EPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
//  EPWM_setADCTriggerEventPrescale(EPWM2_BASE, EPWM_SOC_A, 1);
//
//  EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);


//---------------------------------------------------------------------
//  ΪEPWM1A�����ϵ�250kHz�Գ�PWM����ePWM1
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

    // ����pwmռ�ձ�
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);

    // �㸺�ػ�PRDƥ��
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);


    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

//  ��������
//    EPWM_setDeadBandDelayMode(EPWM1_BASE, EPWM_DB_RED, true);

//  ���á�PWMն������������բ����ֱ���Ƚ϶���
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

//  ���ü�ʱ��ģʽ
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);


//---------------------------------------------------------------------
//  ����ePWMģ���ʱ��
// Note: ��Ӧ������������ePWMģ�����ɣ���ȷ��ePWM֮���ͬ����
//---------------------------------------------------------------------
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);   // ����TBCLK��ePWMģ��

}
