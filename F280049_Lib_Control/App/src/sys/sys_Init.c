/*
 * sys_Init.c
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#include "sys_Init.h"

void sys_per_init(void) {
    // �����ʼ��
    InitEPwm();
    InitAdca();
    InitDacb();
    InitECap();
    InitCla();
}

void sys_init(void) {
    // CPU�ϵ��ʼ��
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    InitWatchdog();
}
