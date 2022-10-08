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
#include "sys_init.h"

// 全局变量
uint16_t DEBUG_TOGGLE = 1;                // 用于实时模式的调制
uint16_t SINE_ENABLE = 0;                 // 用于DAC波形生成
uint16_t PWM_MODULATE = 0;                // 用于PWM调制
uint16_t AdcBuf[ADC_BUF_LEN];             // ADC缓冲区分配
uint16_t AdcBufFiltered[ADC_BUF_LEN];     // ADC过滤数据缓冲区分配
uint16_t DacOffset;                       // DAC偏移
uint16_t DacOutput;                       // DAC输出
uint32_t PwmDuty;                         // 测量的PWM占空比
uint32_t PwmPeriod;                       // 测量的PWM周期
uint16_t ClaFilteredOutput;               // CLA过滤器输出

float32_t xDelay[FILTER_LEN] = {0,0,0,0,0};                         // filter delay chain
float32_t coeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625}; // filter coefficients



#pragma DATA_SECTION(xDelay, "Cla1Data1");
#pragma DATA_SECTION(ClaFilteredOutput, "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(coeffs, "Cla1Data2");


//#pragma DATA_SECTION(AdcBufRaw, "dmaMemBufs");
uint16_t AdcBufRaw[2*ADC_BUF_LEN];          // ADC原始数据缓冲区分配


// main
int main(void){
    DINT;

    sys_init();

    sys_per_init();

    // 开启CPU中断
    Interrupt_enableMaster();


    // 启用全局中断和实时debug
    EINT;
    ERTM;


    // 主循环
    while(1){
        NOP;    // 无操作（asm（NOP））
    }
}
