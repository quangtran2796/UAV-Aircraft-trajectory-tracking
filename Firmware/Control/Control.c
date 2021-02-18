#include "Control.h"
#include <stdarg.h>

Airplane_Mode_Enum AP_Mode = MANUAL_MODE;
Control_State_Enum State = STABLE, Previous_State = STABLE, Command_State = STABLE; // firstly, Airplane must be stable when change from Manual to Auto.
PID_TypeDef PID_Roll;
PID_TypeDef PID_Pitch;
PID_TypeDef PID_Yaw;
PID_TypeDef PID_Throttle;

/* A temporary trajectory for test*/
//double Trajectory[TRAJECT_SIZE][2] = {{10.773333333, 106.7853363333}, 
//									{10.77261266666, 106.7846653333},
//									{10.77205533333, 106.7852593333},
//									{10.772592, 106.78592916666}
//									};
double Trajectory[TRAJECT_SIZE][2] = {{10.76957566667, 106.76362516667}, // Toa do san Cay trung ca
									{10.77067716667, 106.7626541666},
									{10.769875, 106.76166},
									{10.76866083333, 106.7627353333},
									{10.76957566667, 106.76362516667},
									{10.77067716667, 106.7626541666},
									{10.769875, 106.76166},
									{10.76866083333, 106.7627353333},
									{10.76957566667, 106.76362516667},
									{10.77067716667, 106.7626541666},
									{10.769875, 106.76166},
									{10.76866083333, 106.7627353333}
									};

//double Trajectory[TRAJECT_SIZE][2] = {{10.76956083, 106.76082533}, 
//									//{10.76965467, 106.76072367}, 
//									{10.7697915, 106.76064017},
//									//{10.76995417, 106.76043933},
//									{10.76953217, 106.76023917},
//									{10.76918233, 106.760025},
//									{10.76900833, 106.7602135},
//									{10.7693725, 106.76068767}
//									};
//double Trajectory[TRAJECT_SIZE][2] = {{10.7701083, 106.760736}, 
//									//{10.76965467, 106.76072367}, 
//									{10.7690345, 106.759541},
//									//{10.76995417, 106.76043933},
//									{10.76752783, 106.7609495},
//									{10.76882667, 106.762261}
//									};
uint8_t ui8_Size = TRAJECT_SIZE;

float Setpoint = 0.0, Max_response, Yaw2East, temp_roll, temp_pitch;
uint32_t tick_start = 0, tick_start_1 = 0;
uint16_t Pulse = 600;
uint8_t count = 0;
uint8_t countrf = 0;
double Setpoint_Turn = STRAIGHT_SETPOINT;
double Yaw_Setpoint, Yaw_Error, Steer, Yaw_Error_fabs;
bool return_flag = false;										
bool bChange_Mode, bInitialized = false;
uint8_t index_1 = 0, index_2 = 0;
double u_Pitch;	
double Segment_Setpoint_Array[MAX_NUMBER_SEGMENT_SETPOINT];
uint8_t ui8_Num_Segment_Setpoint = 0, ui8_Segment_Setpoint_Retain = 0;	
Temporary_Important_Parameters_Struct Temporary_Important_Parameters;	
float Yaw_Turn_Error = 0;
																		
void AC_AutoMode(void);
void Control_Roll(void);
void Control_Pitch(void);
void Control_Yaw(void);
void Control_Successful_Stable_Test(void);
void Control_Main_Data_Transfer(void);
void Control_Stanley_Calculation(void);
void Control_State_Update();
float Control_LowpassFilter(double Current_SP, double Desired_SP, double Step);
void Control_State_Machine(void);
void Control_State_Update(Control_State_Enum CS_State);
void Control_Calib_Stable_Angle(void);
void Control_Prepare_Ctvalue_Maunual2Auto(void);
void Control_Init_Standley_Algorithm(void);
uint8_t Control_Setpoint_Segment_Prepare_Data_Test(double* Setpoint_Segment_Array, double Setpoint_1, double Setpoint_2, double Setpoint_3, uint8_t Num_Setpoint);
void Control_Setpoint_Setment_Prepare_State(Control_State_Enum Current_State,Control_State_Enum Pre_Sate);
double Control_Segment_Setpoint(double* Setpoint_Segment_Array, uint8_t ui8_Segment_Length, uint8_t* ui8_Index_Retain);
void Control_Save_Important_Parameters(Temporary_Important_Parameters_Enum Para_Name, double Para_Value);
double Control_Get_Important_Parameters(Temporary_Important_Parameters_Enum Para_Name);
bool Control_Turn_Definite_Angle(double Threshold_Angle);
void Control_State_Distribute(bool bInvert_Flag);
void Control_PID(void);
bool Control_Turn_Definite_Angle_Heading(double Threshold_Angle);

