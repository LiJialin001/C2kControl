/*
 * math_pid.c
 *
 *  Created on: 2022��10��4��
 *      Author: Lijialin001
 *
 *      PIDʹ�÷�����
 *       1.����һ��PIDInfo_t�ṹ�壬������Ҫ���Ƶ����ݴ�Ž�ȥ
 *       2.��UpdatePID����������PID������
 *       3.����ֱ�ӵ���ClacCascadePIDֱ�Ӽ��㴮��PID
 */

//�ⲿ�ļ�����
#include "math_pid.h"
#include "myMath.h"

//PID����
PIDInfo_t PIDGroup[emNum_Of_PID_List];


void ResetPID(void)
{
    int i = 0;
    for(i = 0; i < emNum_Of_PID_List; i++)
    {
        PIDGroup[i].integ = 0;
        PIDGroup[i].prevError = 0;
        PIDGroup[i].out = 0;
        PIDGroup[i].offset = 0;
        PIDGroup[i].Err = 0;
        PIDGroup[i].desired = 0;     //< set point
        PIDGroup[i].measured = 0;
        PIDGroup[i].out = 0;
    }

  //  PIDGroup_desired_yaw_pos_tmp= 0;
}



void UpdatePID(PIDInfo_t* pid, const float dt)    // pid��Ҫ�����PID�ṹ��ָ��    dt����λ����ʱ��
{
    float deriv;

    pid->Err = pid->desired - pid->measured + pid->offset; //��ǰ�Ƕ���ʵ�ʽǶȵ����

    if(pid->Err_LimitHigh != 0 && pid->Err_LimitLow != 0)
    {
        pid->Err = LIMIT(pid->Err, pid->Err_LimitLow, pid->Err_LimitHigh);
    }

    pid->integ += pid->Err * dt;

    if(pid->IntegLimitHigh != 0 && pid->IntegLimitLow != 0)
    {
        pid->integ = LIMIT(pid->integ, pid->IntegLimitLow, pid->IntegLimitHigh);
    }

    //deriv = (pid->Err - pid->prevError)/dt;
    deriv = -(pid->measured - pid->prevError)/dt;

    pid->out = pid->kp * pid->Err + pid->ki * pid->integ + pid->kd * deriv;//PID���

    if(pid->OutLimitHigh != 0 && pid->OutLimitLow != 0)
    {
        pid->out = LIMIT(pid->out, pid->OutLimitLow, pid->OutLimitHigh);
    }

    pid->prevError = pid->measured;//pid->Err;
}


void ClacCascadePID(PIDInfo_t* pidA, PIDInfo_t* pidB, const float dt)  // ����PID  pidA:�ڻ�  pidB:�⻷  dt����λ����ʱ��
{
    UpdatePID(pidB, dt);    //�ȼ����⻷
    pidA->desired = pidB->out;
    UpdatePID(pidA, dt);
}


void PID_Init(void)
{
    PIDGroup[emPID_AUX1].kp   = 15.0f;
    PIDGroup[emPID_AUX1].ki   = 1.5f;
    PIDGroup[emPID_AUX1].kd   = 0.7f;
    PIDGroup[emPID_AUX1].IntegLimitHigh = 75;
    PIDGroup[emPID_AUX1].IntegLimitLow = -75;
    PIDGroup[emPID_AUX1].OutLimitHigh = 200;
    PIDGroup[emPID_AUX1].OutLimitLow = -200;


    PIDGroup[emPID_AUX2].kp   = 1.8f;
    PIDGroup[emPID_AUX2].ki   = 1.0f;
    PIDGroup[emPID_AUX2].kd   = 0.12f;
    PIDGroup[emPID_AUX2].IntegLimitHigh = 50;
    PIDGroup[emPID_AUX2].IntegLimitLow = -50;
    PIDGroup[emPID_AUX2].OutLimitHigh = 300;
    PIDGroup[emPID_AUX2].OutLimitLow = -300;


    PIDGroup[emPID_AUX3].kp    = 15.0f;
    PIDGroup[emPID_AUX3].ki    = 1.5f;
    PIDGroup[emPID_AUX3].kd    = 0.7f;
    PIDGroup[emPID_AUX3].IntegLimitHigh = 75;
    PIDGroup[emPID_AUX3].IntegLimitLow = -75;
    PIDGroup[emPID_AUX3].OutLimitHigh = 200;
    PIDGroup[emPID_AUX3].OutLimitLow = -200;

    PIDGroup[emPID_AUX4].kp    = 1.8f;
    PIDGroup[emPID_AUX4].ki    = 1.0f;
    PIDGroup[emPID_AUX4].kd    = 0.12f;
    PIDGroup[emPID_AUX4].IntegLimitHigh = 50;
    PIDGroup[emPID_AUX4].IntegLimitLow = -50;
    PIDGroup[emPID_AUX4].OutLimitHigh = 300;
    PIDGroup[emPID_AUX4].OutLimitLow = -300;



    PIDGroup[emPID_AUX5].kp     = 8.0f;
    PIDGroup[emPID_AUX5].ki     = 3.0f;
    PIDGroup[emPID_AUX5].kd     = 0.00f;
    PIDGroup[emPID_AUX5].OutLimitHigh = 200;
    PIDGroup[emPID_AUX5].OutLimitLow = -200;
}
