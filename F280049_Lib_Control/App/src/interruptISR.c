/*
 * interruptISR.c
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 *
 *  Tip���жϷ�������������board��extern�ĺ���������һ��
 *  ������ִ���жϷ������
 */

#include "device.h"
#include "driverlib.h"
#include "board.h"

__interrupt void cpuTimer0ISR(void){
//    cpuTimer0IntCount++;
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void epwm1ISR(void){

//    EPWM_clearTripZoneFlag(myEPWM1_BASE, EPWM_TZ_FLAG_CBC | EPWM_TZ_FLAG_DCBEVT2 | EPWM_TZ_INTERRUPT);
//    EPWM_clearCycleByCycleTripZoneFlag(myEPWM1_BASE, EPWM_TZ_CBC_FLAG_DCBEVT2);
//
//    //
//    // Clear INT flag for this timer
//    //
//    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
//
//    //
//    // Acknowledge interrupt group
//    //
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

}
