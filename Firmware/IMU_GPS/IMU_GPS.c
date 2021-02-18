#include "IMU_GPS.h"


IMU_Data_Struct IMU_Data;
GGA_Data_Struct GGA_Data;
VTG_Data_Struct VTG_Data;

uint16_t ui16_DMA_Byte_Empty = 0;
uint32_t tick_start0 = 0;
char string[220];

char cRx_Buff[BUFF_SIZE];

void IMU_GPS_DMA_Init(void);
void IMU_GPS_Uart_Init(void);
void IMU_GPS_Timeout_Init(void);
void IMU_Data_Update(uint8_t ui8_Data_Start_Byte, float f_Current_Data);
int8_t IMU_Data_Sign(uint8_t ui8_Data_Sign);
void IMU_GPS_DMA_Restart(void);
void IMU_GPS_Data_Reading(uint16_t ui16_start_index, uint16_t ui16_end_index);

void IMU_GPS_Uart_Init(void)
{

	GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;  
   
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Connect USART2 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); 

  /* GPIO Configuration for USART2 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIO Configuration for USART2 Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 460800 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 460800;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
  /* Enable USART */
  USART_Cmd(USART2, ENABLE);
	/* Enable USART2 DMA */
  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
}
void IMU_GPS_DMA_Init(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
//	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/* DMA1 Stream5 Channel4 for USART2 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)cRx_Buff;// hoi lai?? sao ko ep kieu con tro
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream5, ENABLE);
			
//	/* Enable DMA Interrupt to the highest priority */
//  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

