/*
 * sys.c
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 */

#include "sys.h"


// 将所选计时器初始化为“freq”和“period”参数指定的时间段。
// 频率输入为Hz，周期输入为us 配置后，开启计时器
// 例：configCPUTimer(uint32_t cpuTimer, DEVICE_STSCLK_FREQ, float period)；
void configCPUTimer(uint32_t cpuTimer, float freq, float period) {
    uint32_t temp;

    // 初始化定时器周期
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    // 设置分频
    CPUTimer_setPreScaler(cpuTimer, 0);

    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    CPUTimer_startTimer(cpuTimer);
}


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

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);   // 设置pwm占空比

    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);   // 零负载或PRD匹配


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



void InitWatchdog(void){
    // 配置看门狗
    SysCtl_setWatchdogPredivider(SYSCTL_WD_PREDIV_512);      // WDPRECLKDIV = INTOSC1/512
    SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_1);       // WDCLK=OSCCLK/512/1
    SysCtl_setWatchdogWindowValue(0);                        // 最小窗口阈值（禁用）

    // 设置看门狗模式
   // SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);

    // Enable / Disable
    SysCtl_disableWatchdog();
  //  SysCtl_enableWatchdog();

    // 启用看门狗中断
    Interrupt_register(INT_WAKE, &wakeISR);     // 重新映射看门狗唤醒中断信号以调用ISR
    Interrupt_enable(INT_WAKE);                 // Enable WAKEINT in PIE group 1 and enable INT1 in IER to enable PIE group 1

}


// 初始化 ADC-A
void InitAdca(void) {
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);     // Reset ADC

//  配置ADC-A基址寄存器
    ADC_disableConverter(ADCA_BASE);                                    // 关闭ADC电源进行配置
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);  // VREF内部3.3V
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);                        // ADC时钟预分频器=CPUCLK/4
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);        // INT pulse generation = end of conversion

//--- SOC0 configuration - Trigger using ePWM1-ADCSOCA; Convert channel ADCINA0; Acquisition window = 8 cycles
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 8);

//--- No ADC interrupt triggers SOC0 (TRIGSEL determined by SOC and not ADCINT1 or ADCINT2)
    ADC_setInterruptSOCTrigger(ADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);

    ADC_setSOCPriority(ADCA_BASE, ADC_PRI_ALL_ROUND_ROBIN);             // All SOCs handled in round-robin mode

//--- ADCA1 interrupt configuration
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);                       // Interrupt pulses regardless of flag state
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);        // EOC0 triggers the interrupt
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);                            // Enable the interrupt in the ADC

//--- Enable ADCA1 interrupt
    Interrupt_register(INT_ADCA1, &adcA1ISR);    // Re-map ADCA1 interrupt signal to call the ISR function
//  Interrupt_enable(INT_ADCA1);                 // Enable ADCA1 in PIE group 1 and enable INT1 in IER to enable PIE group 1

//--- Finish up
    ADC_enableConverter(ADCA_BASE);             // Power up the ADC
    DEVICE_DELAY_US(1000);                      // Wait 1 ms after power-up before using the ADC

}


void InitDacb(void) {
//************************************************************************************************************//
//*** Note: DAC-B is being configured to use the VREFHI internal voltage reference.  For proper operation, ***//
//*** the reference modes for ADC-B and ADC-C must be configured.  When using the internal reference of    ***//
//*** 3.3V, the DAC gain of x2 should be set.  If using an external reference for DAC-B, remove the two    ***//
//*** ADC_setVREF() and DAC_setGainMode() code lines below.                                                ***//
//************************************************************************************************************//
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-B VREF internal 3.3V
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-C VREF internal 3.3V
    DAC_setGainMode(DACB_BASE, DAC_GAIN_TWO);                               // DAC-B x2 gain

//--- Set VREFHI as as the DAC reference voltage
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

//-- Set load mode
    DAC_setLoadMode(DACB_BASE, DAC_LOAD_SYSCLK);    // Load on next SYSCLK (not using the DAC PWMSYNC signal)

//--- Set DAC-B output to mid-range
    DAC_setShadowValue(DACB_BASE, 0x0800);          // DACVALS = bits 11-0, bits 15-12 reserved; 0x0800 = 2048

//--- Enable DAC-B output
    DAC_enableOutput(DACB_BASE);                    // Enable DAC output
    DEVICE_DELAY_US(10);                            // Required delay after enabling the DAC (delay for DAC to power up)

}



