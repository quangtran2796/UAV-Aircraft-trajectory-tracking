#ifndef RF_H
#define RF_H

#include "include.h"

typedef enum{
	RIGHT = 'R',
	LEFT = 'L',
	STRAIGHT = 'S',
	INCREASE = 'I',
	DESCREASE = 'D'
} Fight_Dir;

void RF_config(void);
void RF_GainData(char *Data, uint8_t Size);

#endif