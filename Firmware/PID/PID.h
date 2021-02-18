#ifndef PID_H
#define PID_H

/* Includes ------------------------------------------------------------------*/
#include "define.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	int8_t Name;
	double Kp;
	double Ki;
	double Kd;
	double Ts;
	double Error;
	double Error_1;
	double Error_2;
	double Omega;
	double Setpoint;
	double Result;
	double Result_1;
	uint16_t PWM;
	double Stable_Angle;
//add filter here 		
}PID_TypeDef;

uint16_t PID_Calculate_Roll(PID_TypeDef *PID_Type, double Angle_Feeback, double Rate_Feedback);
uint16_t PID_Calculate_Pitch(PID_TypeDef *PID_Type, double Angle_Feeback, double Rate_Feedback, double Coefficient, float High_Thres, float Low_Thres);
void PID_Reset_Param(PID_TypeDef *PID_Type);
void PID_Set_Param(PID_TypeDef *PID_Type, uint8_t Name, double Kp, double Ki, double Kd, double Setpoint, double Result_1, double Omega, double Ts);
void PID_Calib_Stable_Angle(PID_TypeDef *PID_Type, double Stable_Angle);

#endif /* PID_H_ */

