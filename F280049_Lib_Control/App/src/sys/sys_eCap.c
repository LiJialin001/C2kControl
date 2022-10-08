/*
 * sys_eCap.c
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */
#include "sys_eCap.h"


void InitECap(void) {
//  ����eCAP1��Ԫ�Խ��в���

    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);        // Reset eCAP1

//  �������в����жϲ�������в����־
    ECAP_disableInterrupt(ECAP1_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP1_BASE,
                        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE));

    // ����CAP1-CAP4�Ĵ�������
    ECAP_disableTimeStampCapture(ECAP1_BASE);
    // ֹͣ������
    ECAP_stopCounter(ECAP1_BASE);
    // ѡ��Input X-BAR INPUT7��ΪeCAP1��Դ
    ECAP_selectECAPInput(ECAP1_BASE, ECAP_INPUT_INPUTXBAR7);

//  ����eCAP1  ���ò���ģʽ
    ECAP_enableCaptureMode(ECAP1_BASE);
    // ����ģʽ��4�β������
    ECAP_setCaptureMode(ECAP1_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);

    // �������ز����¼�1
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_RISING_EDGE);
    // ���½���Ե�����¼�2
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_FALLING_EDGE);

    // �����¼�1ʱ�����ü�����������ʱ�����
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);

    // �����¼�3�ж�������
    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);

//  ����eCAP1�ж�  ����ӳ��ECAP1�ж��ź��Ե���ISR����
    Interrupt_register(INT_ECAP1, &ecap1ISR);
    // ��PIE��4������ECAP1������IER������INT4������PIE��
    Interrupt_enable(INT_ECAP1);


    ECAP_enableTimeStampCapture(ECAP1_BASE);                // ����CAP1-CAP4�Ĵ�������
    ECAP_startCounter(ECAP1_BASE);                          // ��������

}
