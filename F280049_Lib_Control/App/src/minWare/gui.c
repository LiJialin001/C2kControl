/*
 * gui.c
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#include "font.h"
#include "hw_lcd.h"
#include "gui.h"


void GUI_DrawPoint(u16 x,u16 y,u16 color)
{
    LCD_SetCursor(x,y); // 光标位置
    Lcd_WriteData_16Bit(color);
}



void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
    u16 i,j;
    u16 width=ex-sx+1;
    u16 height=ey-sy+1;
    LCD_SetWindows(sx,sy,ex,ey);
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        Lcd_WriteData_16Bit(color);
    }
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}



void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;

    delta_x=x2-x1;
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1;
    else if(delta_x==0)incx=0;
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x;
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )
    {
        LCD_DrawPoint(uRow,uCol);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}


void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_DrawLine(x1,y1,x2,y1);
    LCD_DrawLine(x1,y1,x1,y2);
    LCD_DrawLine(x1,y2,x2,y2);
    LCD_DrawLine(x2,y1,x2,y2);
}


void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}


void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
{
    GUI_DrawPoint(xc + x, yc + y, c);

    GUI_DrawPoint(xc - x, yc + y, c);

    GUI_DrawPoint(xc + x, yc - y, c);

    GUI_DrawPoint(xc - x, yc - y, c);

    GUI_DrawPoint(xc + y, yc + x, c);

    GUI_DrawPoint(xc - y, yc + x, c);

    GUI_DrawPoint(xc + y, yc - x, c);

    GUI_DrawPoint(xc - y, yc - x, c);
}


void gui_circle(int xc, int yc,u16 c,int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;


    if (fill)
    {

        while (x <= y) {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    } else
    {

        while (x <= y) {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}



void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
    LCD_DrawLine(x0,y0,x1,y1);
    LCD_DrawLine(x1,y1,x2,y2);
    LCD_DrawLine(x2,y2,x0,y0);
}

static void _swap(u16 *a, u16 *b)
{
    u16 tmp;
  tmp = *a;
    *a = *b;
    *b = tmp;
}


void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
    u16 a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0;
    long sb = 0;
    if (y0 > y1)
    {
    _swap(&y0,&y1);
        _swap(&x0,&x1);
    }
    if (y1 > y2)
    {
    _swap(&y2,&y1);
        _swap(&x2,&x1);
    }
  if (y0 > y1)
    {
    _swap(&y0,&y1);
        _swap(&x0,&x1);
  }
    if(y0 == y2)
    {
        a = b = x0;
        if(x1 < a)
    {
            a = x1;
    }
    else if(x1 > b)
    {
            b = x1;
    }
    if(x2 < a)
    {
            a = x2;
    }
        else if(x2 > b)
    {
            b = x2;
    }
        LCD_Fill(a,y0,b,y0,POINT_COLOR);
    return;
    }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if(y1 == y2)
    {
        last = y1;
    }
  else
    {
        last = y1-1;
    }
    for(y=y0; y<=last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
    sb += dx02;
    if(a > b)
    {
            _swap(&a,&b);
        }
        LCD_Fill(a,y,b,y,POINT_COLOR);
    }
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if(a > b)
        {
            _swap(&a,&b);
        }
        LCD_Fill(a,y,b,y,POINT_COLOR);
    }
}



void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
{
    u8 temp;
    u8 pos,t;
    u16 colortemp=POINT_COLOR;

    num=num-' ';
    LCD_SetWindows(x,y,x+size/2-1,y+size-1);
    if(!mode)
    {
        for(pos=0;pos<size;pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];
            else temp=asc2_1608[num][pos];
            for(t=0;t<size/2;t++)
            {
                if(temp&0x01)Lcd_WriteData_16Bit(fc);
                else Lcd_WriteData_16Bit(bc);
                temp>>=1;

            }

        }
    }else
    {
        for(pos=0;pos<size;pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];
            else temp=asc2_1608[num][pos];
            for(t=0;t<size/2;t++)
            {
                POINT_COLOR=fc;
                if(temp&0x01)LCD_DrawPoint(x+t,y+pos);
                temp>>=1;
            }
        }
    }
    POINT_COLOR=colortemp;
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}


void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
{
    while((*p<='~')&&(*p>=' '))
    {
        if(x>(lcddev.width-1)||y>(lcddev.height-1))
        return;
        LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    }
}


u32 mypow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}


void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/mypow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
                continue;
            }else enshow=1;

        }
        LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0);
    }
}


//void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
//{
//  u8 i,j;
//  u16 k;
//  u16 HZnum;
//  u16 x0=x;
//  HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);
//
//
//  for (k=0;k<HZnum;k++)
//  {
//    if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
//    {     LCD_SetWindows(x,y,x+16-1,y+16-1);
//          for(i=0;i<16*2;i++)
//          {
//              for(j=0;j<8;j++)
//              {
//                  if(!mode)
//                  {
//                      if(tfont16[k].Msk[i]&(0x80>>j)) Lcd_WriteData_16Bit(fc);
//                      else Lcd_WriteData_16Bit(bc);
//                  }
//                  else
//                  {
//                      POINT_COLOR=fc;
//                      if(tfont16[k].Msk[i]&(0x80>>j)) LCD_DrawPoint(x,y);
//                      x++;
//                      if((x-x0)==16)
//                      {
//                          x=x0;
//                          y++;
//                          break;
//                      }
//                  }

//              }
//
//          }
//
//
//      }
//      continue;
//  }

//  LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
//}


//void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
//{
//  u8 i,j;
//  u16 k;
//  u16 HZnum;
//  u16 x0=x;
//  HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);  //????????
//
//          for (k=0;k<HZnum;k++)
//          {
//            if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
//            {     LCD_SetWindows(x,y,x+24-1,y+24-1);
//                  for(i=0;i<24*3;i++)
//                  {
//                          for(j=0;j<8;j++)
//                          {
//                              if(!mode) //?????
//                              {
//                                  if(tfont24[k].Msk[i]&(0x80>>j)) Lcd_WriteData_16Bit(fc);
//                                  else Lcd_WriteData_16Bit(bc);
//                              }
//                          else
//                          {
//                              POINT_COLOR=fc;
//                              if(tfont24[k].Msk[i]&(0x80>>j)) LCD_DrawPoint(x,y);//????
//                              x++;
//                              if((x-x0)==24)
//                              {
//                                  x=x0;
//                                  y++;
//                                  break;
//                              }
//                          }
//                      }
//                  }
//
//
//              }
//              continue;  //?????????????,??????????????
//          }

//  LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//???????
//}


//void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
//{
//  u8 i,j;
//  u16 k;
//  u16 HZnum;
//  u16 x0=x;
//  HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);  //????????
//  for (k=0;k<HZnum;k++)
//          {
//            if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
//            {     LCD_SetWindows(x,y,x+32-1,y+32-1);
//                  for(i=0;i<32*4;i++)
//                  {
//                      for(j=0;j<8;j++)
//                      {
//                          if(!mode) //?????
//                          {
//                              if(tfont32[k].Msk[i]&(0x80>>j)) Lcd_WriteData_16Bit(fc);
//                              else Lcd_WriteData_16Bit(bc);
//                          }
//                          else
//                          {
//                              POINT_COLOR=fc;
//                              if(tfont32[k].Msk[i]&(0x80>>j)) LCD_DrawPoint(x,y);//????
//                              x++;
//                              if((x-x0)==32)
//                              {
//                                  x=x0;
//                                  y++;
//                                  break;
//                              }
//                          }
//                      }
//                  }
//
//
//              }
//              continue;  //?????????????,??????????????
//          }
//
//  LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//???????
//}


void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
{
    u16 x0=x;
    u8 bHz=0;
    while(*str!=0)
    {
        if(!bHz)
        {
            if(x>(lcddev.width-size/2)||y>(lcddev.height-size))
            return;
            if(*str>0x80)bHz=1;//中文
            else
            {
                if(*str==0x0D)//换行
                {
                    y+=size;
                    x=x0;
                    str++;
                }
                else
                {
                    if(size>16)
                    {
                    LCD_ShowChar(x,y,fc,bc,*str,16,mode);
                    x+=8;
                    }
                    else
                    {
                    LCD_ShowChar(x,y,fc,bc,*str,size,mode);
                    x+=size/2;
                    }
                }
                str++;

            }
        }else//中文
        {
            if(x>(lcddev.width-size)||y>(lcddev.height-size))
            return;
            bHz=0;//有可用汉字裤
//          if(size==32)
//          GUI_DrawFont32(x,y,fc,bc,str,mode);
//          else if(size==24)
//          GUI_DrawFont24(x,y,fc,bc,str,mode);
//          else
//          GUI_DrawFont16(x,y,fc,bc,str,mode);
//
            str+=2;
            x+=size;
        }
    }
}


void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
{
    u16 len=strlen((const char *)str);
    u16 x1=(lcddev.width-len*8)/2;
    Show_Str(x1,y,fc,bc,str,size,mode);
}



void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) //40*40 QQ
{
    int i;
    unsigned char picH,picL;
    LCD_SetWindows(x,y,x+40-1,y+40-1);
    for(i=0;i<40*40;i++)
    {
        picL=*(p+i*2);
        picH=*(p+i*2+1);
        Lcd_WriteData_16Bit(picH<<8|picL);
    }
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}
void Gui_Drawbmp32(u16 x,u16 y,const unsigned char *p) //60*60 QQ
{
    int i;
    unsigned char picH,picL;
    LCD_SetWindows(x,y,x+60-1,y+60-1);
    for(i=0;i<60*60;i++)
    {
        picL=*(p+i*2);
        picH=*(p+i*2+1);
        Lcd_WriteData_16Bit(picH<<8|picL);
    }
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}


void English_Font_test(void)
{
    DrawTestPage("English Test");
    Show_Str(10,22,BLUE,YELLOW,"6X12:abcdefgh01234567",12,0);
    Show_Str(10,34,BLUE,YELLOW,"6X12:ABCDEFGH01234567",12,1);
    Show_Str(10,47,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:",12,0);
    Show_Str(10,60,BLUE,YELLOW,"8X16:abcde01234",16,0);
    Show_Str(10,76,BLUE,YELLOW,"8X16:ABCDE01234",16,1);
    Show_Str(10,92,BLUE,YELLOW,"8X16:~!@#$%^&*()",16,0);
    delay_ms(1200);
}

void DrawTestPage(u8 *str)
{
LCD_Clear(WHITE);
LCD_Fill(0,0,lcddev.width,25,BLUE);
LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);
Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"thank you!!!",16,1);
//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

