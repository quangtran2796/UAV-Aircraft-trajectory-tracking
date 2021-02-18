/* Call-back function after every 20ms */
void Data_Process(float *f_Roll, float *f_Pitch, float *f_Yaw, float *f_Velo_x, float *f_Velo_y, float *f_Velo_z, float *f_x, float *f_y, float *f_z)
{
	/* Call available functions in IMU_GPS.c*/
}
void Command_State(float *f_Roll, float *f_Pitch, float *f_Yaw, float *f_Velo_x, float *f_Velo_y, float *f_Velo_z, float *f_x, float *f_y, float *f_z)
{
	if (!Detect_Over_Angle(*f_Roll, *f_Pitch, *f_Yaw))
	{
		float f_Velocity = sqrt((*f_Velo_x)*(*f_Velo_x) + (*f_Velo_y)*(*f_Velo_y));
		Stanley(*f_Roll, *f_Pitch, *f_Yaw, f_Velocity, k, position, ui8_Mode);
		switch (ui8_Mode)
		{
			case STRAIGHT:
				Straight_Mode();
				break;
			case LEFT:
				Left_Mode();
				break;
			case RIGHT:
				Right_Mode();
				break;
		}
	}
}


/* SYSTEM SERVICES */
bool Detect_Over_Angle(float *f_Roll, float *f_Pitch, float *f_Yaw); /* If any angles are overranged, return true */
void Set_PulseWidth_Aileron(uint16_t ui16_PulWid)
{
	/* Apply PID*/
}
void Set_PulseWidth_Rudder(uint16_t ui16_PulWid);
void Set_PulseWidth_Elevator(uint16_t ui16_PulWid);
void Set_PulseWidth_Throttle(uint16_t ui16_PulWid);
void Stanley(...)
{
	/* Calculate Yaw angle based on Stanley algorithm */
	/* Estimate other angles (Roll, Pitch) based on Yaw*/
	Detect_Over_Angle();
	/* Determine mode: STRAIGHT, LEFT or RIGHT, based on trajectory. */
}

/* STABILIZATION MODE */
/* These functions will modify the angles to safe ranges*/
void Over_Roll(float *f_Roll)
{
	Set_PulseWidth_Aileron();
}
void Over_Pitch(float *f_Pitch);
void Over_Yaw(float *f_Yaw);

/* STRAIGHT MODE */
void Straight_Mode(...)
{
	Set_PulseWidth_Aileron();
	Set_PulseWidth_Elevator();
	Set_PulseWidth_Throttle();
}

/* LEFT MODE */
void Left_Mode(...)
{
	Set_PulseWidth_Aileron();
	Set_PulseWidth_Elevator();
	Set_PulseWidth_Throttle();
}

/* RIGHT MODE */
void Right_Mode(...)
{
	Set_PulseWidth_Aileron();
	Set_PulseWidth_Elevator();
	Set_PulseWidth_Throttle();
}