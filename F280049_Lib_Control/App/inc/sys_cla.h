/*
 * sys_cla.h
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_CLA_H_
#define APP_INC_SYS_CLA_H_

#include "driverlib.h"
#include "device.h"


extern interrupt void cla1Isr1(void);             // 11.1 - CLA1 Interrupt 1


// CLA 函数原型
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


// 链接器命令文件中定义的全局符号
extern uint16_t Cla1ProgLoadStart;
extern uint16_t Cla1ProgLoadSize;
extern uint16_t Cla1ProgRunStart;


void InitCla(void);

#endif /* APP_INC_SYS_CLA_H_ */