void Airplane_Control(void)
{
 	char Data1[25] = "AUTO MODE  xxx.x  xxx.x";
	char Data2[3] = "fff";
	char Data3[3] = "zzz";
	Data1[23] = 0x0d;
	Data1[24] = 0x0a;
	
	switch (AP_Mode)
	{
		case MANUAL_MODE:
			if (SysTick_IsTimeout(tick_start, 300))
			{
				IMU_GPS_Data_Process();
				RF_GainData(Data3, 3);
				tick_start = SysTick_GetTick();
			}
			if (GPIO_Trigger_Read())
			{
				Control_Mode_Set(CALIB_MODE);
				RF_GainData(Data2, 3);
				
			}
			break;
			
		case CALIB_MODE:		
			Control_Calib_Stable_Angle();
			Control_Prepare_Ctvalue_Maunual2Auto();
			Control_Init_Standley_Algorithm();
			//if (IMU_GPS_IsCoordinateAvailable()) 
			{
				Control_Mode_Set(AUTO_MODE);
				
				/* Transfer data to SDCard */
				temp_roll = IMU_GPS_GetRoll();
				if (temp_roll < 0.0)
					Data1[10] = '-';
				else Data1[10] = ' ';
				temp_roll = fabs(temp_roll);
				Data1[11] = ((uint16_t) (temp_roll * 10.0)) / 1000 + '0';
				Data1[12] = (((uint16_t) (temp_roll * 10.0)) % 1000) / 100 + '0';
				Data1[13] = ((((uint16_t) (temp_roll * 10.0)) % 1000) % 100) / 10 + '0';
				Data1[15] = ((((uint16_t) (temp_roll * 10.0)) % 1000) % 100) % 10 + '0';
				temp_pitch = IMU_GPS_GetPitch();
				if (temp_pitch < 0.0)
					Data1[17] = '-';
				else Data1[17] = ' ';
				temp_pitch = fabs(temp_pitch);
				Data1[18] = ((uint16_t) (temp_pitch * 10.0)) / 1000 + '0';
				Data1[19] = (((uint16_t) (temp_pitch * 10.0)) % 1000) / 100 + '0';
				Data1[20] = ((((uint16_t) (temp_pitch * 10.0)) % 1000) % 100) / 10 + '0';
				Data1[22] = ((((uint16_t) (temp_pitch * 10.0)) % 1000) % 100) % 10 + '0';
				RF_GainData(Data1, 25);
				/* Change Pitch Setpoint when switching into AUTO */
				PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, -IMU_GPS_GetPitch(), NO_CHANGE, NO_CHANGE, NO_CHANGE);
			}
			break;
		case AUTO_MODE:
		if (SysTick_IsTimeout(tick_start, 20))
			{
				/* Setpoint PWM_Roll PWM_Pitch Roll Pitch Yaw*/
				IMU_GPS_Data_Process();
				/* Decide the control state */
				//AC_AutoMode();
				Yaw2East = IMU_GPS_Yaw_Heading();
				Control_State_Machine();
				
				Control_Main_Data_Transfer();
				tick_start = SysTick_GetTick();	
			}
			if (!GPIO_Trigger_Read())
			{
				
				Control_Mode_Set(MANUAL_MODE);
				State = STABLE;
				Command_State = STABLE;
				Previous_State = STABLE;
				PID_Reset_Param(&PID_Roll);
				PID_Reset_Param(&PID_Pitch);
				RF_GainData(Data3, 3);
			}
			
			break;
		case TEST_CALIB_MODE:
		{
			/* Initial calculations of Stanley algorithm */
			{
				double Coordinate[1][2];
				Coordinate[0][0] = IMU_GPS_GetLatitude();
				Coordinate[0][1] = IMU_GPS_GetLongtitude();
				//Stanley_Init(Trajectory, ui8_Size, Coordinate, IMU_GPS_GetYaw(), K, (IMU_GPS_GetSpeed()*KNOT2M));
				Pulse = 600;
			}
			/* Calibrate the stable angles */
			IMU_GPS_Data_Process();
			PID_Calib_Stable_Angle(&PID_Roll, IMU_GPS_GetRoll());
			PID_Calib_Stable_Angle(&PID_Pitch, IMU_GPS_GetPitch());
			//PID_Calib_Stable_Angle(&PID_Yaw, IMU_GPS_GetYaw());
			/* Change into AUTO Mode */
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, PID_Roll.Stable_Angle, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			PID_Set_Param(&PID_Pitch,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, PID_Pitch.Stable_Angle, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			Control_Mode_Set(TEST_AUTO_MODE);
//			if (SysTick_IsTimeout(tick_start, 200))
//			{
//				Stanley_Test_Sample_Trajectory(IMU_GPS_GetLatitude(), IMU_GPS_GetLongtitude());
//				tick_start = SysTick_GetTick();
//			}
		}
			break;
		case TEST_AUTO_MODE:
		{
			if (SysTick_IsTimeout(tick_start, 20))
			{
				IMU_GPS_Data_Process();
				AC_AutoMode();
				tick_start = SysTick_GetTick();
			}
		}
			break;
		default:
			break;
	}
}
void PWM_Init(void)
{
	
}

