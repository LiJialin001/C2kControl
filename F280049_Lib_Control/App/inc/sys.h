/*
 * sys.h
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_H_
#define APP_INC_SYS_H_

// ��������
#define PWM_HALF_PERIOD     200             // 250kHz �İ�����
#define PWM_DUTY_CYCLE      50              // 25%ռ�ձ�
#define PWM_MIN_DUTY        20              // PWM���Ƶ�10%ռ�ձ�
#define PWM_MAX_DUTY        180             // PWM���Ƶ�90%ռ�ձ�
#define PWM_STEP            2               // PWM���Ƶ�����
#define ADC_BUF_LEN         50              // ADC buffer length
#define ADC_SAMPLE_PERIOD   1999            // 1999 = 50 kHz sampling w/ 100 MHz ePWM clock
#define FILTER_LEN          5               // filter length
#define SINE_PTS            25              // number of point in sine wave

#if !defined(__TMS320C28XX_CLA__)
    #include <string.h>
#endif

#if !defined(__TMS320C28XX_CLA__)
    #include "driverlib.h"
    #include "device.h"
#else
    #include "hw_types.h"
#endif



// ȫ�ֱ�������
extern float32_t xDelay[FILTER_LEN];
extern float32_t coeffs[FILTER_LEN];
extern uint16_t AdcBuf[ADC_BUF_LEN];
extern uint16_t AdcBufFiltered[ADC_BUF_LEN];
extern uint16_t AdcBufRaw[2*ADC_BUF_LEN];
extern uint16_t ClaFilteredOutput;
extern uint16_t DacOffset;
extern uint16_t DacOutput;
extern uint32_t PwmDuty;
extern uint32_t PwmPeriod;
extern uint16_t DEBUG_TOGGLE;
extern uint16_t SINE_ENABLE;
extern uint16_t PWM_MODULATE;
extern int QuadratureTable[SINE_PTS];



// ����ԭ��-ISR����
extern interrupt void adcA1ISR(void);             // 1.1 - ADCA �ж� 1
extern interrupt void wakeISR(void);              // 1.8 - Watchdog Wake Interrupt
extern interrupt void ecap1ISR(void);             // 4.1 - eCAP1 Interrupt
extern interrupt void dmaCh1ISR(void);            // 7.1 - DMA Channel 1 Interrupt
extern interrupt void cla1Isr1(void);             // 11.1 - CLA1 Interrupt 1


// CLA Function Prototypes
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


// Global symbols defined in the linker command file
extern uint16_t Cla1ProgLoadStart;
extern uint16_t Cla1ProgLoadSize;
extern uint16_t Cla1ProgRunStart;
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;



// ��ʱ��������
static inline void Delay_us(uint16_t us) {
    DEVICE_DELAY_US(us);
}
static inline void Delay_ms(uint16_t ms) {
    uint16_t i = 10;
    for(; i>0; i--)
        Delay_us(1000);
}



// Timer ���
void initCPUTimers(void);
void configCPUTimer(uint32_t cpuTimer, float freq, float period);

// EPwm ���
void InitEPwm(void);

// ���Ź�
void InitWatchdog(void);

// ADC ��ʼ��
void InitAdca(void);
void InitDacb(void);



void InitECap(void);
void InitCla(void);



#endif /* APP_INC_SYS_H_ */
