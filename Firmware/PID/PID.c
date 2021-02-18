#include "PID.h"
#include <math.h>

uint16_t PID_Calculate_Roll(PID_TypeDef *PID_Type, double Angle_Feeback, double Rate_Feedback)
{
	double a, b, c, Angle_error;
#ifdef PID_METHOD1
	/* Control angle by applying PID controller to its "Rate":
	 *	Desired_Angle ----->(+-)------------------->(+-)------>| PID_Controller |------->(Steering_Angle)
	 *											 /|\                     /|\
	 *	Measured_Angle----------------------------|						  |
	 *																	  |
	 *	Angle_Rate------------| Omega >-----------------------------------|
	 */
	
	/* Note: Calculate below parameters based on the concept not holding desired error */
	Angle_error = PID_Type->Setpoint - Angle_Feeback;
	PID_Type->Error = Angle_error - Rate_Feedback*PID_Type->Omega;
	if ((PID_Type->Error < ERROR_THRES) && (PID_Type->Error > -ERROR_THRES))
	{
		PID_Type->Error = 0.0;
		//PID_Type->Result = 0.0;
		//PID_Type->Result_1 = 0.0;
	}
#endif
#ifdef PID_METHOD2
	/*	Desired_Angle ----->(+-)------>| PID_Controller |------->(Steering_Angle)
	 *											 /|\                    
	 *	Measured_Angle----------------------------| 				    					
	 */
	PID_Type->Error = PID_Type->Setpoint - Angle_Feeback;

//	if (PID_Type->Kp == 0.015)
//	{
	if ((PID_Type->Error < ERROR_THRES) && (PID_Type->Error > -ERROR_THRES))
	{
		PID_Type->Error = 0.0;
		//PID_Type->Result = 0.0;
		//PID_Type->Result_1 = 0.0;
	}
	if ((PID_Type->Error > UPPER_ROLL_ERR_THRES) || (PID_Type->Error < -UPPER_ROLL_ERR_THRES))
		PID_Set_Param(PID_Type, NO_CHANGE, 4*KP_ROLL, 4*KI_ROLL, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
	else if ((PID_Type->Error > LOWER_ROLL_ERR_THRES) || (PID_Type->Error < -LOWER_ROLL_ERR_THRES))
		PID_Set_Param(PID_Type, NO_CHANGE, 2*KP_ROLL, 2*KI_ROLL, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
	else
		PID_Set_Param(PID_Type, NO_CHANGE, KP_ROLL, KI_ROLL, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
#endif	
//	}
	a = (PID_Type->Kp + PID_Type->Ki*PID_Type->Ts/2 + PID_Type->Kd/PID_Type->Ts);
	b = (-PID_Type->Kp + PID_Type->Ki*PID_Type->Ts/2 - 2*PID_Type->Kd/PID_Type->Ts);
	c = PID_Type->Kd/PID_Type->Ts;
	
	PID_Type->Result = PID_Type->Result_1 + a*PID_Type->Error + b*PID_Type->Error_1 + c*PID_Type->Error_2;
	
	if (PID_Type->Result >= RESULT_THRES_ROLL)
		PID_Type->Result = RESULT_THRES_ROLL;
	else if (PID_Type->Result <= -RESULT_THRES_ROLL)
		PID_Type->Result = -RESULT_THRES_ROLL;
	
	PID_Type->Result_1 = PID_Type->Result;
	PID_Type->Error_1 = PID_Type->Error;
	PID_Type->Error_2 = PID_Type->Error_1;
	/* Calculate PWM value and assign to PID_Type->PWM*/	
	//PID_Type->PWM = (uint16_t) ((PID_Type->Result + 1.0)/2.0*(800.0 - 400.0) + 400.0);
	PID_Type->PWM = (uint16_t) ((PID_Type->Result + 1.0)/2.0*(1000.0 - 200.0) + 200.0);
	return PID_Type->PWM;
}
uint16_t PID_Calculate_Pitch(PID_TypeDef *PID_Type, double Angle_Feeback, double Rate_Feedback, double Coefficient, float High_Thres, float Low_Thres)
{
	double a, b, c, Angle_error;
#ifdef PID_METHOD1
	/* Control angle by applying PID controller to its "Rate":
	 *  Roll_Error-----| Correlation >---------------|
	 *	                                             |
	 *                                              \|/
	 *	Desired_Angle ----->(+-)------------------>(++-)------>| PID_Controller |------->(Steering_Angle)
	 *											 /|\                     /|\
	 *	Measured_Angle--------| 				    					|
	 *																	    					|
	 *	Angle_Rate------------| Omega >---------------|
	 */
	
	/* Note: Calculate below parameters based on the concept not holding desired error */
	Angle_error = PID_Type->Setpoint - Angle_Feeback + Coefficient; // Note: Coefficient = Roll_error * ROLL_PITCH_CORRELATION;
	PID_Type->Error = Angle_error - Rate_Feedback*PID_Type->Omega;
	if ((PID_Type->Error < ERROR_THRES) && (PID_Type->Error > -ERROR_THRES))
	{
		PID_Type->Error = 0.0;
		//PID_Type->Result = 0.0;
		//PID_Type->Result_1 = 0.0;
	}
	if ((PID_Type->Error > LOWER_PITCH_ERR_THRES) || (PID_Type->Error < -LOWER_PITCH_ERR_THRES))
		PID_Set_Param(PID_Type, NO_CHANGE, 1.5*KP_PITCH, 1.5*KI_PITCH, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
	else
		PID_Set_Param(PID_Type, NO_CHANGE, KP_PITCH, KI_PITCH, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
#endif
#ifdef PID_METHOD2
	/*	Desired_Angle ----->(+-)------>| PID_Controller |------->(Steering_Angle)
	 *											 /|\                    
	 *	Measured_Angle----------------------------| 				    					
	 */
	PID_Type->Error = PID_Type->Setpoint - Angle_Feeback;

//	if (PID_Type->Kp == 0.015)
//	{
	if ((PID_Type->Error < ERROR_THRES) && (PID_Type->Error > -ERROR_THRES))
	{
		PID_Type->Error = 0.0;
		//PID_Type->Result = 0.0;
		//PID_Type->Result_1 = 0.0;
	}
	if ((PID_Type->Error > LOWER_PITCH_ERR_THRES) || (PID_Type->Error < -LOWER_PITCH_ERR_THRES))
		PID_Set_Param(PID_Type, NO_CHANGE, 1.5*KP_PITCH, 1.5*KI_PITCH, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
	else
		PID_Set_Param(PID_Type, NO_CHANGE, KP_PITCH, KI_PITCH, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE);
#endif	
//	}
	a = (PID_Type->Kp + PID_Type->Ki*PID_Type->Ts/2 + PID_Type->Kd/PID_Type->Ts);
	b = (-PID_Type->Kp + PID_Type->Ki*PID_Type->Ts/2 - 2*PID_Type->Kd/PID_Type->Ts);
	c = PID_Type->Kd/PID_Type->Ts;
	
	PID_Type->Result = PID_Type->Result_1 + a*PID_Type->Error + b*PID_Type->Error_1 + c*PID_Type->Error_2;
	if (PID_Type->Result >= High_Thres)
		PID_Type->Result = High_Thres;
	else if (PID_Type->Result <= Low_Thres)
		PID_Type->Result = Low_Thres;
	
	PID_Type->Result_1 = PID_Type->Result;
	PID_Type->Error_1 = PID_Type->Error;
	PID_Type->Error_2 = PID_Type->Error_1;
	/* Calculate PWM value and assign to PID_Type->PWM*/	
	//PID_Type->PWM = (uint16_t) ((PID_Type->Result + 1.0)/2.0*(800.0 - 400.0) + 400.0);
	PID_Type->PWM = (uint16_t) ((PID_Type->Result + 1.0)/2.0*(1000.0 - 200.0) + 200.0);
	return PID_Type->PWM;
}
void PID_Reset_Param(PID_TypeDef *PID_Type)
{
//	PID_Type->Kp = (double) 0.0;
//	PID_Type->Kd = (double) 0.0;
//	PID_Type->Ki = (double) 0.0;
//	PID_Type->Ts = (double) 0.0;
	PID_Type->Error = (double) 0.0;
	PID_Type->Error_1 = (double) 0.0;
	PID_Type->Error_2 = (double) 0.0;
//	PID_Type->Setpoint = (double) 0.0;
	PID_Type->Result = (double) 0.0;
	PID_Type->Result_1 = (double) 0.0;
}
void PID_Set_Param(PID_TypeDef *PID_Type, uint8_t Name, double Kp, double Ki, double Kd, double Setpoint, double Result_1, double Omega, double Ts) 
{
	//if (Name != NO_CHANGE) PID_Type->Name = Name;
	if (Kp != NO_CHANGE) PID_Type->Kp = Kp;
	if (Ki != NO_CHANGE) PID_Type->Ki = Ki;
	if (Kd != NO_CHANGE) PID_Type->Kd = Kd;
	if (Setpoint != NO_CHANGE) PID_Type->Setpoint = Setpoint;
	if (Result_1 != NO_CHANGE) PID_Type->Result_1 = Result_1;
	if (Omega != NO_CHANGE) PID_Type->Omega = Omega;
	if (Ts != NO_CHANGE) PID_Type->Ts = Ts;
}
void PID_Calib_Stable_Angle(PID_TypeDef *PID_Type, double Stable_Angle)
{
	PID_Type->Stable_Angle = Stable_Angle;
}