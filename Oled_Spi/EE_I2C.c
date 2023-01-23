#include "EE_I2C.h"

static uint32_t	EE_I2C_Timeout;
static uint32_t TM_I2C_INT_Clocks[3] = {0xffffffff,0xffffffff,0xffffffff};

/* Private defines */
#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

GPIO_InitTypeDef  GPIO_InitStructure;

static void EE_I2C1_INT_InitPins(EE_I2C_PinsPack_t pinspack);
static void EE_I2C2_INT_InitPins(EE_I2C_PinsPack_t pinspack);
static void EE_I2C3_INT_InitPins(EE_I2C_PinsPack_t pinspack);

void EE_I2C_Init(I2C_TypeDef* I2Cx , EE_I2C1_PinsPack_t pinspack, uint32_t clockSpeed){
	I2C_InitTypeDef i2c_InitStruct;
	
	if(I2Cx == I2C1){
		//Enable I2C1 Clock
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		
		//Pin Configration
		
	}
}






/* Private functions */
static void EE_I2C1_INT_InitPins(EE_I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == EE_I2C_PinsPack_1) {
		RCC->APB1ENR |= RCC_AHB1Periph_GPIOB;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
#endif
#if defined(GPIOB)
	if (pinspack == EE_I2C_PinsPack_2) {
		RCC->APB1ENR |= RCC_AHB1Periph_GPIOB;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
#endif
#if defined(GPIOB)
	if (pinspack == EE_I2C_PinsPack_3) {
		RCC->APB1ENR |= RCC_AHB1Periph_GPIOB;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
#endif

}

static void EE_I2C2_INT_InitPins(EE_I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == TM_I2C_PinsPack_1) {
		TM_GPIO_InitAlternate(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C2);
	}
#endif
#if defined(GPIOF)
	if (pinspack == TM_I2C_PinsPack_2) {
		TM_GPIO_InitAlternate(GPIOF, GPIO_PIN_0 | GPIO_PIN_1, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C2);
	}
#endif
#if defined(GPIOH)
	if (pinspack == TM_I2C_PinsPack_3) {
		TM_GPIO_InitAlternate(GPIOH, GPIO_PIN_4 | GPIO_PIN_5, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C2);
	}
#endif
	if (pinspack == TM_I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		TM_I2C_InitCustomPinsCallback(I2C2, GPIO_AF_I2C2);
	}
}

static void EE_I2C3_INT_InitPins(EE_I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOA) && defined(GPIOC)
	if (pinspack == TM_I2C_PinsPack_1) {
		TM_GPIO_InitAlternate(GPIOA, GPIO_PIN_8, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C3);
		TM_GPIO_InitAlternate(GPIOC, GPIO_PIN_9, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C3);
	}
#endif
#if defined(GPIOH)
	if (pinspack == TM_I2C_PinsPack_2) {
		TM_GPIO_InitAlternate(GPIOH, GPIO_PIN_7 | GPIO_PIN_8, TM_GPIO_OType_OD, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium, GPIO_AF_I2C3);
	}
#endif
	if (pinspack == TM_I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		TM_I2C_InitCustomPinsCallback(I2C3, GPIO_AF_I2C3);
	}
}