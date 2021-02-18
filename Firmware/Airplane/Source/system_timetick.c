
/* Includes ------------------------------------------------------------------*/
#include "system_timetick.h"
#include "IMU_GPS.h"

uint32_t	tick_count;
uint32_t	tick_flag;
#define BUFF_SIZE	73

extern uint8_t 	rxbuff[BUFF_SIZE];
extern Value_Process_GGA string_pro;
extern Value_Process_VTG string_pro_v;
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}
	  
void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  tick_flag = 1;
  tick_count++;
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		// Do something here suntan   
		
  }
}
