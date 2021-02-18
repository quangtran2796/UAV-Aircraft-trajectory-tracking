#ifndef CONTROL_H
#define CONTROL_H

#include "include.h"

typedef enum{
	CALIB_MODE = 0,
	MANUAL_MODE,
	AUTO_MODE,
	TEST_CALIB_MODE,
	TEST_AUTO_MODE
} Airplane_Mode_Enum;

typedef enum{
	STATE_DECISION = 0,
	STABLE,
	TURN_LEFT,
	TURN_RIGHT,
	TRACK_LEFT,
	TRACK_RIGHT
} Control_State_Enum;

typedef struct 
{
	double u_Pitch_Getinto_Turnstate; // save the control signal u, when roll reach the H_RIGHT/LEFT_SETPOINT
	double Yaw_Before_Turn;
	double Upper_Current_Result_Thres_Pitch;
	double Roll_Effect;
} Temporary_Important_Parameters_Struct;

typedef enum
{
	U_PITCH_GETINTO_TURNSTATE,
	YAW_BEFORE_TURN,
	UPPER_CURRENT_RESULT_THRES_PITCH,
	ROLL_EFFECT
} Temporary_Important_Parameters_Enum;

void PWM_Init(void);
void PWM_DutySet(float Duty_Cycle, uint8_t ui8_Channel);
void Control_Mode_Set(Airplane_Mode_Enum ui8_AP_Mode);
void Mode_Select(void);
void Airplane_Control(void);
void Control_Params_Init(void);
	
#endif /* CONTROL_H */
