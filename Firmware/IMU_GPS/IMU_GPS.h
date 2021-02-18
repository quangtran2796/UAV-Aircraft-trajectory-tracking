#ifndef IMU_GPS_H
#define IMU_GPS_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "include.h"
#define BUFF_SIZE 800
	 
#define IMU_PHI_START_BYTE		0
#define IMU_THETA_START_BYTE	7
#define IMU_PSI_START_BYTE		14
#define IMU_WX_START_BYTE			21
#define IMU_WY_START_BYTE			28
#define IMU_WZ_START_BYTE			35
#define IMU_NUM_DIGIT					6
#define IMU_CERTAINTY					100 //0.01 DEGREE
//3 thong so sau hien tai chua co
#define IMU_AX_START_BYTE			38
#define IMU_AY_START_BYTE			44
#define IMU_AZ_START_BYTE			50

typedef struct{
	char original_string[80];
	char completed_string[80];
	uint8_t string_size;
	float Phi;
	float Theta;
	float Psi;
	float Wx;
	float Wy;
	float Wz;
	float Ax;
	float Ay;
	float Az;
	float Mx;
	float My;
	float Mz;
	float P;
}IMU_Data_Struct;
	 
typedef struct{
	char original_string[90];
	char completed_string[90];
	uint8_t string_size;
	char sTime[10];							// 1
	char sLatitude[11];					// 2
	char Latitude_NS;						// 3
	char sLongtitude[12];				// 4
	char Longtitude_WE;					// 5
	char sFix;										// 6
	char sNo_Satellite[3];				// 7
	char sHDOP[5];								// 8
	char sAltitude[6];						// 9
	char sAltitude_unit[3];			// 10
	char sHeight_geoid[5];				// 11
	char sHeight_geoid_unit[3];	// 12
	char sTime_update[3];				// 13
	char sStation_ID[3];					// 14
	char sChecksum[3];						// 15
	double Latitude;
	double Longtitude;
	uint8_t No_Satellite;
	double Altitude;
	double Height_geoid;
} GGA_Data_Struct;

typedef struct{
	char original_string[50];
	char completed_string[50];
	uint8_t string_size;
	char sDegree_true[7];				// 1
	char True_north;						// 2
	char sDegree_magnetic[7];		// 3
	char Magnetic_north;				// 4
	char sSpeed[7];							// 5
	char Speed_unit;						// 6
	char sSpeed_over_ground[7];	// 7
	char Speed_over_ground_unit;// 8
	char sChecksum[3];						// 9
	double Degree_true;
	double Degree_magnetic;
	double Speed;
	double Speed_over_ground;
} VTG_Data_Struct;

typedef enum{
	START = 0,
	IMU_READING,
	VTG_READING,
	GGA_READING,
	IDLE,
	DEFAULT
} IMU_GPS_Reading_State;


/*entire string including "$" and "\n" characters */
void GPS_GGA_Data_Process(void);
void GPS_VTG_Data_Process(void);
void IMU_Data_Process(void);
void IMU_GPS_Init(void);
void IMU_GPS_Data_Process(void);
float IMU_GPS_GetRoll(void);
float IMU_GPS_GetPitch(void);
float IMU_GPS_GetYaw(void);
float IMU_GPS_GetLatitude(void);
float IMU_GPS_GetLongtitude(void);
float IMU_GPS_GetAltitude(void);
float IMU_GPS_GetPressure(void);
float IMU_GPS_GetVx(void);
float IMU_GPS_GetVy(void);
float IMU_GPS_GetVz(void);
float IMU_GPS_GetSpeed(void);
void IMU_GPS_Pre_Process(void);
bool IMU_GPS_IsCoordinateAvailable(void);
float IMU_GPS_Yaw2East(void);
double IMU_GPS_Yaw_Heading(void);
void IMU_GPS_Get_Lat_String(char *LatStr);
void IMU_GPS_Get_Lon_String(char *LonStr);
void IMU_GPS_Get_Alt_String(char *AltStr);

#endif /* IMU_GPS_H_ */