void InitECap(void) {
//---------------------------------------------------------------------
//--- Configure eCAP1 unit for capture
//---------------------------------------------------------------------

//--- Reset the eCAP1.  This is good programming practice.
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);        // Reset eCAP1

//--- Disable all capture interrupts and clear all capture flags
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


    ECAP_disableTimeStampCapture(ECAP1_BASE);                       // Disable CAP1-CAP4 register loads
    ECAP_stopCounter(ECAP1_BASE);                                   // Stop the counter
    ECAP_selectECAPInput(ECAP1_BASE, ECAP_INPUT_INPUTXBAR7);        // Select Input X-BAR INPUT7 as the source for eCAP1

//--- Configure eCAP1
    ECAP_enableCaptureMode(ECAP1_BASE);                                             // Enable capture mode
    ECAP_setCaptureMode(ECAP1_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);    // Continuous mode and wrap after 4 captures

    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_RISING_EDGE);         // Capture event 1 on rising edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_FALLING_EDGE);        // Capture event 2 on falling edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_RISING_EDGE);         // Capture event 3 on rising edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_FALLING_EDGE);        // Capture event 4 on falling edge

    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);                      // Do not reset counter on capture event 1 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);                      // Do not reset counter on capture event 2 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);                      // Do not reset counter on capture event 3 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);                      // Do not reset counter on capture event 4 (absolute time stamp)

    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);              // Capture event 3 interrupt enabled

//--- Enable eCAP1 interrupt
    Interrupt_register(INT_ECAP1, &ecap1ISR);       // Re-map ECAP1 interrupt signal to call the ISR function
    Interrupt_enable(INT_ECAP1);                    // Enable ECAP1 in PIE group 4 and enable INT4 in IER to enable PIE group

//--- Finish up
    ECAP_enableTimeStampCapture(ECAP1_BASE);                // Enable CAP1-CAP4 register loads
    ECAP_startCounter(ECAP1_BASE);                          // Start the counter

}



void InitCla(void) {
#ifdef _FLASH
//--- Copy the CLA program code from its load address to the CLA program
//--- memory (using memcpy() from RTS library).
    memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (uint32_t)&Cla1ProgLoadSize);
#endif

//--- Memory Configuration - Master CPU and CLA Select
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU

//--- Memory Configuration - CLA Data Memory and CLA Program Memory Select
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_PROGRAM);  // Configured as CLA program memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
    MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory

//--- Initialize CLA task interrupt vectors
//*******************************************************************************************************//
//*** Note: suppressing compiler #770-D "conversion from pointer to smaller integer" warning.         ***//
//*** The CLA address range is 16 bits and the addresses passed to the MVECT registers will be in the ***//
//*** lower 64Kw address space. The warning is turned back on after the MVECTs are assigned addresses ***//
//*******************************************************************************************************//
#pragma diag_suppress=770
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_2, (uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_3, (uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_4, (uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_5, (uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_6, (uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_7, (uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_8, (uint16_t)&Cla1Task8);
#pragma diag_warning=770

//--- Select Task interrupt source
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);        // ADCAINT1 is trigger source for Task1
    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);     // Software (none) is trigger source for Task8

//--- Disable background task
    CLA_disableBackgroundTask(CLA1_BASE);       // Disable background task

//--- Enable use of software to start a task (IACK)
    CLA_enableIACK(CLA1_BASE);                  // Enable IACKE to start task using software

//--- Force one-time initialization Task 8 - zero delay buffer
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // Enable CLA task interrupt 8
    asm("  IACK  #0x0080");                                     // IACK - CLA task force instruction
    asm("  RPT #3 || NOP");                                     // Wait at least 4 cycles
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8) == 1);    // Loop until task completes
    CLA_disableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // Disable CLA task interrupt 8

//--- Enable CLA task interrupt 1
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1);                 // Enable CLA interrupt 1

//--- Enable CLA1_1 interrupt
    Interrupt_register(INT_CLA1_1, &cla1Isr1);           // Re-map CLA1 Task1 interrupt signal to call the ISR function
    Interrupt_enable(INT_CLA1_1);                     // Enable CLA1 Task1 in PIE group 11 and enable INT11 in IER to enable PIE group 11

}







