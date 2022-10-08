/*
 * sys_cla.c
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#include "sys_cla.h"

void InitCla(void) {
#ifdef _FLASH
//  ��CLA������������ص�ַ���Ƶ�CLA����
    memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (uint32_t)&Cla1ProgLoadSize);
#endif

//  �ڴ�����-��CPU��CLAѡ��
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);     // CPU��CLA֮�乲��
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_ONLY);     // ר����CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_ONLY);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMMASTER_CPU_ONLY);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMMASTER_CPU_ONLY);

//  �ڴ�����-CLA�����ڴ��CLA�����ڴ�ѡ��
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);     // ����ΪCLA���ݴ洢��
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_PROGRAM);  // ����ΪCLA�����ڴ�
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);

//  ��ʼ��CLA�����ж�����
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

//  ѡ�������ж�Դ
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);        // ADCAINT1��Task1�Ĵ���Դ
    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);     // ������ޣ���Task8�Ĵ���Դ

//  ���ú�̨����
    CLA_disableBackgroundTask(CLA1_BASE);

//  ����ʹ�������������IACK��
    CLA_enableIACK(CLA1_BASE);

//  ǿ��һ���Գ�ʼ������8-���ӳٻ�����
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_8);                 // ����CLA�����ж�8
    asm("  IACK  #0x0080");                                     // IACK-CLA������ָ��
    asm("  RPT #3 || NOP");                                     // ���ٵȴ�4������
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8) == 1);    // ѭ��ֱ���������
    CLA_disableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // ����CLA�����ж�8

//  ����CLA�����ж�1
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1);

//  ����CLA1_1�ж�
    Interrupt_register(INT_CLA1_1, &cla1Isr1);
    Interrupt_enable(INT_CLA1_1);

}
