/*
 * sys.c
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 */

#include "sys.h"


// ����ѡ��ʱ����ʼ��Ϊ��freq���͡�period������ָ����ʱ��Ρ�
// Ƶ������ΪHz����������Ϊus ���ú󣬿�����ʱ��
// ����configCPUTimer(uint32_t cpuTimer, DEVICE_STSCLK_FREQ, float period)��
void configCPUTimer(uint32_t cpuTimer, float freq, float period) {
    uint32_t temp;

    // ��ʼ����ʱ������
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    // ���÷�Ƶ
    CPUTimer_setPreScaler(cpuTimer, 0);

    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    CPUTimer_startTimer(cpuTimer);
}


void InitWatchdog(void){
    // ���ÿ��Ź�
    SysCtl_setWatchdogPredivider(SYSCTL_WD_PREDIV_512);      // WDPRECLKDIV = INTOSC1/512
    SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_1);       // WDCLK=OSCCLK/512/1
    SysCtl_setWatchdogWindowValue(0);                        // ��С������ֵ�����ã�

    // ���ÿ��Ź�ģʽ
    // SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);

    // Enable / Disable
    SysCtl_disableWatchdog();
    //  SysCtl_enableWatchdog();

    // ���ÿ��Ź��ж�
    Interrupt_register(INT_WAKE, &wakeISR);     // ����ӳ�俴�Ź������ж��ź��Ե���ISR
    Interrupt_enable(INT_WAKE);                 // Enable WAKEINT in PIE group 1 and enable INT1 in IER to enable PIE group 1

}




