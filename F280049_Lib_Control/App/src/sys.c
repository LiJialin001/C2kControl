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


void configEPWM(void) {



}

void InitWatchdog(void)
{
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

} // end of InitWatchdog()












