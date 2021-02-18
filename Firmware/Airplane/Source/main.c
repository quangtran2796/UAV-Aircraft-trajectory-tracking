#include "include.h"

int main(void)
{

	TIM_PWM_Config();
	IMU_GPS_Init();
	Control_Params_Init();
	Control_Mode_Set(MANUAL_MODE); // Nho doi lai MODE truoc khi bay
	GPIO_Config();
	FSMC_Init();
	RF_config();
//	TIM_PWM_SetPulseWidth(600, AILERON);
//	TIM_PWM_SetPulseWidth(600, ELEVATOR);
//	TIM_PWM_SetPulseWidth(600, RUDDER);
//	TIM_PWM_SetPulseWidth(400, THROTTLE);
	while(1)
	{
		Airplane_Control();
	}
}
