#ifndef STANLEY_H
#define STANLEY_H

#include "include.h"
#include "math.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct{
	double Trajectory[MAX_TRA_POINT][2];
	uint16_t Size;
	double Slope[MAX_TRA_POINT];
	double Velocity;
	double K;
	double Coordinate[1][2];
	uint8_t Index;
	double Steering_Angle;
} Stanley_Param;

void Stanley_Init(double Trajectory[][2], uint16_t Size, double Start_Coordinate[][2], double Start_Angle, double K, double Velocity); // Call this function once before applying the algorithm
void Stanley_Algorithm(double fCoordinate[][2], double fSteer_Ang, double fVelocity);
void Stanley_Test_Sample_Trajectory(float CoordinateX, float CoordinateY);
double Stanley_Get_Steer_Ang(void);
void Stanley_Set_Size(uint16_t Size);
uint8_t Stanley_GetIndex(void);

#endif
