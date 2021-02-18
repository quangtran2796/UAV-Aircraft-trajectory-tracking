#ifndef GPIO_H
#define GPIO_H

#include "include.h"

#define MODE1 0x00
#define MODE2 0x01
#define MODE3 0x02
#define MODE4 0x03
#define LED_BASE GPIOA
#define SW1_BASE GPIOC
#define SW2_BASE GPIOB
#define BT1_BASE GPIOB
#define BT2_BASE GPIOE
#define TRG_BASE GPIOC

typedef enum{
	LED_RED = GPIO_Pin_2,
	LED_GREEN = GPIO_Pin_4,
	LED_BLUE = GPIO_Pin_5,
	SW1 = GPIO_Pin_4,
	SW2 = GPIO_Pin_2,
	BTN1 = GPIO_Pin_8,
	BTN2 = GPIO_Pin_0,
	TRIGGER = GPIO_Pin_6
} IO_Pin;


void GPIO_Config(void);
void GPIO_LED_On(IO_Pin Pin);
void GPIO_LED_Off(IO_Pin Pin);
void GPIO_LED_Blink(IO_Pin Pin, uint16_t cycle_ms);
uint8_t GPIO_Switch_Read(void);
uint8_t GPIO_Button_Read(IO_Pin Pin);
bool GPIO_Trigger_Read(void);

#endif /* GPIO_H */
