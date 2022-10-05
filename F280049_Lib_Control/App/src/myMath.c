/*
 * myMath.c
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 */


//�ⲿ�ļ�����
#include "myMath.h"
#include <math.h>



float sine(float x)
{
    float Q = 0.775f;
    float P = 0.225f;
    float B =  1.273239544;
    float tmp_c = -0.405284f;
    float y = B * x + tmp_c * x * fabs(x);
    return (Q * y + P * y * fabs(y));
}


float cosine(float x)
{
    return sine(x + M_PI / 2);
}


float arctan(float x)      //�������������չ��ʽ ����Խ�ߣ�ֵԽ׼ȷ70��������׼ȷ��
{
    float t = x;
    float result = 0;
    float X2 = x * x;
    unsigned char cnt = 1;
    do
    {
        result += t / ((cnt << 1) - 1);
        t = -t;
        t *= X2;
        cnt++;
    }while(cnt <= 6);

    return result;
}


float arcsin(float x)   //�������������չ��ʽ -1 < x < +1     42��������׼ȷ��
{
    float d = 1;
    float t = x;
    unsigned char cnt = 1;
    float result = 0;
    float X2 = x * x;

    if (x >= 1.0f)
    {
        return M_PI_2;
    }
    if (x <= -1.0f)
    {
        return -M_PI_2;
    }
    do
    {
        result += t / (d * ((cnt << 1) - 1));
        t *= X2 * ((cnt << 1) - 1);//
        d *= (cnt << 1);//2 4 6 8 10 ...
        cnt++;
    }while(cnt <= 6);

    return result;
}


float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = *(long*) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = *(float*) &i;
    y  = y * (threehalfs - (x2 * y * y ));   // 1st iteration ����һ��ţ�ٵ�����
    return y;
}



float data_limit(float data, float toplimit, float lowerlimit)   //�����޷�
{
  if(data > toplimit)  data = toplimit;
  else if(data < lowerlimit) data = lowerlimit;
    return data;
}