//  /* Transfer complete interrupt mask */
//  DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);
}
void GPS_GGA_Data_Process(void)
{
	uint8_t ui8_previousindex, ui8_nextindex, i, j;
	uint8_t ui8_stringid = 0;
	uint8_t b_flag = 0;
	char *pui8_temp;
	char c_temp1[10], c_temp2[10];
	for (i = 0; i < GGA_Data.string_size; i++)		// Search for ',' character, determine positions of ','s
	{
		if ((b_flag == 0) && (GGA_Data.original_string[i] == ','))
		{
			ui8_previousindex = i;
			b_flag = 1;
		}
		else if (((b_flag == 1) && (GGA_Data.original_string[i] == ',')) || (i == (GGA_Data.string_size - 1)))
		{
			ui8_nextindex = i;
			b_flag = 1;
			ui8_stringid++;	
			switch (ui8_stringid)			// String ID was numbered in declaration of struct 
			{
				case 1: 
					GGA_Data.sTime[9] = '\0';
					pui8_temp = GGA_Data.sTime;
					break;
				case 2:
					GGA_Data.sLatitude[10] = '\0';
					pui8_temp = GGA_Data.sLatitude;
					break;
				case 3:
					pui8_temp = &(GGA_Data.Latitude_NS);
					break;
				case 4:
					GGA_Data.sLongtitude[11] = '\0';
					pui8_temp = GGA_Data.sLongtitude;
					break;
				case 5:
					pui8_temp = &(GGA_Data.Longtitude_WE);
					break;
				case 6:
					pui8_temp = &(GGA_Data.sFix);
					break;
				case 7:
					GGA_Data.sNo_Satellite[2] = '\0';
					pui8_temp = GGA_Data.sNo_Satellite;
					break;
				case 8:
					GGA_Data.sHDOP[4] = '\0';
					pui8_temp = GGA_Data.sHDOP;
					break;
				case 9:
					GGA_Data.sAltitude[5] = '\0';
					pui8_temp = GGA_Data.sAltitude;
					break;
				case 10:
					GGA_Data.sAltitude_unit[2] = '\0';
					pui8_temp = GGA_Data.sAltitude_unit;
					break;
				case 11:
					GGA_Data.sHeight_geoid[4] = '\0';
					pui8_temp = GGA_Data.sHeight_geoid;
					break;
				case 12:
					GGA_Data.sHeight_geoid_unit[2] = '\0';
					pui8_temp = GGA_Data.sHeight_geoid_unit;
					break;
				case 13:
					GGA_Data.sTime_update[2] = '\0';
					pui8_temp = GGA_Data.sTime_update;
					break;
				case 14:
					GGA_Data.sStation_ID[2] = '\0';
					pui8_temp = GGA_Data.sStation_ID;
					break;
				case 15:
					ui8_stringid = 0;
					GGA_Data.sChecksum[2] = '\0';
					pui8_temp = GGA_Data.sChecksum;
					break;
			}
			if (ui8_previousindex != ui8_nextindex)							// if no character between two ',' skip to next string
																													// still remain the old value.
			{
				for (j = 0; j < (ui8_nextindex - ui8_previousindex - 1); j++) // (ui8_nextindex - ui8_previousindex - 1): size of data string between 2 ','s.
				pui8_temp[j] = GGA_Data.original_string[ui8_previousindex + j + 1];
				pui8_temp[ui8_nextindex - ui8_previousindex - 1] = '\0';
				ui8_previousindex = ui8_nextindex;
			}		
		}
	}
	// Convert to struct value
	//value_pr->Latitude = Convert_String(string_pr.Latitude, 2) + Convert_String(&(string_pr.Latitude[2]), 8)/60;
	c_temp1[2] = 0x00;
	strncpy(c_temp1, GGA_Data.sLatitude, 2);
	strncpy(c_temp2, &(GGA_Data.sLatitude[2]), 8);
	GGA_Data.Latitude = atof(c_temp1) + atof(c_temp2)/60;
	GGA_Data.Latitude_NS = GGA_Data.Latitude_NS;
	strncpy(c_temp1, GGA_Data.sLongtitude, 3);
	strncpy(c_temp2, &(GGA_Data.sLongtitude[3]), 8);
	GGA_Data.Longtitude = atof(c_temp1) + atof(c_temp2)/60;
	GGA_Data.Longtitude_WE = GGA_Data.Longtitude_WE;
	GGA_Data.No_Satellite =  (uint8_t) atof(GGA_Data.sNo_Satellite);
	GGA_Data.Altitude = atof(GGA_Data.sAltitude);
	GGA_Data.Height_geoid = atof(GGA_Data.sHeight_geoid);
}
void GPS_VTG_Data_Process(void)
{
	uint8_t ui8_previousindex, ui8_nextindex, i, j;
	uint8_t ui8_stringid = 0;
	uint8_t b_flag = 0;
	char *pui8_temp;
	for (i = 0; i < VTG_Data.string_size; i++)		// Search for ',' character, determine positions of ','s
	{
		if ((b_flag == 0) && (VTG_Data.original_string[i] == ','))
		{
			ui8_previousindex = i;
			b_flag = 1;
		}
		else if (((b_flag == 1) && (VTG_Data.original_string[i] == ',')) || (i == (VTG_Data.string_size - 1)))
		{
			ui8_nextindex = i;
			b_flag = 1;
			ui8_stringid++;	
			switch (ui8_stringid)			// String ID was numbered in declaration of struct 
			{
				case 1: 
					VTG_Data.sDegree_true[6] = '\0';
					pui8_temp = VTG_Data.sDegree_true;
					break;
				case 2:
					pui8_temp = &(VTG_Data.True_north);
					break;
				case 3:
					VTG_Data.sDegree_magnetic[6] = '\0';
					pui8_temp = VTG_Data.sDegree_magnetic;
					break;
				case 4:
					pui8_temp = &(VTG_Data.Magnetic_north);
					break;
				case 5:
					VTG_Data.sSpeed[6] = '\0';
					pui8_temp = VTG_Data.sSpeed;
					break;
				case 6:
					pui8_temp = &(VTG_Data.Speed_unit);
					break;
				case 7:
					VTG_Data.sSpeed_over_ground[6] = '\0';
					pui8_temp = VTG_Data.sSpeed_over_ground;
					break;
				case 8:
					pui8_temp = &(VTG_Data.Speed_over_ground_unit);
					break;
				case 9:
					ui8_stringid = 0;
					VTG_Data.sChecksum[2] = '\0';
					pui8_temp = VTG_Data.sChecksum;
					break;
			}
			if (ui8_previousindex != ui8_nextindex)		// if no character between two ',' skip to next string, still remain the old value.
			{
				for (j = 0; j < (ui8_nextindex - ui8_previousindex - 1); j++) // (ui8_nextindex - ui8_previousindex - 1): size of data string between 2 ','s.
				pui8_temp[j] = VTG_Data.original_string[ui8_previousindex + j + 1];
				pui8_temp[ui8_nextindex - ui8_previousindex - 1] = '\0';
				ui8_previousindex = ui8_nextindex;
			}		
		}
	}
	// Convert to struct value
	VTG_Data.Degree_true = atof(VTG_Data.sDegree_true);
	VTG_Data.Degree_magnetic = atof(VTG_Data.sDegree_magnetic);
	VTG_Data.Speed = atof(VTG_Data.sSpeed);
	VTG_Data.Speed_over_ground = atof(VTG_Data.sSpeed_over_ground)*KPH2MPS;
}

