#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_rcc.h>
#include "delay.h"



void _GPIO_Config(void);
void _Timer_Config(void);
void TIM2_IRQHandler(void);

int main(void)
{

	SystemInit();
	SystemCoreClockUpdate();   
	DWT_Init();
	_GPIO_Config();
	
	_Timer_Config();
	
	
	GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15);
	
	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
		DWT_Delay(1000000);
	}

}

void _GPIO_Config(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* GPIOE Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PE3, PE2 and PE7 in output push-pull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void _Timer_Config(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84;
 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 
	NVIC_Init(&NVIC_InitStructure);
	
}


void TIM2_IRQHandler(void)
{
	static uint8_t tick = 0;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if(tick++ == 200)
		{
			tick = 0;
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		}
	}
}
