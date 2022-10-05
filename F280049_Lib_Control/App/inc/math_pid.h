/*
 * math_pid.h
 *
 *  Created on: 2022年10月4日
 *      Author: Lijialin001
 */

#ifndef APP_INC_MATH_PID_H_
#define APP_INC_MATH_PID_H_


//外部文件引用
#include <stdbool.h>
#include "stdint.h"

//数据结构声明
typedef enum
{
    emPID_AUX1,
    emPID_AUX2,
    emPID_AUX3,
    emPID_AUX4,
    emPID_AUX5,

    emNum_Of_PID_List,
}emPID_list_t;

typedef struct
{
    float kp;           //  < proportional gain
    float ki;           //  < integral gain
    float kd;           //  < derivative gain
    float out;
    float Err;
    float desired;     //  < set point
    float measured;

    float Err_LimitHigh;
    float Err_LimitLow;

    float offset;      //
    float prevError;    //  < previous error
    float integ;        //  < integral

    float IntegLimitHigh;       //  < integral limit
    float IntegLimitLow;

    float OutLimitHigh;
    float OutLimitLow;
}PIDInfo_t;

//Extern引用
extern PIDInfo_t PIDGroup[emNum_Of_PID_List];

//函数声明
void ResetPID(void);
void ClacCascadePID(PIDInfo_t* pidA, PIDInfo_t* pidB, const float dt);  //串级PID
void UpdatePID(PIDInfo_t* pid, const float dt);  //PID
extern void PID_Init(void);

#endif /* APP_INC_MATH_PID_H_ */
