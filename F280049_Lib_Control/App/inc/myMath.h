/*
 * myMath.h
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 */

#ifndef APP_INC_MYMATH_H_
#define APP_INC_MYMATH_H_


//外部文件引用
#include "driverlib.h"


//宏定义区
#define squa( Sq )        (((float)Sq)*((float)Sq))
#define absu16( Math_X )  ((Math_X)<0? -(Math_X):(Math_X))
#define absFloat( Math_X )((Math_X)<0? -(Math_X):(Math_X))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define LIMIT( x, min, max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )


//数据结构声明


//Extern引用
//extern const float PI;


//函数声明
extern float safe_asin(float v);
extern float arcsin(float x);
extern float arctan(float x);
extern float sine(float x);
extern float cosine(float x);
extern float Q_rsqrt(float number);
extern float VariableParameter(float error);


#endif /* APP_INC_MYMATH_H_ */
