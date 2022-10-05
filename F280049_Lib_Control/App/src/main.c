/*
 * main.c
 *
 *  Created on: 2022��10��4��
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
    // CPU�ϵ��ʼ��
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    InitWatchdog();


    // �����ʼ��



    // Enables CPU interrupts
    Interrupt_enableMaster();


    // ����ȫ���жϺ�ʵʱdebug
    EINT;
    ERTM;


    // ��ѭ��
    while(1){
        NOP;    // �޲�����asm��NOP����
    }
}
