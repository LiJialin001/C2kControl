/*
 * sys_interrupts.c
 *
 *  Created on: 2022��10��5��
 *      Author: Lijialin001
 *
 *  Tip���жϷ�������������board��extern�ĺ���������һ��
 */

#include "sys.h"
#include "sys_ePwm.h"
#include "sys_adc.h"
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


interrupt void adcA1ISR(void){                           // PIE1.1 @ 0x000D40  ADC-A interrupt #1
    static uint16_t *AdcBufPtr = AdcBuf;
    static uint16_t iQuadratureTable = 0;                   // ������
    static volatile uint16_t GPIO34_count = 0;              // pin�л�����
    static volatile uint16_t PwmModDelay = 0;               // ����PWM�ļ���
    static volatile uint16_t PwmModDir = 1;                 // ����PWM����
    static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // PWM����ʼֵ

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);      // ȷ��PIE��

//  ����ADC�жϱ�־
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);   // ���ADCINT1��־

    *AdcBufPtr++ = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);    // ��ȡ���


    if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
    {
        AdcBufPtr = AdcBuf;                         // ��ָ�뵹����ʼλ��
    }

//  ʾ�����л�GPIO25���Ա����ǿ�����ADC��ȡ***/
    if(DEBUG_TOGGLE == 1)
    {
        GPIO_togglePin(25);
    }

//  ʾ������0.5��������л�GPIO34�����ӵ�LED��
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
    if(GPIO34_count++ > 25000)                      // �����л��Բ鿴LED��˸
    {
        GPIO_togglePin(34);
        GPIO34_count = 0;                           // ���ü���
    }

//  Write to DAC-B to create input to ADC-A0
    if(SINE_ENABLE == 1)
    {
        DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
    }
    else
    {
        DacOutput = DacOffset;
    }
    if(iQuadratureTable > (SINE_PTS - 1))
    {
        iQuadratureTable = 0;
    }
    DAC_setShadowValue(DACB_BASE, DacOutput);

//  ʾ������10%��90%ռ�ձ�֮�����ePWM1A���
    if(PWM_MODULATE == 1)
    {
        if(PwmModDelay++ >= 100)                    // ��������PWM�Բ鿴����
        {
            // Modulate PWM waveform
            if(PwmModDir == 0)
            {
                PwmCmpaVal += PWM_STEP;             // ����������CMPAֵ
                if(PwmCmpaVal >= PWM_MIN_DUTY)      // ����ﵽ���ޣ���ı䷽��
                {
                    PwmCmpaVal = PWM_MIN_DUTY;      // ����Ϊ��Сռ�ձ�
                    PwmModDir = 1;                  // ��ת����
                }
            }
            else
            {
                PwmCmpaVal -= PWM_STEP;
                if(PwmCmpaVal <= PWM_MAX_DUTY)
                {
                    PwmCmpaVal = PWM_MAX_DUTY;
                    PwmModDir = 0;
                }
            }
            EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // ���µ�PWM CMPAֵ
            PwmModDelay = 0;                        // �����ӳټ�����
        }
    }
}

//---------------------------------------------------------------------
interrupt void wakeISR(void)                            // PIE1.8 @ 0x000D4E  WAKE interrupt (LPM/WD)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

//  �������н����ڵ���-����ISR��ɾ��
    asm (" ESTOP0");                                    // Emulator��ָͣ��
    while(1);
}

//---------------------------------------------------------------------
interrupt void ecap1ISR(void)                           // PIE4.1 @ 0x000D70  eCAP1 interrupt
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    ECAP_clearGlobalInterrupt(ECAP1_BASE);              // ���ECAP1�жϱ�־
    ECAP_clearInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);    // ���CEVT3��־

// Note: eCAP���豸��100 MHzȫƵ�����С�
//       Captured values reflect this time base.

//  ����PWMռ�ձȣ������ص��½��أ�
    PwmDuty = (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_2) - (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);

//  ����PWM���ڣ������ص������أ�
    PwmPeriod = (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_3) - (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);
}

