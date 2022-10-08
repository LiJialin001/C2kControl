/*
 * sys_cla.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#include "sys_cla.h"

void InitCla(void) {
#ifdef _FLASH
//  将CLA程序代码从其加载地址复制到CLA程序
    memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (uint32_t)&Cla1ProgLoadSize);
#endif

//  内存配置-主CPU和CLA选择
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);     // CPU和CLA之间共享
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_ONLY);     // 专用于CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_ONLY);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMMASTER_CPU_ONLY);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMMASTER_CPU_ONLY);

//  内存配置-CLA数据内存和CLA程序内存选择
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);     // 配置为CLA数据存储器
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_PROGRAM);  // 配置为CLA程序内存
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);

//  初始化CLA任务中断向量
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

//  选择任务中断源
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);        // ADCAINT1是Task1的触发源
    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);     // 软件（无）是Task8的触发源

//  禁用后台任务
    CLA_disableBackgroundTask(CLA1_BASE);

//  允许使用软件启动任务（IACK）
    CLA_enableIACK(CLA1_BASE);

//  强制一次性初始化任务8-零延迟缓冲区
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_8);                 // 启用CLA任务中断8
    asm("  IACK  #0x0080");                                     // IACK-CLA工作组指令
    asm("  RPT #3 || NOP");                                     // 至少等待4个周期
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8) == 1);    // 循环直到任务完成
    CLA_disableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // 禁用CLA任务中断8

//  启用CLA任务中断1
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1);

//  启用CLA1_1中断
    Interrupt_register(INT_CLA1_1, &cla1Isr1);
    Interrupt_enable(INT_CLA1_1);

}
