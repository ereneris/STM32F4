/**
  ******************************************************************************
  * @file    USART Intterup Example
  * @author  Eren ERIS
  * @version V0.0.0
  * @date    21-January-2023
  * @brief   Bu Dosya GitHub ve Blogumda yayinlamak üzere olusturulmus Örnektir
  ******************************************************************************
	
	Channel					ADC1	ADC2	ADC3
	APB							2			2			2
	ADC Channel 0		PA0		PA0		PA0
	ADC Channel 1		PA1		PA1		PA1
	ADC Channel 2		PA2		PA2		PA2
	ADC Channel 3		PA3		PA3		PA3
	ADC Channel 4		PA4		PA4		PF6
	ADC Channel 5		PA5		PA5		PF7
	ADC Channel 6		PA6		PA6		PF8
	ADC Channel 7		PA7		PA7		PF9
	ADC Channel 8		PB0		PB0		PF10
	ADC Channel 9		PB1		PB1		PF3
	ADC Channel 10	PC0		PC0		PC0
	ADC Channel 11	PC1		PC1		PC1
	ADC Channel 12	PC2		PC2		PC2
	ADC Channel 13	PC3		PC3		PC3
	ADC Channel 14	PC4		PC4		PF4
	ADC Channel 15	PC5		PC5		PF5
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

	/* GPIOB clock Aktif Edildi */
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

void ADCInit(void){
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* GPIOA clock Aktif Edildi */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	/* Enable ADC clock */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	/* Init ADC settings */
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	/* Set resolution */
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_8Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	/* Initialize ADC */
	ADC_Init(ADC1, &ADC_InitStruct);
	
	/* Enable ADC */
	ADC1->CR2 |= ADC_CR2_ADON;
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

uint16_t ADC_Read(uint8_t channel) {
	uint32_t timeout = 0xFFF;
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_15Cycles);
	/* ADC Cevrimini Baslatma */
	ADC1->CR2 |= (uint32_t)ADC_CR2_SWSTART;
	/* Donen Sonucu Bekleme*/
	while (!(ADC1->SR & ADC_SR_EOC)) {
		if (timeout-- == 0x00) {
			return 0;
		}
	}
	/* Okunan Sonucu Dondurme */
	return ADC1->DR;
}

int main(void){
	SystemCoreClockUpdate();
	DWT_Init();
	UsartInit();
	GPIOInit();
	ADCInit();
	char dizi[15];
	
	USART_puts(USART1,"Start Data\r\n");

	while(1){
		sprintf(dizi,"sm,%d,%d,%d,%d,\r\n",GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14),GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15));
		USART_puts(USART1,dizi);
		sprintf(dizi,"sa,%4d,\r\n",ADC_Read(ADC_Channel_0));
		USART_puts(USART1,dizi);
		DWT_Delay(1000000);
	}

}