////---------------------------------------------------------------------
//interrupt void dmaCh1ISR(void)                            // PIE7.1 @ 0x000DA0  DMA channel 1 interrupt
//{
//uint16_t *AdcBufPtr = AdcBuf;                           // Pointer to buffer
//static uint16_t iQuadratureTable = 0;                   // Quadrature table index
//static volatile uint16_t GPIO34_count = 0;              // Counter for pin toggle
//static volatile uint16_t PwmModDelay = 0;               // Counter to change PWM
//static volatile uint16_t PwmModDir = 1;                 // Create a direction for PWM
//static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // Starting value for PWM
//static uint16_t iPingPong = 0;                          // Ping Pong flag
//uint16_t *AdcBufRawPtr;                                 // Pointer to ADC raw data buffer
//uint16_t i;                                             // General purpose uint16_t
//
//  Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);      // Must acknowledge the PIE group
//
////--- Process the ADC data
//  if(iPingPong == 0)  // Ping buffer filling, process Pong buffer
//  {
//      // Manage the DMA address registers - adjust DST start address for Pong buffer
//      DMA_configAddresses(DMA_CH1_BASE, (const void *)(AdcBufRaw + ADC_BUF_LEN), (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));
//
//      // Initialization the raw data buffer pointer
//      AdcBufRawPtr = AdcBufRaw + ADC_BUF_LEN;         // Point to Pong buffer
//
//      // Raw ADC data
//      for(i=0; i<ADC_BUF_LEN; i++)
//      {
//          //--- Read the ADC result:
//          *AdcBufPtr++ = *AdcBufRawPtr++;
//      }
//  }
//  else    // Pong buffer filling, process Ping buffer
//  {
//      // Manage the DMA address registers - adjust DST start address for Ping buffer
//      DMA_configAddresses(DMA_CH1_BASE, (const void *)AdcBufRaw, (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));
//
//      // Initialization the raw data buffer pointer
//      AdcBufRawPtr = AdcBufRaw;                       // Point to Ping buffer
//
//      // Raw ADC data
//      for(i=0; i<ADC_BUF_LEN; i++)
//      {
//          //--- Read the ADC result:
//          *AdcBufPtr++ = *AdcBufRawPtr++;
//      }
//  }
////--- Update the Ping Pong buffer flag
//  iPingPong ^= 1;                                     // iPingPong toggles between 0 and 1
//
////--- Example: Toggle GPIO25 so we can read it with the ADC ***/
//  if(DEBUG_TOGGLE == 1)
//  {
//        GPIO_togglePin(25);                          // Toggle the pin
//  }
//
////--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED).
////             (1/50000 sec/sample)*(50 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
////             ==> x = 500
//  if(GPIO34_count++ > 500)                        // Toggle slowly to see the LED blink
//  {
//        GPIO_togglePin(34);                         // Toggle the pin
//      GPIO34_count = 0;                           // Reset the counter
//  }
//
////--- Write to DAC-B to create input to ADC-A0
//  if(SINE_ENABLE == 1)
//  {
//      DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
//  }
//  else
//  {
//      DacOutput = DacOffset;
//  }
//    if(iQuadratureTable > (SINE_PTS - 1))               // Wrap the index
//    {
//        iQuadratureTable = 0;
//    }
//    DAC_setShadowValue(DACB_BASE, DacOutput);
//
////--- Example: Modulate ePWM1A output between 10% and 90% duty cycle
//  if(PWM_MODULATE == 1)
//  {
//      if(PwmModDelay++ >= 100)                        // Change PWM slowly to see waveform
//      {
//          // Modulate PWM waveform
//          if(PwmModDir == 0)
//          {
//              PwmCmpaVal += PWM_STEP;                 // Increment CMPA value by step size
//              if(PwmCmpaVal >= PWM_MIN_DUTY)          // If limit reached then change direction
//              {
//                  PwmCmpaVal = PWM_MIN_DUTY;          // Set to minimum duty cycle
//                  PwmModDir = 1;                      // Reverse direction
//              }
//          }
//          else
//          {
//              PwmCmpaVal -= PWM_STEP;                 // Decrement CMPA value by step size
//              if(PwmCmpaVal <= PWM_MAX_DUTY)          // If limit reached then change direction
//              {
//                  PwmCmpaVal = PWM_MAX_DUTY;          // Set to maximum duty cycle
//                  PwmModDir = 0;                      // Reverse direction
//              }
//          }
//          EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // Updated PWM CMPA value
//          PwmModDelay = 0;                            // Reset the delay counter
//      }   // end of modulate PWM waveform
//  }
//}

//---------------------------------------------------------------------
interrupt void cla1Isr1(void)                           // PIE11.1 @ 0x000DE0 CLA1 interrupt #1
{
static uint16_t *AdcBufPtr = AdcBuf;
static uint16_t iQuadratureTable = 0;
static uint16_t *AdcBufFilteredPtr = AdcBufFiltered;
static volatile uint16_t GPIO34_count = 0;
static volatile uint16_t PwmModDelay = 0;
static volatile uint16_t PwmModDir = 1;
static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    *AdcBufPtr++ = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    *AdcBufFilteredPtr++ = ClaFilteredOutput;           // ��ȡCLA���������

    if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
    {
        AdcBufPtr = AdcBuf;
        AdcBufFilteredPtr = AdcBufFiltered;
    }

    if(DEBUG_TOGGLE == 1)
    {
        GPIO_togglePin(25);
    }

//--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED).
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
    if(GPIO34_count++ > 25000)
    {
        GPIO_togglePin(34);
        GPIO34_count = 0;
    }

    if(SINE_ENABLE == 1)
    {
        DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
    }
    else
    {
        DacOutput = DacOffset;
    }
    if(iQuadratureTable > (SINE_PTS - 1))
    {
        iQuadratureTable = 0;
    }
    DAC_setShadowValue(DACB_BASE, DacOutput);

    if(PWM_MODULATE == 1)
    {
        if(PwmModDelay++ >= 100)
        {
            // ����pwm��
            if(PwmModDir == 0)
            {
                PwmCmpaVal += PWM_STEP;
                if(PwmCmpaVal >= PWM_MIN_DUTY)
                {
                    PwmCmpaVal = PWM_MIN_DUTY;
                    PwmModDir = 1;
                }
            }
            else
            {
                PwmCmpaVal -= PWM_STEP;
                if(PwmCmpaVal <= PWM_MAX_DUTY)
                {
                    PwmCmpaVal = PWM_MAX_DUTY;
                    PwmModDir = 0;
                }
            }
            EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);
            PwmModDelay = 0;
        }
    }
}








