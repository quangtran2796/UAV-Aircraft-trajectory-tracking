#include "stm32f4xx_it.h"
//#include "include.h"
#include "stdbool.h"
#include "IMU_GPS.h"

uint32_t tick_count = 0;
bool tick_flag;
extern PID_TypeDef PID_Roll;

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	tick_count++;
	IMU_GPS_Pre_Process();
}
uint32_t SysTick_GetTick(void)
{
  return tick_count;
}
bool SysTick_IsTimeout(uint32_t start_time, uint32_t timeout_ms)
{
	return (tick_count - start_time > timeout_ms);
}
void UART4_IRQHandler(void)
{
	char Fight_Dir;
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		Fight_Dir = (char) USART_ReceiveData(UART4);
		switch (Fight_Dir)
		{
			case RIGHT:
				PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, H_RIGHT_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				break;
			case LEFT:
				PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, H_LEFT_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				break;
			case STRAIGHT:
				PID_Set_Param(&PID_Roll, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, STRAIGHT_SETPOINT, NO_CHANGE, NO_CHANGE, NO_CHANGE);
				break;
			default:
				break;
		}
	}
	USART_Cmd(UART4, ENABLE);
}

