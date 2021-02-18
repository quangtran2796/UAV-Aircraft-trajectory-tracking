#ifndef FSMC_H
#define FSMC_H

#include "include.h"

#define PW_BASE_ADDR 	((uint32_t) 0x60000020)

typedef enum{
	AILERON_PW = 0,
	ELEVATOR_PW = 2,
	RUDDER_PW = 4,
	THROTTLE_PW = 6
} PW_Type;

void FSMC_Init(void);
uint8_t FSMC_GetPulseWidth(PW_Type PulseWing);

#endif



