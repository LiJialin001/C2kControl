/*
 * base_interrupts.c
 *
 *  Created on: 2022年10月5日
 *      Author: Lijialin001
 */

#include "sys.h"


interrupt void adcA1ISR(void){                           // PIE1.1 @ 0x000D40  ADC-A interrupt #1
    static uint16_t *AdcBufPtr = AdcBuf;
    static uint16_t iQuadratureTable = 0;                   // 表索引
    static volatile uint16_t GPIO34_count = 0;              // pin切换计数
    static volatile uint16_t PwmModDelay = 0;               // 更改PWM的计数
    static volatile uint16_t PwmModDir = 1;                 // 创建PWM方向
    static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // PWM的起始值

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);      // 确认PIE组

//  管理ADC中断标志
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);   // 清除ADCINT1标志

    *AdcBufPtr++ = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);    // 读取结果


    if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
    {
        AdcBufPtr = AdcBuf;                         // 将指针倒回起始位置
    }

//  示例：切换GPIO25，以便我们可以用ADC读取***/
    if(DEBUG_TOGGLE == 1)
    {
        GPIO_togglePin(25);
    }

//  示例：以0.5秒的速率切换GPIO34（连接到LED）
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
    if(GPIO34_count++ > 25000)                      // 减缓切换以查看LED闪烁
    {
        GPIO_togglePin(34);
        GPIO34_count = 0;                           // 重置计数
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

//  示例：在10%和90%占空比之间调节ePWM1A输出
    if(PWM_MODULATE == 1)
    {
        if(PwmModDelay++ >= 100)                    // 缓慢更改PWM以查看波形
        {
            // Modulate PWM waveform
            if(PwmModDir == 0)
            {
                PwmCmpaVal += PWM_STEP;             // 按步长增加CMPA值
                if(PwmCmpaVal >= PWM_MIN_DUTY)      // 如果达到极限，则改变方向
                {
                    PwmCmpaVal = PWM_MIN_DUTY;      // 设置为最小占空比
                    PwmModDir = 1;                  // 反转方向
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
            EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // 更新的PWM CMPA值
            PwmModDelay = 0;                        // 重置延迟计数器
        }   // end of modulate PWM waveform
    }
}

//---------------------------------------------------------------------
interrupt void wakeISR(void)                            // PIE1.8 @ 0x000D4E  WAKE interrupt (LPM/WD)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

//  下面两行仅用于调试-插入ISR后删除
    asm (" ESTOP0");                                    // Emulator暂停指令
    while(1);
}

//---------------------------------------------------------------------
interrupt void ecap1ISR(void)                           // PIE4.1 @ 0x000D70  eCAP1 interrupt
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    ECAP_clearGlobalInterrupt(ECAP1_BASE);              // 清除ECAP1中断标志
    ECAP_clearInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);    // 清除CEVT3标志

// Note: eCAP以设备的100 MHz全频率运行。
//       Captured values reflect this time base.

//  计算PWM占空比（上升沿到下降沿）
    PwmDuty = (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_2) - (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);

//  计算PWM周期（上升沿到上升沿）
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

    *AdcBufFilteredPtr++ = ClaFilteredOutput;           // 读取CLA过滤器结果

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
            // Modulate PWM waveform
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








