#ifndef DEFINE_H
#define DEFINE_H

/* PID files */
#define PID_METHOD1
#define NO_CHANGE 			((float) 0xFFFFFFFF)
#define ERROR_THRES			((float) 0.1)			// Variation within ERROR_THRES will not effect.
#define RESULT_THRES_ROLL		((float) 0.6)			// <1
#define UPPER_ROLL_ERR_THRES		((float) 25.0)
#define LOWER_ROLL_ERR_THRES		((float) 15.0)
#define UPPER_PITCH_ERR_THRES		((float) 20.0)
#define LOWER_PITCH_ERR_THRES		((float) 20.0)
#define	ROLL_PITCH_CORRELATION		((float) 0.2)			//((float) 0.5)
#define UPPER_RESULT_THRES_PITCH_NORMAL ((float) 0.2)
#define UPPER_RESULT_THRES_PITCH_TURN ((float) 0.15)	
#define LOWER_RESULT_THRES_PITCH ((float) -0.05)
/* Stanley files */
#define PI 					((float) 180.0)
#define MAX_TRA_POINT 		100
#define RAD2DEG				((double) 180.0/3.1415926535)
#define UPDATE_DISTANCE		((float) 40.0)
#define K_SL				0.4
/* PWM files */
#define TICK_PERIOD 		400000					// unit: Hz, period for single count.
#define RELOAD_PERIOD 		8000					// period for pulse, Reload Cycle = RELOAD_PERIOD / TICK_PERIOD.
#define AILERON_PINSOURCE 	(uint8_t)GPIO_PinSource6
#define ELEVATOR_PINSOURCE 	(uint8_t)GPIO_PinSource7
#define RUDDER_PINSOURCE 	(uint8_t)GPIO_PinSource0
#define THROTTLE_PINSOURCE 	(uint8_t)GPIO_PinSource1
#define PWM_TIMERBASE 		TIM3
#define PWM_CLOCK 			RCC_APB1Periph_TIM3
#define GPIO_AF_PWM 		GPIO_AF_TIM3
/* IMU_GPS files */
#define KNOT2M				((float) 1852.0)		// 1 knot = 1852 m
#define KPH2MPS				((float) 5.0/18.0)		// 1 k/m = 5/18 m/s
#define LATDEG2M			((float) 110567)		// 1 degree Latitude = 110.567 km at the Equator
#define LONDEG2M			((float) 111321)		// 1 degree Longtitude = 111.321 km at the Equator
/* RF files*/
#define BUFFTX_SIZE 		220
#define TRANS_PEDRIOD		100						// milisecond
#define H_RIGHT_SETPOINT	25.0 // Official setpoint of turning right
#define H_LEFT_SETPOINT		-15.0
#define L_RIGHT_SETPOINT	17.0
#define L_LEFT_SETPOINT		-4.0
#define STRAIGHT_SETPOINT	5.0
/* UTM files*/
#define PI_RAD				((double) 3.1415926535898)
/* General definition*/
#define TRAJECT_SIZE 		12
#define MIN_SPEED			7.5
#define PITCH_SETPOINT		((float) 15.0)
#define LOWER_PW			((float) 50.0)
#define UPPER_PW			((float) 250.0)
#define KP_ROLL				((double) 0.005)	//((double) 0.005)									//((double) 0.01)				//((double) 0.035)					//((double) 0.035)
#define KI_ROLL				((double) 0.0015)//((double) 0.0025)									//((double) 0.0005)					//((double) 0.01)					//((double) 0.018)
#define KD_ROLL				((double) 0.000)//((double) 0.0005)									//((double) 0.001)
#define KP_PITCH			((double) 0.015)//((double) 0.02)					//((double) 0.01)					//((double) 0.03)
#define KI_PITCH			((double) 0.0001)//((double) 0.001)				//((double) 0.008)					//((double) 0.01)
#define KD_PITCH			((double) 0.001)//((double) 0.005)
#define OMEGA_PITCH		((double) 0.0)					//((double) 0.1)
#define OMEGA_ROLL		((double) 0.0)					//((double) 0.1)
#define YAW_SETPOINT	((double) 0.0)
#define RIGHT_YAW_SETPOINT ((double) 5.0)
#define TURNING_SETPOINT	((double) 20.0) // Test goc queo
#define ROLL_ERROR_THRESHOLD ((double) 10.0) // need to consider again, currently this para ist dismissed
#define STRAIGHT_TURNING_THRES ((double) 90.0)
#define ACCEPTABLE_THRESHOLD	0.5
#define STABLE_DEADBAND		2.0 // have to modify during experience
#define TRACK_DEADBAND		1.0 // have to modify during experience
#define TURN_DEADBAND		3.0 // have to modify during experience
#define SEGMENT_SETPOINT_DEABAND 5.0 
#define MAX_NUMBER_SEGMENT_SETPOINT 5 
#define YAW_ERROR_STABLE_RANGE 10
#define YAW_ERROR_TRACK_RANGE 60
#define TURN_ANGLE 			25
#endif
