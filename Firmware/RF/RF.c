#include "RF.h"

char txbuff[BUFFTX_SIZE];

void RF_config(void)
{
		GPIO_InitTypeDef 	GPIO_InitStructure; 
		USART_InitTypeDef USART_InitStructure;   
		DMA_InitTypeDef  	DMA_InitStructure;
		NVIC_InitTypeDef  NVIC_InitStructure;	
	   
	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		/* Enable DMA1 clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	  /* Connect UART4 pins to AF2 */  
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 

	  /* GPIO Configuration for UART4 Tx */
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* GPIO Configuration for USART Rx */
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		   
	  /* USARTx configured as follow:
			- BaudRate = 115200 baud  
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	  */
	  USART_InitStructure.USART_BaudRate = 57600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  USART_Init(UART4, &USART_InitStructure);
	  
		/* Enable USART */
	  USART_Cmd(UART4, ENABLE);
		
		/* Enable UART4 DMA */
	  USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 
		/* Enable DMA Interrupt to the highest priority */
	  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

		/* Transfer complete interrupt mask */
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
		
		/* DMA1 Stream4 Channel4 for UART4 Tx configuration */			
	  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	  DMA_InitStructure.DMA_BufferSize = BUFFTX_SIZE;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	  DMA_Cmd(DMA1_Stream4, ENABLE);
}
void RF_GainData(char *Data, uint8_t Size)
{
	uint8_t i;
	for (i = 0; i < Size; i++)
		txbuff[i] = Data[i];
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
	DMA1_Stream4->NDTR = Size;
	DMA_Cmd(DMA1_Stream4, ENABLE);
}