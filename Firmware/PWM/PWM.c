#include "PWM.h"

void TIM_PWM_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	uint16_t PrescalerValue = 0;
	  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(PWM_CLOCK, ENABLE);

  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	  /* GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Configure PA6, PA7 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = AILERON | ELEVATOR;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure PB0, PB1 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = RUDDER | THROTTLE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / TICK_PERIOD) - 1;		// Setup cycle period: 0.4MHz

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = RELOAD_PERIOD;					// 8000 * (1/0.4e6) = 0.02s -> Reload counter after 20ms.
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(PWM_TIMERBASE, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(PWM_TIMERBASE, PrescalerValue, TIM_PSCReloadMode_Immediate);
	
  /* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, AILERON_PINSOURCE, GPIO_AF_PWM);
  GPIO_PinAFConfig(GPIOA, ELEVATOR_PINSOURCE, GPIO_AF_PWM); 
  GPIO_PinAFConfig(GPIOB, RUDDER_PINSOURCE, GPIO_AF_PWM);
  GPIO_PinAFConfig(GPIOB, THROTTLE_PINSOURCE, GPIO_AF_PWM); 
}

void TIM_PWM_SetPulseWidth(uint16_t ui16_Pulse_Width, PulseOut_Type Pulse_Out)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	__IO uint16_t CCR1_Val, CCR2_Val, CCR3_Val, CCR4_Val;

  /* PWM_TIMER disable counter */
  TIM_Cmd(PWM_TIMERBASE, DISABLE);
	
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	switch (Pulse_Out)
	{
		case AILERON:
			/* PWM1 Mode configuration: Channel1 */
			CCR1_Val = ui16_Pulse_Width;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
			TIM_OC1Init(PWM_TIMERBASE, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(PWM_TIMERBASE, TIM_OCPreload_Enable);
			break;
		case ELEVATOR:
			/* PWM1 Mode configuration: Channel2 */
			CCR2_Val = ui16_Pulse_Width;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
			TIM_OC2Init(PWM_TIMERBASE, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(PWM_TIMERBASE, TIM_OCPreload_Enable);
			break;
		case RUDDER:
			/* PWM1 Mode configuration: Channel3 */
			CCR3_Val = ui16_Pulse_Width;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
			TIM_OC3Init(PWM_TIMERBASE, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(PWM_TIMERBASE, TIM_OCPreload_Enable);
			break;
		case THROTTLE:
			/* PWM1 Mode configuration: Channel4 */
			CCR4_Val = ui16_Pulse_Width;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
			TIM_OC4Init(PWM_TIMERBASE, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(PWM_TIMERBASE, TIM_OCPreload_Enable);
			break;
	}
	TIM_ARRPreloadConfig(PWM_TIMERBASE, ENABLE);

  /* PWM_TIMER enable counter */
  TIM_Cmd(PWM_TIMERBASE, ENABLE);
}
