/*
 * myMath.h
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 */

#ifndef APP_INC_MYMATH_H_
#define APP_INC_MYMATH_H_


//�ⲿ�ļ�����
#include "driverlib.h"


//�궨����
#define squa( Sq )        (((float)Sq)*((float)Sq))
#define absu16( Math_X )  ((Math_X)<0? -(Math_X):(Math_X))
#define absFloat( Math_X )((Math_X)<0? -(Math_X):(Math_X))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define LIMIT( x, min, max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )


//���ݽṹ����


//Extern����
//extern const float PI;


//��������
extern float safe_asin(float v);
extern float arcsin(float x);
extern float arctan(float x);
extern float sine(float x);
extern float cosine(float x);
extern float Q_rsqrt(float number);
extern float VariableParameter(float error);


#endif /* APP_INC_MYMATH_H_ */
