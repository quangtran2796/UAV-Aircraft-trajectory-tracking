#include "GPIO.h"

void Switch_Config(void);
void LED_Config(void);
void Button_Config(void);
void Trigger_Config(void);

void GPIO_Config(void)
{
	Switch_Config();
	LED_Config();
	Button_Config();
	Trigger_Config();
}
void Switch_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = SW1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SW1_BASE, &GPIO_InitStructure);
	
  /* Configure PD12, PD13 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = SW2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SW2_BASE, &GPIO_InitStructure);
}
void LED_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = LED_RED | LED_GREEN | LED_BLUE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_BASE, &GPIO_InitStructure);
}
void Button_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = BTN1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BT1_BASE, &GPIO_InitStructure);
	
  /* Configure PD12, PD13 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = BTN2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BT2_BASE, &GPIO_InitStructure);
}
void Trigger_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = TRIGGER;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TRG_BASE, &GPIO_InitStructure);
	
}
void GPIO_LED_On(IO_Pin Pin)
{
	GPIO_SetBits(LED_BASE, Pin);
}

void GPIO_LED_Off(IO_Pin Pin)
{
	GPIO_ResetBits(LED_BASE, Pin);
}
void GPIO_LED_Blink(IO_Pin Pin, uint16_t cycle_ms)
{
	static uint16_t tick_start = 0;
	static bool LED_Blink = false;
	if (SysTick_IsTimeout(tick_start, cycle_ms))
	{
		tick_start = SysTick_GetTick();
		LED_Blink ^= LED_Blink;
		if (LED_Blink)
			GPIO_SetBits(LED_BASE, Pin);
		else
			GPIO_ResetBits(LED_BASE, Pin);
	}
}
uint8_t GPIO_Switch_Read(void)
{
	switch(GPIO_ReadInputDataBit(SW1_BASE, SW1)*2 + GPIO_ReadInputDataBit(SW2_BASE, SW2))
	{
		case 0x00:
			return MODE1;
		case 0x01:
			return MODE2;
		case 0x02:
			return MODE3;
		case 0x03:
			return MODE4;
		default:
			break;
	}
}
uint8_t GPIO_Button_Read(IO_Pin Pin)
{
	if (Pin == BTN1)
		return GPIO_ReadInputDataBit(BT1_BASE, BTN1);
	else if (Pin == BTN2)
		return GPIO_ReadInputDataBit(BT2_BASE, BTN2);
}
bool GPIO_Trigger_Read(void)
{
	return (GPIO_ReadInputDataBit(TRG_BASE, TRIGGER) == (uint8_t) 1);
}