//void DMA1_Stream5_IRQHandler(void)
//{
//  DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF2);
//	DMA_Cmd(DMA1_Stream5, ENABLE);
//}

void IMU_GPS_Timeout_Init(void)
{
	/* Enable SysTick at 2ms interrupt */
	SysTick_Config(SystemCoreClock/1000);
}

void IMU_GPS_Init(void)
{
	IMU_GPS_Timeout_Init();
	IMU_GPS_Uart_Init();
	IMU_GPS_DMA_Init();
}

void IMU_Data_Process(void)
{
	uint32_t ui32_Sign_Index = 0, ui32_Data_Index = 0;
	float	f_Data_Temp = 0;
	for(ui32_Sign_Index = IMU_PHI_START_BYTE; ui32_Sign_Index <= IMU_WZ_START_BYTE; ui32_Sign_Index +=IMU_NUM_DIGIT+1)
	{
		for(ui32_Data_Index = ui32_Sign_Index + IMU_NUM_DIGIT - 1; ui32_Sign_Index < ui32_Data_Index; ui32_Data_Index--)
		{
			f_Data_Temp = f_Data_Temp + (IMU_Data.completed_string[ui32_Data_Index]-0x30)*pow(10,IMU_NUM_DIGIT - 1 - ui32_Data_Index + ui32_Sign_Index);
		}
		f_Data_Temp = f_Data_Temp*IMU_Data_Sign(IMU_Data.completed_string[ui32_Sign_Index]);
		IMU_Data_Update(ui32_Sign_Index, f_Data_Temp/100);
		f_Data_Temp = 0;
	}
}

int8_t IMU_Data_Sign(uint8_t ui8_Data_Sign)
{
	if(ui8_Data_Sign == '-')
	{
		return -1;
	}
	else 
	{
		return 1;
	}
		
}

void IMU_Data_Update(uint8_t ui8_Data_Start_Byte, float f_Current_Data)
{
	switch(ui8_Data_Start_Byte)
	{
		case IMU_PHI_START_BYTE:
			IMU_Data.Phi = f_Current_Data;
			break;
		case IMU_THETA_START_BYTE:
			IMU_Data.Theta = f_Current_Data;
			break;
		case IMU_PSI_START_BYTE:
			IMU_Data.Psi = f_Current_Data;
			break;
		case IMU_WX_START_BYTE:
			IMU_Data.Wx = f_Current_Data;
			break;
		case IMU_WY_START_BYTE:
			IMU_Data.Wy = f_Current_Data;
			break;
		case IMU_WZ_START_BYTE:
			IMU_Data.Wz = f_Current_Data;
			break;
		case IMU_AX_START_BYTE:
			IMU_Data.Ax = f_Current_Data;
			break;
		case IMU_AY_START_BYTE:
			IMU_Data.Ay = f_Current_Data;
			break;
		case IMU_AZ_START_BYTE:
			IMU_Data.Az = f_Current_Data;
			break;
		default:
			break;
	}
}

void IMU_GPS_DMA_Restart(void)
{
	DMA_Cmd(DMA1_Stream5,DISABLE);
	DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2);
	DMA_SetCurrDataCounter(DMA1_Stream5,BUFF_SIZE);
	DMA_Cmd(DMA1_Stream5,ENABLE);
}

