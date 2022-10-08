/*
 * hw_lcd.h
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#ifndef APP_INC_HW_LCD_H_
#define APP_INC_HW_LCD_H_

#include "driverlib.h"
#include "device.h"
#include "sys.h"

//ͨ��LCD����
typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t id;
    uint8_t  dir;              // ����OR����  0 OR 1
    uint16_t  wramcmd;         // ��ʼдgramָ��
    uint16_t  setxcmd;         // дxָ��
    uint16_t  setycmd;         //дyָ��
    uint8_t   xoffset;
    uint8_t   yoffset;
}_lcd_dev;

extern _lcd_dev lcddev;

#define USE_HORIZONTAL       0 //��Ļ˳ʱ����ת�Ƕ�   0->0  1->90  2->180  3->270


#define LCD_W 128
#define LCD_H 160


extern uint16_t  POINT_COLOR;
extern uint16_t  BACK_COLOR;

// LCD�˿ڶ���
#define LED      9        //�������          9
#define LCD_CS   11       //Ƭѡ��           11
#define LCD_RS   10       //������           10
#define LCD_RST  12       //��λ����          12

#define LCD_LED_ON GPIO_writePin(LED, 1);
#define LCD_LED_OFF GPIO_writePin(LED, 0);


//��ɫ
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0XBC40
#define BRRED       0XFC07
#define GRAY        0X8430
#define GRAY0       0xEF7D
#define GRAY1       0x8410
#define GRAY2       0x4208

//GUI��ɫ
#define DARKBLUE         0X01CF //����
#define LIGHTBLUE        0X7D7C //ǳ��
#define GRAYBLUE         0X5458 //����

#define LIGHTGREEN       0X841F  //ǳ��
#define LIGHTGRAY        0XEF5B  //ǳ��(PANNEL)
#define LGRAY            0XC618  //ǳ��(PANNEL),����ɫ

#define LGRAYBLUE        0XA651  //ǳ����(�м��)
#define LBBLUE           0X2B12  //ǳ����(ѡ����)


void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);

uint16_t LCD_RD_DATA(void);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WR_DATA(uint8_t data);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
uint16_t LCD_BGR2RGB(uint16_t c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction );


#endif /* APP_INC_HW_LCD_H_ */
