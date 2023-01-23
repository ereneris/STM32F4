/**
  ******************************************************************************
  * @file    USART Intterup Example
  * @author  Eren ERIS
  * @version V0.0.0
  * @date    21-January-2023
  * @brief   Bu Dosya GitHub ve Blogumda yayinlamak üzere olusturulmus Örnektir
  ******************************************************************************
  */
	
#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>
#include "delay.h"
#include <stdio.h>

void UsartInit(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* USART 1 Clock Aktif Edildi*/
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/* GPIOA clock Aktif Edildi */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//GPIO Registeri Ayarlandi
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// TGPIO Alternatif Fonksiyonlar Aktif Edildi
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	//USART Registeri Ayarlandi
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE); // Usart1 Aktif

	
	//Usart 1 Interrupt Için NVIC Registeriini Ayarlama
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART1->CR1 |= USART_CR1_RXNEIE; // USART1 Intterupt RX için Aktif
}

void GPIOInit(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* GPIOD Clock Aktif */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Konfügre Pin12-13-14-15*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void USART1_IRQHandler(void){
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{

		char c  = USART_ReceiveData(USART1);
		USART_SendData(USART1,c);
		USART_SendData(USART1,'\r');
		USART_SendData(USART1,'\n');
		if(c){
			if(c == 'w'){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
			}
			else if(c == 'a'){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
			}
			else if(c == 'd'){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
			}
			else if(c == 's'){
				GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //Usart 1 Rx Intterup Flagi Temizleme
	}
}
void USART_puts(USART_TypeDef* USARTx, volatile char *s){
    while(*s){
        while( !(USARTx->SR & 0x00000040) );
        USART_SendData(USARTx, *s);
        *s++;
    }
}
int main(void){
	SystemCoreClockUpdate();
	DWT_Init();
	UsartInit();
	GPIOInit();
	char dizi[15];
	
	USART_puts(USART1,"Start Data\r\n");

	while(1){
		sprintf(dizi,"sm,%d,%d,%d,%d,\r\n",GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15));
		USART_puts(USART1,dizi);
		DWT_Delay(1000000);
	}

}