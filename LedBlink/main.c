#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "delay.h"

GPIO_InitTypeDef  GPIO_InitStructure;



int main(void)
{

	SystemInit();
	SystemCoreClockUpdate();   
	DWT_Init();
	
	
	/* GPIOE Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PE3, PE2 and PE7 in output push-pull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_12| GPIO_Pin_14| GPIO_Pin_15);
	
	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
		DWT_Delay(1000000);
	}

}