void PWM_DutySet(float Duty_Cycle, uint8_t ui8_Channel)
{
}
void AC_AutoMode(void)
{
	Control_Roll();
	Control_Pitch();
	Control_Yaw();
}
void Control_Roll(void)
{
	//PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, Setpoint, NO_CHANGE, NO_CHANGE);
	//TIM_PWM_SetPulseWidth(PID_Calculate_Roll(&PID_Roll, IMU_GPS_GetRoll(), IMU_GPS_GetVx()), AILERON);
}
void Control_Pitch(void)
{
	//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, Setpoint, NO_CHANGE, NO_CHANGE);
	double RollEffect, Roll_Error;
	Roll_Error = fabs(IMU_GPS_GetRoll() - STRAIGHT_SETPOINT);
	if ((FSMC_GetPulseWidth(THROTTLE_PW) > 150) && (Roll_Error > ROLL_ERROR_THRESHOLD))
	{
		RollEffect = fabs(2 * ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
		TIM_PWM_SetPulseWidth(PID_Calculate_Pitch(&PID_Pitch, -IMU_GPS_GetPitch(), IMU_GPS_GetVy(), RollEffect, UPPER_RESULT_THRES_PITCH_TURN, LOWER_RESULT_THRES_PITCH), ELEVATOR);
	}
	else
	{
		RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
		TIM_PWM_SetPulseWidth(PID_Calculate_Pitch(&PID_Pitch, -IMU_GPS_GetPitch(), IMU_GPS_GetVy(), RollEffect, UPPER_RESULT_THRES_PITCH_NORMAL, LOWER_RESULT_THRES_PITCH), ELEVATOR);
	}
}
void Control_Yaw(void)
{
	/* Calculate steering angles */
	Control_Stanley_Calculation();
	//Control_Success_Stable_Test();
}
void Control_Mode_Set(Airplane_Mode_Enum ui8_AP_Mode)
{
	AP_Mode = ui8_AP_Mode;
}
void Mode_Select(void)
{
	switch (GPIO_Switch_Read())
	{
		case MODE1:
			// Control_Mode_Set(MANUAL_MODE);
			GPIO_LED_On(LED_RED);
			break;
		case MODE2:
			Control_Mode_Set(TEST_CALIB_MODE);
			GPIO_LED_Blink(LED_RED, 500);
			break;
		case MODE3:
			Control_Mode_Set(TEST_AUTO_MODE);
			GPIO_LED_Blink(LED_RED, 200);
			break;
		case MODE4: /* RESET_MODE */
			/* If mode is in TEST_CALIB or TEST_AUTO, switch it to MODE4 before changing mode into Control
			 * including MANUAL -> CALIB -> AUTO
			 * After that, switch to MODE1 to operate */
			Control_Mode_Set(MANUAL_MODE);
			Stanley_Set_Size(0);
			GPIO_LED_Off(LED_RED);
			break;
		default:
			break;
	}
}

void Control_Params_Init(void)
{
	PID_Set_Param(&PID_Roll, 1, KP_ROLL, KI_ROLL, KD_ROLL, 0, 0, OMEGA_ROLL, 0.02);
	PID_Set_Param(&PID_Pitch, 2, KP_PITCH, KI_PITCH, 0, 0, 0, OMEGA_PITCH, 0.02);
	TIM_PWM_SetPulseWidth(Pulse, RUDDER);
	Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_NORMAL);
	//PID_Set_Param(&PID_Yaw, 3, 0, 0, 0, 0, 0, 0, 0.02);
}
void Control_Successful_Stable_Test(void)
{
	double Current_Yaw;
	if (FSMC_GetPulseWidth(THROTTLE_PW) > 150)
	{
//		return_flag = false;
		if (index_1 == 0)
		{
			Yaw_Setpoint = IMU_GPS_GetYaw();			// Lay so lieu lan dau chuyen MODE sang bay cong
			u_Pitch = PID_Pitch.Result; // Giu lai gia tri de luu vao Result_1 khi da bay thang
			index_1++;
		}
		else											// Nhung lan sau se lay gia tri goc de quyet dinh chuyen ve bay thang
		{
			Current_Yaw = IMU_GPS_GetYaw();
			if ((Yaw_Setpoint >= 90.0) && (Yaw_Setpoint <= 180.0)) // Khi goc dat ban dau tu 90 den 180 thi neu 
			{														// goc hien tai trong khoang -90 den -180 thi cong them 360
				if ((Current_Yaw <= -90.0) && (Current_Yaw >= -180.0))
				{
					Current_Yaw += 360.0;
				}
			}
			else if ((Yaw_Setpoint <= -90.0) && (Yaw_Setpoint >= -180.0)) // Tuong tu nhu tren
			{
				if ((Current_Yaw >= 90.0) && (Current_Yaw <= 180.0))
				{
					Current_Yaw -= 360.0;
				}
			}
			Yaw_Error = fabs(Yaw_Setpoint - Current_Yaw);
			if (Yaw_Error >= STRAIGHT_TURNING_THRES) // neu sai so vuot qua cho phep thi bat flag bay thang
			{
				return_flag = true;
			}
		}
		if (return_flag) // Flag duoc bat thi tra gia tri goc ve 0
		{
			if (Setpoint_Turn > STRAIGHT_SETPOINT)
			{
				if (count < 1)
				{
					count += 1; // 2 lan dem tru mot lan
				}
				else
				{
					count = 0;
					Setpoint_Turn -= 0.5;
					PID_Set_Param(&PID_Roll,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Setpoint_Turn, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				}
			}
			else // khi da dat gia tri STRAIGHT thi dung tru
			{
				PID_Set_Param(&PID_Roll,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, STRAIGHT_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				if (index_2 == 0)
				{
					index_2++;
					PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, u_Pitch, NO_CHANGE, NO_CHANGE);
				}
			}
		}
		else // Khi ko co flag thi dang cong goc de bay cong
		{
			if (Setpoint_Turn < TURNING_SETPOINT)
			{
				if (count < 1)
				{
					count += 1;
				}
				else
				{
					count = 0;
					Setpoint_Turn += 0.5;
					PID_Set_Param(&PID_Roll,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Setpoint_Turn, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				}
			}
			else
				PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, TURNING_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
		}
	}
	else // Khi bat Switch so 5 ve
	{
		index_1 = 0; index_2 = 0;// Xoa bien cho lan chay tiep theo
		return_flag = false;
		if (Setpoint_Turn > STRAIGHT_SETPOINT)
		{
			if (count < 1)
			{
				count += 1;
			}
			else
			{
				count = 0;
				Setpoint_Turn -= 0.2;
				PID_Set_Param(&PID_Roll,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Setpoint_Turn, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			}
		}
		else
			PID_Set_Param(&PID_Roll,NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, STRAIGHT_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
	}
}
void Control_Stanley_Calculation(void)
{
	if (IMU_GPS_IsCoordinateAvailable() && (bInitialized))
//	if (bInitialized)
	{
		uint8_t j[1][2];
		double dCoordinate[1][2], Speed, dCoordinUTM[1][2];	
//		dCoordinate[0][0] = 10.769676;		
//		dCoordinate[0][1] = 106.657495;
		Speed = IMU_GPS_GetSpeed();
		dCoordinate[0][0] = IMU_GPS_GetLatitude(); 
		dCoordinate[0][1] = IMU_GPS_GetLongtitude();
		//Speed = Test_Velocity;
		/* Pass Coordiante, Yaw and Speed to Stanley Algorithm, */
		if (Speed <= MIN_SPEED)
				Speed = MIN_SPEED;
		UTM_Deg2utm(dCoordinate, dCoordinUTM, j, 1);
		// da sua thanh yaw heading
		Stanley_Algorithm(dCoordinUTM, IMU_GPS_Yaw_Heading(), Speed);
		//PID_Set_Param(&PID_Yaw, NO_CHANGE, NO_CHANGE, NO_CHANGE, Steer, NO_CHANGE, NO_CHANGE);
		//TIM_PWM_SetPulseWidth(PID_Calculate(&PID_Yaw, IMU_GPS_GetYaw(), IMU_GPS_GetVz(), Max_response), RUDDER);
	}
	else
		TIM_PWM_SetPulseWidth(600, RUDDER);
}
/**
  * @brief  This function transfer data to SDCard in Auto_mode.
  */
void Control_Main_Data_Transfer(void)
{
	char Data[84] = "xxx.x  xxx  xxx  xxx.x  xxx.x  xxx.x xxx.x xxx.x xxxxxxxxxx xxxxxxxxxxx xxxx.x x x";
	float  temp_yaw, temp_setpoint, temp_heading, temp_steer;
	char temp_lat[10], temp_lon[11], temp_alt[6];
	uint8_t i;
	if (countrf >= 10)
	{
		temp_setpoint = PID_Roll.Setpoint;
		if (temp_setpoint < 0.0)
			Data[0] = '-';
		else Data[0] = ' ';
		temp_setpoint = fabs(temp_setpoint);
		Data[1] = ((uint16_t) (temp_setpoint*10.0)) / 100 + '0';
		Data[2] = (((uint16_t) (temp_setpoint*10.0)) % 100) / 10 + '0';
		Data[4] = (((uint16_t) (temp_setpoint*10.0)) % 100) % 10 + '0';
		Data[7] = PID_Roll.PWM / 100 + '0';
		Data[8] = (PID_Roll.PWM % 100) / 10 + '0';
		Data[9] = (PID_Roll.PWM % 100) % 10 + '0';
		Data[12] = PID_Pitch.PWM / 100 + '0';
		Data[13] = (PID_Pitch.PWM % 100) / 10 + '0';
		Data[14] = (PID_Pitch.PWM % 100) % 10 + '0';
		temp_roll = IMU_GPS_GetRoll();
		if (temp_roll < 0.0)
			Data[16] = '-';
		else Data[16] = ' ';
		temp_roll = fabs(temp_roll);
		Data[17] = ((uint16_t) (temp_roll * 10.0)) / 1000 + '0';
		Data[18] = (((uint16_t) (temp_roll * 10.0)) % 1000) / 100 + '0';
		Data[19] = ((((uint16_t) (temp_roll * 10.0)) % 1000) % 100) / 10 + '0';
		Data[21] = ((((uint16_t) (temp_roll * 10.0)) % 1000) % 100) % 10 + '0';
		temp_pitch = IMU_GPS_GetPitch();
		if (temp_pitch < 0.0)
			Data[23] = '-';
		else Data[23] = ' ';
		temp_pitch = fabs(temp_pitch);
		Data[24] = ((uint16_t) (temp_pitch * 10.0)) / 1000 + '0';
		Data[25] = (((uint16_t) (temp_pitch * 10.0)) % 1000) / 100 + '0';
		Data[26] = ((((uint16_t) (temp_pitch * 10.0)) % 1000) % 100) / 10 + '0';
		Data[28] = ((((uint16_t) (temp_pitch * 10.0)) % 1000) % 100) % 10 + '0';
		temp_yaw = IMU_GPS_GetYaw();
		if (temp_yaw < 0.0)
			Data[30] = '-';
		else Data[30] = ' ';
		temp_yaw = fabs(temp_yaw);
		Data[31] = ((uint16_t) (temp_yaw * 10.0)) / 1000 + '0';
		Data[32] = (((uint16_t) (temp_yaw * 10.0)) % 1000) / 100 + '0';
		Data[33] = ((((uint16_t) (temp_yaw * 10.0)) % 1000) % 100) / 10 + '0';
		Data[35] = ((((uint16_t) (temp_yaw * 10.0)) % 1000) % 100) % 10 + '0';
		temp_heading = IMU_GPS_Yaw_Heading();
		Data[37] = ((uint16_t) (temp_heading * 10.0)) / 1000 + '0';
		Data[38] = (((uint16_t) (temp_heading * 10.0)) % 1000) / 100 + '0';
		Data[39] = ((((uint16_t) (temp_heading * 10.0)) % 1000) % 100) / 10 + '0';
		Data[41] = ((((uint16_t) (temp_heading * 10.0)) % 1000) % 100) % 10 + '0';
		temp_steer = Stanley_Get_Steer_Ang();
		Data[43] = ((uint16_t) (temp_steer * 10.0)) / 1000 + '0';
		Data[44] = (((uint16_t) (temp_steer * 10.0)) % 1000) / 100 + '0';
		Data[45] = ((((uint16_t) (temp_steer * 10.0)) % 1000) % 100) / 10 + '0';
		Data[47] = ((((uint16_t) (temp_steer * 10.0)) % 1000) % 100) % 10 + '0';
		IMU_GPS_Get_Lat_String(temp_lat);
		for (i = 0; i < 10; i++)
		{
			Data[49+i] = temp_lat[i];
		}
		IMU_GPS_Get_Lon_String(temp_lon);
		for (i = 0; i < 11; i++)
		{
			Data[60+i] = temp_lon[i];
		}
		IMU_GPS_Get_Alt_String(temp_alt);
		for (i = 0; i < 6; i++)
		{
			Data[72+i] = temp_alt[i];
		}
		Data[79] = State + '0';
		Data[81] = Stanley_GetIndex() + '0';
		
		Data[82] = 0x0d;
		Data[83] = 0x0a;
		RF_GainData(Data, 84);
		countrf = 0;
	}
	else
		countrf++;		
}
void Control_State_Update(Control_State_Enum CS_State)
{
	State = CS_State;
}
float Control_LowpassFilter(double Current_SP, double Desired_SP, double Step)
{
	/* Current Setpoint would be the temporary variable, which is added/ substracted at the previous time */
	if (Desired_SP < Current_SP)
	{
		Current_SP -= Step;
	}
	else if (Desired_SP > Current_SP)
	{
		Current_SP += Step;
	}
	else if (Desired_SP == Current_SP)
	{
		Current_SP = Desired_SP;
	}
	return (float)Current_SP;
}

/**
  * @brief  This function is the main control machine state.
  */
void Control_State_Machine(void)
{
	// Discuss again why argument type mu0ss be double
	double Roll_Error, RollEffect, U_R_Thres_Pitch;
	float Roll_Setpoint = 0, Pitch_Setpoint = 0;
	bool bSteer_Invert_Flag = false;
	switch (State)
	{
		case STATE_DECISION:		
			Control_Stanley_Calculation();
			Steer = Stanley_Get_Steer_Ang();	
			Yaw_Error = Steer - IMU_GPS_Yaw_Heading();
			Yaw_Error_fabs = fabs(Yaw_Error);
			if(fabs(Yaw_Error) > 180)
			{
				bSteer_Invert_Flag = true;
				Yaw_Error_fabs = 360 - Yaw_Error_fabs;
			}
			Control_State_Distribute(bSteer_Invert_Flag);
			bSteer_Invert_Flag = false;
			RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll()))); // this line used to update the lastest value RollEffect, which is needed to PID calculate
			Control_State_Update(Command_State);
			break;
		case STABLE:	
			if ((Previous_State == TRACK_LEFT) || (Previous_State == TRACK_RIGHT) || (Previous_State == STABLE))
			{
				Roll_Setpoint = STRAIGHT_SETPOINT;
				Pitch_Setpoint = PITCH_SETPOINT;
				RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
				
			}
			else if ((Previous_State == TURN_LEFT) || (Previous_State == TURN_RIGHT))
			{
				//Roll_Setpoint = Control_Segment_Setpoint(Segment_Setpoint_Array, ui8_Num_Segment_Setpoint, &ui8_Segment_Setpoint_Retain);
				Roll_Setpoint = Control_LowpassFilter(PID_Roll.Setpoint, STRAIGHT_SETPOINT, 0.25);
				Pitch_Setpoint = PITCH_SETPOINT;
				RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
			}
			if (fabs(STRAIGHT_SETPOINT - IMU_GPS_GetRoll()) < STABLE_DEADBAND)
			{				
				Previous_State = STABLE;
				Control_State_Update(STATE_DECISION);
			}
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Roll_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Pitch_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			break;
		case TURN_LEFT:
			if (Previous_State != TURN_LEFT)
			{
				//Roll_Setpoint = Control_Segment_Setpoint(Segment_Setpoint_Array, ui8_Num_Segment_Setpoint, &ui8_Segment_Setpoint_Retain);
				Roll_Setpoint = Control_LowpassFilter(PID_Roll.Setpoint, H_LEFT_SETPOINT, 0.25);
				Pitch_Setpoint = PITCH_SETPOINT;
				RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
			}
			else if (Previous_State == Command_State)
			{
				Roll_Setpoint = Control_LowpassFilter(PID_Roll.Setpoint, H_LEFT_SETPOINT, 0.25);
				Pitch_Setpoint = PITCH_SETPOINT;
				/* In this case, because of rotating with a large angle, the plane lose its height, 
				conpensating the height by increasing RollEffect and Result Threshold*/
				RollEffect = fabs(2 * ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
				
				//Change Pitch limmit range to turn a large angle
				Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_TURN);
				
				// When has reached TURN_ANGLE, immediately jump to STABLE 
//				if(Control_Turn_Definite_Angle_Heading(TURN_ANGLE))
//				{
//					Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_NORMAL);
//					Command_State = STABLE;
//					Control_State_Update(STABLE);
//				}
			}
			if ((fabs(H_LEFT_SETPOINT - IMU_GPS_GetRoll()) < TURN_DEADBAND) && Previous_State != Command_State) 
			{
				Previous_State = TURN_LEFT;
				// Get Pitch control signal in order to reset Pitch control signal when has already reached desired Yaw.  
				Control_Save_Important_Parameters(U_PITCH_GETINTO_TURNSTATE, PID_Pitch.Result);
			}
			
			if(Control_Turn_Definite_Angle_Heading(TURN_ANGLE))
			{
				Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_NORMAL);
				Command_State = STABLE;
				Control_State_Update(STABLE);
			}
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Roll_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Pitch_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			break;
		case TURN_RIGHT: 
			if (Previous_State != TURN_RIGHT)
			{
				//Roll_Setpoint = Control_Segment_Setpoint(Segment_Setpoint_Array, ui8_Num_Segment_Setpoint, &ui8_Segment_Setpoint_Retain);
				Roll_Setpoint = Control_LowpassFilter(PID_Roll.Setpoint, H_RIGHT_SETPOINT, 0.25);
				Pitch_Setpoint = PITCH_SETPOINT;
				RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
			}
			else if (Previous_State == Command_State)
			{
				Roll_Setpoint = Control_LowpassFilter(PID_Roll.Setpoint, H_RIGHT_SETPOINT, 0.25);
				Pitch_Setpoint = PITCH_SETPOINT;				
				/* In this case, because of rotating with a large angle, the plane lose its height, 
				conpensating the height by increasing RollEffect and Result Threshold*/
				RollEffect = fabs(2 * ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
				
				//Change Pitch limmit range to turn a large angle
				Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_TURN);
				
				// When has reached TURN_ANGLE, immediately jump to STABLE 
//				if(Control_Turn_Definite_Angle_Heading(TURN_ANGLE))
//				{
//					Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_NORMAL);
//					Command_State = STABLE;
//					Control_State_Update(STABLE);
//				}			
			}
			if ((fabs(H_RIGHT_SETPOINT - IMU_GPS_GetRoll()) < TURN_DEADBAND) && Previous_State != Command_State) 
			{
				Previous_State = TURN_RIGHT;
				// Get Pitch control signal in order to reset Pitch control signal when has already reached desired Yaw.  
				Control_Save_Important_Parameters(U_PITCH_GETINTO_TURNSTATE, PID_Pitch.Result);
			}
			
			if(Control_Turn_Definite_Angle_Heading(TURN_ANGLE))
			{
				Control_Save_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH, UPPER_RESULT_THRES_PITCH_NORMAL);
				Command_State = STABLE;
				Control_State_Update(STABLE);
			}
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Roll_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Pitch_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);		
			break;
		case TRACK_LEFT:
			//Only STABLE can access to TRACK_LEFT
			Roll_Setpoint = L_LEFT_SETPOINT;
			Pitch_Setpoint = PITCH_SETPOINT;
			RollEffect = fabs(1.25*ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
			if (fabs(L_LEFT_SETPOINT - IMU_GPS_GetRoll()) < TRACK_DEADBAND) 
				Previous_State = TRACK_LEFT;
			if(Previous_State == Command_State)
				Control_State_Update(STATE_DECISION);
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Roll_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Pitch_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);		
			break;
		case TRACK_RIGHT:
			//Only STABLE can access to TRACK_RIGHT
			Roll_Setpoint = L_RIGHT_SETPOINT;
			Pitch_Setpoint = PITCH_SETPOINT;
			RollEffect = fabs(ROLL_PITCH_CORRELATION * (STRAIGHT_SETPOINT - ((double) IMU_GPS_GetRoll())));
			if (fabs(L_RIGHT_SETPOINT - IMU_GPS_GetRoll()) < TRACK_DEADBAND) 
				Previous_State = TRACK_RIGHT;
			if(Previous_State == Command_State)
				Control_State_Update(STATE_DECISION);
			PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Roll_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);
			//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Pitch_Setpoint, NO_CHANGE, NO_CHANGE, NO_CHANGE);		
			break;
		default:
			break;
	}
	Control_Save_Important_Parameters(ROLL_EFFECT, RollEffect);
	Control_PID();
}

