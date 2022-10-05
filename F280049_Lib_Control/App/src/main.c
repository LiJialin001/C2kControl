/*
 * main.c
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 *      Devices: TMS320F28004x
 */

#include "device.h"
#include "driverlib.h"
#include "board.h"
#include "sys.h"

// Globals



// main
int main(void){
    // CPU上电初始化
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    InitWatchdog();


    // 外设初始化



    // Enables CPU interrupts
    Interrupt_enableMaster();


    // 启用全局中断和实时debug
    EINT;
    ERTM;


    // 主循环
    while(1){
        NOP;    // 无操作（asm（NOP））
    }
}
