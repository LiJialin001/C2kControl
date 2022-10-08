/*
 * sys_Init.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#include "sys_Init.h"

void sys_per_init(void) {
    // 外设初始化
    InitEPwm();
    InitAdca();
    InitDacb();
    InitECap();
    InitCla();
}

void sys_init(void) {
    // CPU上电初始化
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    InitWatchdog();
}