/**
  * 
@brief  This function calibrate the stable angles.
  */
void Control_Calib_Stable_Angle(void)
{
	IMU_GPS_Data_Process();
	PID_Calib_Stable_Angle(&PID_Roll, IMU_GPS_GetRoll());
	PID_Calib_Stable_Angle(&PID_Pitch, IMU_GPS_GetPitch());
	//PID_Calib_Stable_Angle(&PID_Yaw, IMU_GPS_GetYaw()); // this line follow above code in original
}

/**
  * @brief  This function pass the arguments for u(k-1), the current controlling values, to PID controller.
  */
void Control_Prepare_Ctvalue_Maunual2Auto(void)
{
	uint8_t ui8_RollPW, ui8_PitchPW;
	double dRoll_Result1, dPitch_Result1;
	ui8_RollPW = FSMC_GetPulseWidth(AILERON_PW);
	ui8_PitchPW = FSMC_GetPulseWidth(ELEVATOR_PW);
	dRoll_Result1 = (ui8_RollPW - LOWER_PW)/(UPPER_PW - LOWER_PW)*2.0 - 1.0; /* Scale the value from 114 - 190 to -1.0 - 1.0*/
	dPitch_Result1 = (ui8_PitchPW - LOWER_PW)/(UPPER_PW - LOWER_PW)*2.0 - 1.0;
	PID_Roll.Name = 1;
	PID_Pitch.Name = 2;
	PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, STRAIGHT_SETPOINT, dRoll_Result1, NO_CHANGE, NO_CHANGE);
	PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, PITCH_SETPOINT, dPitch_Result1, NO_CHANGE, NO_CHANGE);
}

