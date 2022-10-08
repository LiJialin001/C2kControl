/*
 * sys_cla.h
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_CLA_H_
#define APP_INC_SYS_CLA_H_

#include "driverlib.h"
#include "device.h"


extern interrupt void cla1Isr1(void);             // 11.1 - CLA1 Interrupt 1


// CLA ����ԭ��
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


// �����������ļ��ж����ȫ�ַ���
extern uint16_t Cla1ProgLoadStart;
extern uint16_t Cla1ProgLoadSize;
extern uint16_t Cla1ProgRunStart;


void InitCla(void);

#endif /* APP_INC_SYS_CLA_H_ */
