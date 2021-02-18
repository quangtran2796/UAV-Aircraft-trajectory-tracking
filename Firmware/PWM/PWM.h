#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "include.h"

typedef enum {
	AILERON = (uint16_t) GPIO_Pin_6,
	ELEVATOR = (uint16_t) GPIO_Pin_7,
	RUDDER = (uint16_t) GPIO_Pin_0,
	THROTTLE = (uint16_t) GPIO_Pin_1,
} PulseOut_Type;
	 
void TIM_PWM_Config(void);
void TIM_PWM_SetPulseWidth(uint16_t ui16_Pulse_Width, PulseOut_Type Pulse_Out);	 
	 
#ifdef __cplusplus
}
#endif

#endif