/**
  * @brief  This function include initial calculations of Stanley algorithmr.
  */
void Control_Init_Standley_Algorithm(void)
{
	IMU_GPS_Data_Process();
	if (IMU_GPS_IsCoordinateAvailable())
	{
		uint8_t i = 0, j[1][2];
		double Coordinate[1][2], TrajectUTM[TRAJECT_SIZE][2], CoordinUTM[1][2], Speed;
		Coordinate[0][0] = IMU_GPS_GetLatitude();		
		Coordinate[0][1] = IMU_GPS_GetLongtitude();
//		Coordinate[0][0] = 10.769676;
//		Coordinate[0][1] = 106.657495;
		//Stanley_Init(Trajectory, ui8_Size, Coordinate, IMU_GPS_GetYaw(), K, IMU_GPS_GetSpeed());
		UTM_Deg2utm(Trajectory, TrajectUTM, j, TRAJECT_SIZE);
		UTM_Deg2utm(Coordinate, CoordinUTM, j, 1);
		//Speed = Test_Velocity;
		Speed = IMU_GPS_GetSpeed();
		if (Speed <= MIN_SPEED)
			Speed = MIN_SPEED;
		Stanley_Init(TrajectUTM, ui8_Size, CoordinUTM, IMU_GPS_Yaw_Heading(), K_SL, Speed);
		bChange_Mode = false;
		bInitialized = true;
	}
	else 
		bChange_Mode = true;
}

