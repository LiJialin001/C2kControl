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
#include "sys_init.h"

// ȫ�ֱ���
uint16_t DEBUG_TOGGLE = 1;                // ����ʵʱģʽ�ĵ���
uint16_t SINE_ENABLE = 0;                 // ����DAC��������
uint16_t PWM_MODULATE = 0;                // ����PWM����
uint16_t AdcBuf[ADC_BUF_LEN];             // ADC����������
uint16_t AdcBufFiltered[ADC_BUF_LEN];     // ADC�������ݻ���������
uint16_t DacOffset;                       // DACƫ��
uint16_t DacOutput;                       // DAC���
uint32_t PwmDuty;                         // ������PWMռ�ձ�
uint32_t PwmPeriod;                       // ������PWM����
uint16_t ClaFilteredOutput;               // CLA���������

float32_t xDelay[FILTER_LEN] = {0,0,0,0,0};                         // filter delay chain
float32_t coeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625}; // filter coefficients



#pragma DATA_SECTION(xDelay, "Cla1Data1");
#pragma DATA_SECTION(ClaFilteredOutput, "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(coeffs, "Cla1Data2");


//#pragma DATA_SECTION(AdcBufRaw, "dmaMemBufs");
uint16_t AdcBufRaw[2*ADC_BUF_LEN];          // ADCԭʼ���ݻ���������


// main
int main(void){
    DINT;

    sys_init();

    sys_per_init();

    // ����CPU�ж�
    Interrupt_enableMaster();


    // ����ȫ���жϺ�ʵʱdebug
    EINT;
    ERTM;


    // ��ѭ��
    while(1){
        NOP;    // �޲�����asm��NOP����
    }
}
