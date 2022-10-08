/*
 * hw_lcd.h
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#ifndef APP_INC_HW_LCD_H_
#define APP_INC_HW_LCD_H_

#include "driverlib.h"
#include "device.h"
#include "sys.h"

//通用LCD参数
typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t id;
    uint8_t  dir;              // 横屏OR竖屏  0 OR 1
    uint16_t  wramcmd;         // 开始写gram指令
    uint16_t  setxcmd;         // 写x指令
    uint16_t  setycmd;         //写y指令
    uint8_t   xoffset;
    uint8_t   yoffset;
}_lcd_dev;

extern _lcd_dev lcddev;

#define USE_HORIZONTAL       0 //屏幕顺时针旋转角度   0->0  1->90  2->180  3->270


#define LCD_W 128
#define LCD_H 160


extern uint16_t  POINT_COLOR;
extern uint16_t  BACK_COLOR;

// LCD端口定义
#define LED      9        //背光控制          9
#define LCD_CS   11       //片选线           11
#define LCD_RS   10       //数据线           10
#define LCD_RST  12       //复位引脚          12

#define LCD_LED_ON GPIO_writePin(LED, 1);
#define LCD_LED_OFF GPIO_writePin(LED, 0);


//颜色
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

//GUI颜色
#define DARKBLUE         0X01CF //深蓝
#define LIGHTBLUE        0X7D7C //浅蓝
#define GRAYBLUE         0X5458 //灰蓝

#define LIGHTGREEN       0X841F  //浅绿
#define LIGHTGRAY        0XEF5B  //浅灰(PANNEL)
#define LGRAY            0XC618  //浅灰(PANNEL),背景色

#define LGRAYBLUE        0XA651  //浅灰蓝(中间层)
#define LBBLUE           0X2B12  //浅棕蓝(选择项)


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