/**
  * @brief  This function segments the Setpoint into smaller setpoint to avoid overload.
  *	@retval Segment setpoint in type Double
  *	@param  Setpoint_Segment_Array ist the array, that contain segment setpoints and have to be sorted from small to large.
  * @param ui8_Index_Retain ist the argument that is used to retain the current index of Setpoint_Segment_Array. This argument      
  *        muss be inited to be 0 and reset to 0 before a new process.
  */
double Control_Segment_Setpoint(double* Setpoint_Segment_Array, uint8_t ui8_Segment_Length, uint8_t* ui8_Index_Retain)
{
	if(fabs(Setpoint_Segment_Array[*ui8_Index_Retain] - IMU_GPS_GetRoll()) < SEGMENT_SETPOINT_DEABAND)
	{
		ui8_Index_Retain++;
	}
	return Setpoint_Segment_Array[*ui8_Index_Retain];
}
/**
  * @brief This function is used to create the segment setpoint list for Control_Segment_Setpoint.
  * @param num is the number of setpoint and than write setpoints follow.  
  */
uint8_t Control_Setpoint_Segment_Prepare_Data(double* Setpoint_Segment_Array, int num,...)
{
	va_list valist;
	uint32_t ui32_Index;
	va_start(valist, num);

	for (ui32_Index = 0; ui32_Index < num; ui32_Index++) 
	{
	  Setpoint_Segment_Array[ui32_Index] = va_arg(valist, double);
	}

	va_end(valist);

	return num;
}
/**
  * @brief This function is used to create the segment setpoint list for Control_Segment_Setpoint, just test for NCKH.
  * @param Num_Setpoint is the number of setpoint and than write setpoints follow.  
  */
uint8_t Control_Setpoint_Segment_Prepare_Data_Test(double* Setpoint_Segment_Array, double Setpoint_1, double Setpoint_2, double Setpoint_3, uint8_t Num_Setpoint)
{
	if(Num_Setpoint == 2)
	{
		Setpoint_Segment_Array[0] = Setpoint_1;
		Setpoint_Segment_Array[1] = Setpoint_2;
	}
	else if(Num_Setpoint == 3)
	{
		Setpoint_Segment_Array[0] = Setpoint_1;
		Setpoint_Segment_Array[1] = Setpoint_2;
		Setpoint_Segment_Array[2] = Setpoint_3;
	}
	
	return Num_Setpoint;
}
/**
  * @brief This function is used to create the segment setpoint list depend on command sate.
  * @param Num_Setpoint is the number of setpoint and than write setpoints follow.  
  */