void IMU_GPS_Data_Process(void)
{ 
	uint8_t Size, i;
	char RFData[BUFFTX_SIZE];

	IMU_Data_Process();
	GPS_VTG_Data_Process();
	GPS_GGA_Data_Process();
	/* Prepare data for transferring to RF module*/
//	if (SysTick_IsTimeout(tick_start0, TRANS_PEDRIOD))
//	{
//		Size = IMU_Data.string_size + VTG_Data.string_size + GGA_Data.string_size;
//		for (i = 0; i < IMU_Data.string_size; i++)
//			RFData[i] = IMU_Data.completed_string[i];
//		RFData[IMU_Data.string_size] = 0x0d;
//		RFData[IMU_Data.string_size +1] = 0x0a;
//		for (i = (IMU_Data.string_size + 2); i < (IMU_Data.string_size + VTG_Data.string_size); i++)
//			RFData[i] = VTG_Data.completed_string[i - IMU_Data.string_size];
//		RFData[IMU_Data.string_size + VTG_Data.string_size] = 0x0d;
//		RFData[IMU_Data.string_size + VTG_Data.string_size + 1] = 0x0a;
//		for (i = (IMU_Data.string_size + VTG_Data.string_size + 2); i < Size; i++)
//			RFData[i] = GGA_Data.completed_string[i - (IMU_Data.string_size + VTG_Data.string_size)];
//		RFData[Size] = 0x0d;
//		RFData[Size + 1] = 0x0a;
//		RF_GainData(RFData, (Size + 2));
//		tick_start0 = SysTick_GetTick();
//	}
}
float IMU_GPS_GetRoll(void)
{
	return (IMU_Data.Phi); // Chua biet phan thap phan, kiem tra goc Roll?!
}
float IMU_GPS_GetPitch(void)
{
	return (-IMU_Data.Theta); // Chua biet phan thap phan, kiem tra goc Pitch?!
}
float IMU_GPS_GetYaw(void)
{
	return IMU_Data.Psi; // Chua biet phan thap phan, kiem tra goc Yaw?!
}
float IMU_GPS_GetLatitude(void)
{
	return GGA_Data.Latitude;
}
float IMU_GPS_GetLongtitude(void)
{
	return GGA_Data.Longtitude;
}
float IMU_GPS_GetAltitude(void)
{
	return GGA_Data.Altitude;
}
float IMU_GPS_GetPressure(void)
{
	return IMU_Data.P;
}
float IMU_GPS_GetVx(void)
{
	return IMU_Data.Wx; // Chuyen thanh van toc dai
}
float IMU_GPS_GetVy(void)
{
	return IMU_Data.Wy; // Chuyen thanh van toc dai
}
float IMU_GPS_GetVz(void)
{
	return IMU_Data.Wz; // Chuyen thanh van toc dai
}
float IMU_GPS_GetSpeed(void)
{
	return ((float) (VTG_Data.Speed_over_ground));
}
bool IMU_GPS_IsCoordinateAvailable(void)
{
	if (GGA_Data.string_size > 50)
		return true;
	else
		return false;
}
void IMU_GPS_Pre_Process(void)
{
	static uint16_t ui16_end_index, ui16_start_index = 0;
	if (DMA1_Stream5->NDTR == BUFF_SIZE)
		ui16_end_index = BUFF_SIZE - 1;
	else
		ui16_end_index = BUFF_SIZE - DMA1_Stream5->NDTR - 1; 	
	if(ui16_end_index < ui16_start_index)
	{
		IMU_GPS_Data_Reading(ui16_start_index, (BUFF_SIZE - 1));
		IMU_GPS_Data_Reading(0, ui16_end_index);
		if (ui16_end_index == (BUFF_SIZE - 1))
			ui16_start_index = 0;
		else
			ui16_start_index = ui16_end_index + 1;
	}
	else if ((ui16_end_index > ui16_start_index) && !((ui16_start_index == 0) && (ui16_end_index == (BUFF_SIZE - 1))))
	{
		IMU_GPS_Data_Reading(ui16_start_index, ui16_end_index);
		if (ui16_end_index == (BUFF_SIZE - 1))
			ui16_start_index = 0;
		else
			ui16_start_index = ui16_end_index + 1;
	}
}
void IMU_GPS_Data_Reading(uint16_t ui16_start_index, uint16_t ui16_end_index)
{
	uint32_t ui32_Index = 0;
	static uint8_t ui8_index;
	static IMU_GPS_Reading_State Reading_State = IDLE;
	for (ui32_Index = ui16_start_index; ui32_Index <= ui16_end_index; ui32_Index++)
	{
		switch (Reading_State)
		{
			case START:
				if ((cRx_Buff[ui32_Index] == ' ') || (cRx_Buff[ui32_Index] == '-'))
				{
					Reading_State = IMU_READING;
					IMU_Data.original_string[0] = cRx_Buff[ui32_Index];
					ui8_index = 1;
				}
				else if (cRx_Buff[ui32_Index] == 'V')
				{
					Reading_State = VTG_READING;
					ui8_index = 3;
				}
				else if (cRx_Buff[ui32_Index] == 'A')
				{
					Reading_State = GGA_READING;
					ui8_index = 5;
				}
				break;
			case IMU_READING:
				if (cRx_Buff[ui32_Index] == 0x0D)
				{	
					uint32_t i;
					IMU_Data.original_string[ui8_index] = '\0';
					IMU_Data.string_size = ui8_index;
					for (i = 0; i <= ui8_index; i++)
						IMU_Data.completed_string[i] = IMU_Data.original_string[i];
					Reading_State = IDLE;
				}
				else
				{
					IMU_Data.original_string[ui8_index++] = cRx_Buff[ui32_Index];
				}
				break;
			case VTG_READING:
				if (cRx_Buff[ui32_Index] == 0x0D)
				{	
					uint32_t i;
					VTG_Data.original_string[ui8_index] = '\0';
					VTG_Data.string_size = ui8_index;
					for (i = 0; i <= ui8_index; i++)
						VTG_Data.completed_string[i] = VTG_Data.original_string[i];
					Reading_State = IDLE;
				}
				else
				{
					VTG_Data.original_string[ui8_index++] = cRx_Buff[ui32_Index];
				}
				break;
			case GGA_READING:
				if (cRx_Buff[ui32_Index] == 0x0D)
				{	
					uint32_t i;
					GGA_Data.original_string[ui8_index] = '\0';
					GGA_Data.string_size = ui8_index;
					for (i = 0; i <= ui8_index; i++)
						GGA_Data.completed_string[i] = GGA_Data.original_string[i];
					Reading_State = IDLE;
				}
				else
				{
					GGA_Data.original_string[ui8_index++] = cRx_Buff[ui32_Index];
				}
				break;
			case IDLE:
				if (cRx_Buff[ui32_Index] == 0x0A)
				{
					Reading_State = START;
					ui8_index = 0;
				}
				break;
			default:
				break;
		}
	}
}
float IMU_GPS_Yaw2East(void)
{
	float New_Yaw;
	New_Yaw = -IMU_Data.Psi + PI/2.0;
	if (New_Yaw > PI)
		New_Yaw -= 2.0*PI;
	else if (New_Yaw < -PI)
		New_Yaw += 2.0*PI;
	return New_Yaw;
}
double IMU_GPS_Yaw_Heading(void)
{
	return VTG_Data.Degree_true;
}
void IMU_GPS_Get_Lat_String(char *LatStr)
{
	uint8_t i;
	for (i = 0; i < 10; i++)
	{
		LatStr[i] = GGA_Data.sLatitude[i];
	}
}
void IMU_GPS_Get_Lon_String(char *LonStr)
{
	uint8_t i;
	for (i = 0; i < 11; i++)
	{
		LonStr[i] = GGA_Data.sLongtitude[i];
	}
}
void IMU_GPS_Get_Alt_String(char *AltStr)
{
	uint8_t i;
	for (i = 0; i < 6; i++)
	{
		AltStr[i] = GGA_Data.sAltitude[i];
	}
}