void Control_Setpoint_Setment_Prepare_State(Control_State_Enum Current_State,Control_State_Enum Pre_Sate)
{
	switch(Current_State)
	{
		case STABLE:
			if(Pre_Sate == TURN_LEFT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, H_LEFT_SETPOINT + 10, H_LEFT_SETPOINT + 20, STRAIGHT_SETPOINT,3);
			else if(Pre_Sate == TURN_RIGHT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, H_RIGHT_SETPOINT - 10, H_RIGHT_SETPOINT - 20, STRAIGHT_SETPOINT,3);
			break;
		case TRACK_LEFT:
			if(Pre_Sate == TURN_LEFT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, H_LEFT_SETPOINT + 10, L_LEFT_SETPOINT, L_LEFT_SETPOINT,2);
			break;
		case TRACK_RIGHT:
			if(Pre_Sate == TURN_RIGHT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, H_RIGHT_SETPOINT - 10, L_RIGHT_SETPOINT, L_RIGHT_SETPOINT,2);
			break;
		case TURN_LEFT:
			if(Pre_Sate == STABLE)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, STRAIGHT_SETPOINT - 10, STRAIGHT_SETPOINT - 20, H_LEFT_SETPOINT,3);
			else if(Pre_Sate == TRACK_LEFT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, L_LEFT_SETPOINT - 10,  H_LEFT_SETPOINT, H_LEFT_SETPOINT,2);
			break;
		case TURN_RIGHT:
			if(Pre_Sate == STABLE)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, STRAIGHT_SETPOINT + 10, STRAIGHT_SETPOINT + 20, H_RIGHT_SETPOINT,3);
			else if(Pre_Sate == TRACK_RIGHT)
				ui8_Num_Segment_Setpoint = Control_Setpoint_Segment_Prepare_Data_Test(Segment_Setpoint_Array, L_RIGHT_SETPOINT + 10,  H_RIGHT_SETPOINT, H_RIGHT_SETPOINT,2);
			break;
		default:
			break;
	}
}
/**
  * @brief This function is used to control Yaw turn to a definite angle and the definite angle is defined by the lable TURN_ANGLE in define.h.
  * @param Threshold_Angle is the desired turning angle.
  */
bool Control_Turn_Definite_Angle(double Threshold_Angle)
{
	float Current_Yaw, Start_Turn_Yaw;
	
	Current_Yaw = IMU_GPS_GetYaw();
	Start_Turn_Yaw = Control_Get_Important_Parameters(YAW_BEFORE_TURN);
	
	if ((Start_Turn_Yaw >= 90.0) && (Start_Turn_Yaw <= 180.0)) // Khi goc dat ban dau tu 90 den 180 thi neu 
	{														   // goc hien tai trong khoang -90 den -180 thi cong them 360
		if ((Current_Yaw <= -90.0) && (Current_Yaw >= -180.0))
		{
				Current_Yaw += 360.0;
		}
	}
	else if ((Start_Turn_Yaw <= -90.0) && (Start_Turn_Yaw >= -180.0)) // Tuong tu nhu tren
	{
		if ((Current_Yaw >= 90.0) && (Current_Yaw <= 180.0))
		{
				Current_Yaw -= 360.0;
		}
	}
	
	Yaw_Error = fabs(Start_Turn_Yaw - Current_Yaw);
	if (Yaw_Error >= Threshold_Angle) // neu sai so vuot qua cho phep thi Alarm d? quay ve Stable.
	{
		//Reset Pitch control signal
		//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Control_Get_Important_Parameters(U_PITCH_GETINTO_TURNSTATE), NO_CHANGE, NO_CHANGE);
		return true;
	}
	return false;	
}
/**
  * @brief This function is used to save important parameters, which is used in control process.
  */
void Control_Save_Important_Parameters(Temporary_Important_Parameters_Enum Para_Name, double Para_Value)
{
	switch(Para_Name)
	{
		case U_PITCH_GETINTO_TURNSTATE:
			Temporary_Important_Parameters.u_Pitch_Getinto_Turnstate = Para_Value;
			break;
		case YAW_BEFORE_TURN:
			Temporary_Important_Parameters.Yaw_Before_Turn = Para_Value;
			break;
		case UPPER_CURRENT_RESULT_THRES_PITCH:
			Temporary_Important_Parameters.Upper_Current_Result_Thres_Pitch = Para_Value;
			break;
		case ROLL_EFFECT:
			Temporary_Important_Parameters.Roll_Effect = Para_Value;
			break;
		default:
			break;
	}
}
/**
  * @brief This function is used to get important parameters, which is used in control process.
  */
double Control_Get_Important_Parameters(Temporary_Important_Parameters_Enum Para_Name)
{
	switch(Para_Name)
	{
		case U_PITCH_GETINTO_TURNSTATE:
			return Temporary_Important_Parameters.u_Pitch_Getinto_Turnstate;
			break;
		case YAW_BEFORE_TURN:
			return Temporary_Important_Parameters.Yaw_Before_Turn;
			break;
		case UPPER_CURRENT_RESULT_THRES_PITCH:
			return Temporary_Important_Parameters.Upper_Current_Result_Thres_Pitch;
			break;
		case ROLL_EFFECT:
			return Temporary_Important_Parameters.Roll_Effect;
			break;
		default:
			return 0;
			break;
	}	
}
/**
  * @brief This function is used to distribute the states in fucntion Control_State_Machine().
  * @param Invert_Flag is true when yaw_error > 180 degree.
  */
void Control_State_Distribute(bool bInvert_Flag)
{
	if(Yaw_Error_fabs <= YAW_ERROR_STABLE_RANGE)
	{
		//This code is used to prepare Setpoint Data for the first time change command state.  
//		if(Command_State == TURN_LEFT)
//			Control_Setpoint_Setment_Prepare_State(STABLE, TURN_LEFT);
//		else if(Command_State == TURN_RIGHT)
//			Control_Setpoint_Setment_Prepare_State(STABLE, TURN_RIGHT);
		Command_State = STABLE;
	}
	else if(Yaw_Error_fabs > YAW_ERROR_STABLE_RANGE && Yaw_Error_fabs <= YAW_ERROR_TRACK_RANGE)
	{
		if(bInvert_Flag)
		{
			if(Yaw_Error > 0)
			{
				//Can not change from TRACK_RIGHT to TRACK_LEFT.Firstly, state muss change from TRACK_RIGHT to STABLE.
				if(Command_State == TRACK_RIGHT)
					Command_State = STABLE;			
				else
					Command_State = TRACK_LEFT;
			}
			else
			{
				//Can not change from TRACK_LEFT to TRACK_RIGHT.Firstly, state muss change from TRACK_LEFT to STABLE.
				if(Command_State == TRACK_LEFT)
					Command_State = STABLE;
				else 
					Command_State = TRACK_RIGHT;
			}
		}
		else
		{
			if(Yaw_Error < 0)
			{
				//Can not change from TRACK_RIGHT to TRACK_LEFT.Firstly, state muss change from TRACK_RIGHT to STABLE.
				if(Command_State == TRACK_RIGHT)
					Command_State = STABLE;			
				else
					Command_State = TRACK_LEFT;
			}
			else
			{
				//Can not change from TRACK_LEFT to TRACK_RIGHT.Firstly, state muss change from TRACK_LEFT to STABLE.
				if(Command_State == TRACK_LEFT)
					Command_State = STABLE;
				else 
					Command_State = TRACK_RIGHT;
			}
		}
	}
	else if(Yaw_Error_fabs > YAW_ERROR_TRACK_RANGE)
	{
		if(bInvert_Flag)
		{
			if(Yaw_Error > 0)
			{
				//This code is used to prepare Setpoint Data for the first time change command state.
//				if(Command_State == STABLE)
//					Control_Setpoint_Setment_Prepare_State(TURN_LEFT, STABLE);
//				else if(Command_State == TRACK_LEFT)
//					Control_Setpoint_Setment_Prepare_State(TURN_LEFT, TRACK_LEFT);
				
				//Can not change from TRACK_RIGHT to TURN_LEFT.Firstly, state muss change from TRACK_RIGHT to STABLE.
				if(Command_State == TRACK_RIGHT)
					Command_State = STABLE;			
				else
				{
					Command_State = TURN_LEFT;
					//Control_Save_Important_Parameters(YAW_BEFORE_TURN, (double)IMU_GPS_GetYaw());
					Control_Save_Important_Parameters(YAW_BEFORE_TURN, IMU_GPS_Yaw_Heading());
				}
			}
			else
			{
				//This code is used to prepare Setpoint Data for the first time change command state.
//				if(Command_State == STABLE)
//					Control_Setpoint_Setment_Prepare_State(TURN_RIGHT, STABLE);
//				else if(Command_State == TRACK_RIGHT)
//					Control_Setpoint_Setment_Prepare_State(TURN_RIGHT, TRACK_RIGHT);
				
				//Can not change from TRACK_LEFT to TURN_RIGHT.Firstly, state muss change from TRACK_LEFT to STABLE.
				if(Command_State == TRACK_LEFT)
					Command_State = STABLE;
				else
				{							
					Command_State = TURN_RIGHT;
					Control_Save_Important_Parameters(YAW_BEFORE_TURN, IMU_GPS_Yaw_Heading());
				}
			}
		}
		else
		{
			if(Yaw_Error < 0)
			{
				//This code is used to prepare Setpoint Data for the first time change command state.
//				if(Command_State == STABLE)
//					Control_Setpoint_Setment_Prepare_State(TURN_LEFT, STABLE);
//				else if(Command_State == TRACK_LEFT)
//					Control_Setpoint_Setment_Prepare_State(TURN_LEFT, TRACK_LEFT);
				
				//Can not change from TRACK_RIGHT to TURN_LEFT.Firstly, state muss change from TRACK_RIGHT to STABLE.
				if(Command_State == TRACK_RIGHT)
					Command_State = STABLE;			
				else
				{
					Command_State = TURN_LEFT;
					Control_Save_Important_Parameters(YAW_BEFORE_TURN, IMU_GPS_Yaw_Heading());
				}
			}
			else
			{
				//This code is used to prepare Setpoint Data for the first time change command state.
//				if(Command_State == STABLE)
//					Control_Setpoint_Setment_Prepare_State(TURN_RIGHT, STABLE);
//				else if(Command_State == TRACK_RIGHT)
//					Control_Setpoint_Setment_Prepare_State(TURN_RIGHT, TRACK_RIGHT);
				
				//Can not change from TRACK_LEFT to TURN_RIGHT.Firstly, state muss change from TRACK_LEFT to STABLE.
				if(Command_State == TRACK_LEFT)
					Command_State = STABLE;
				else
				{	
					Command_State = TURN_RIGHT;
					Control_Save_Important_Parameters(YAW_BEFORE_TURN, IMU_GPS_Yaw_Heading());					
				}
			}
		}
	}	
}
/**
  * @brief This function is the main PID control for pitch and roll.
  */
void Control_PID(void)
{
	TIM_PWM_SetPulseWidth(PID_Calculate_Pitch(&PID_Pitch, -IMU_GPS_GetPitch(), IMU_GPS_GetVy(), Control_Get_Important_Parameters(ROLL_EFFECT),Control_Get_Important_Parameters(UPPER_CURRENT_RESULT_THRES_PITCH), LOWER_RESULT_THRES_PITCH), ELEVATOR);
	TIM_PWM_SetPulseWidth(PID_Calculate_Roll(&PID_Roll, IMU_GPS_GetRoll(), IMU_GPS_GetVx()), AILERON);
}
/**
  * @brief This function is used to control Yaw heading turn to a definite angle and the definite angle is defined by the lable TURN_ANGLE in define.h.
  * @param Threshold_Angle is the desired turning angle.
  */
bool Control_Turn_Definite_Angle_Heading(double Threshold_Angle)
{
	float Current_Yaw, Start_Turn_Yaw;
	
	Current_Yaw = IMU_GPS_Yaw_Heading();
	Start_Turn_Yaw = Control_Get_Important_Parameters(YAW_BEFORE_TURN);
	
	if ((Start_Turn_Yaw >= 270.0) && (Start_Turn_Yaw <= 360.0)) // Khi goc dat ban dau tu 90 den 180 thi neu 
	{														   // goc hien tai trong khoang -90 den -180 thi cong them 360
		if ((Current_Yaw <= 90.0) && (Current_Yaw >= 0.0))
		{
				Current_Yaw += 360.0;
		}
	}
	else if ((Start_Turn_Yaw <= 90.0) && (Start_Turn_Yaw >= 0.0)) // Tuong tu nhu tren
	{
		if ((Current_Yaw >= 270.0) && (Current_Yaw <= 360.0))
		{
				Current_Yaw -= 360.0;
		}
	}
	Yaw_Turn_Error = fabs(Start_Turn_Yaw - Current_Yaw);
	if (Yaw_Turn_Error >= Threshold_Angle) // neu sai so vuot qua cho phep thi Alarm d? quay ve Stable.
	{
		//Reset Pitch control signal
		//PID_Set_Param(&PID_Pitch, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, Control_Get_Important_Parameters(U_PITCH_GETINTO_TURNSTATE), NO_CHANGE, NO_CHANGE);
		return true;
	}
	return false;	
}