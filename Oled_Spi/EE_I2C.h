/*
*	@author	Eren ERIS
*	@website	http://www.ereneris.net
*	@version v0.0.0
*	@ide	Keil uVison
*	@brief	I2C Liblary 


*/

#ifndef EE_I2C_H
#define EE_I2C_H 161
/**
 * @addtogroup EE_STM32F4xx_Libraries
 * @{
 */

/**
 * @defgroup EE_I2C
 * @brief    I2C library for STM32F4xx
 * @{
 *
 *	\par Pinout
 *	
@verbatim
       |PINSPACK 1   |PINSPACK 2   |PINSPACK 3
I2CX   |SCL   SDA    |SCL   SDA    |SCL   SDA
       |             |             |
I2C1   |PB6   PB7    |PB8   PB9    |PB6   PB9
I2C2   |PB10  PB11   |PF1   PF0    |PH4   PH5
I2C3   |PA8   PC9    |PH7   PH8    |-     -
@endverbatim
 *
 * \par Custom pinout
 *
 * In case these pins are not good for you, you can use
 * @ref TM_I2C_PinsPack_Custom in @ref TM_I2C_Init() function and callback function will be called,
 * where you can initialize your custom pinout for your I2C peripheral
 *
 * Possible changes in your defines.h file:
 * Change x to your I2C used, 1-3
 *	
@verbatim
//By default library support only 7bit long address
#define TM_I2Cx_ACKNOWLEDGED_ADDRESS   I2C_AcknowledgedAddress_7bit
//Library supports I2C mode
#define TM_I2Cx_MODE                   I2C_Mode_I2C
//Own address, if slave mode
#define TM_I2Cx_OWN_ADDRESS            0x00
//By default, disable ack
#define TM_I2Cx_ACK                    I2C_Ack_Disable
//Duty cycle 2, 50%
#define TM_I2Cx_DUTY_CYCLE             I2C_DutyCycle_2
@endverbatim
 *
 * \par Changelog
 *
@verbatim
 Version 0.0.0
  - December 25, 2022
  -  Crated File
  

@endverbatim
 *
 * \par Dependencies
 *
@verbatim
 - STM32F4xx
 - STM32F4xx I2C
 - defines.h
 - attributes.h
@endverbatim
 */
 
#include "stm32f4xx.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "defines.h"

#ifndef EE_I2C_TIMEOUT
#define EE_I2C_TIMEOUT	20000
#endif

#ifndef EE_I2C1_ACKNOWLEDGED_ADDRESS
#define EE_I2C1_ACKNOWLEDGED_ADDRESS I2C_AcknowledgedAddress_7bit
#endif

#ifndef EE_I2C1_MODE
#define EE_I2C1_MODE I2C_Mode_I2C
#endif

#ifndef EE_I2C1_ACK
#define EE_I2C1_ACK I2C_Ack_Disable
#endif

#ifndef EE_I2C1_OWN_DISABLE
#define EE_I2C1_OWN_DISABLE 0X00
#endif

#ifndef EE_I2C1_DUTY_CYCLE
#define EE_I2C1_DUTY_CYCLE I2C_DutyCycle_2
#endif


#ifndef EE_I2C2_ACKNOWLEDGED_ADDRESS
#define EE_I2C2_ACKNOWLEDGED_ADDRESS I2C_AcknowledgedAddress_7bit
#endif

#ifndef EE_I2C2_MODE
#define EE_I2C2_MODE I2C_Mode_I2C
#endif

#ifndef EE_I2C2_ACK
#define EE_I2C2_ACK I2C_Ack_Disable
#endif

#ifndef EE_I2C2_OWN_DISABLE
#define EE_I2C2_OWN_DISABLE 0X00
#endif

#ifndef EE_I2C2_DUTY_CYCLE
#define EE_I2C2_DUTY_CYCLE I2C_DutyCycle_2
#endif

#ifndef EE_I2C3_ACKNOWLEDGED_ADDRESS
#define EE_I2C3_ACKNOWLEDGED_ADDRESS I2C_AcknowledgedAddress_7bit
#endif

#ifndef EE_I2C3_MODE
#define EE_I2C3_MODE I2C_Mode_I2C
#endif

#ifndef EE_I2C3_ACK
#define EE_I2C3_ACK I2C_Ack_Disable
#endif

#ifndef EE_I2C3_OWN_DISABLE
#define EE_I2C3_OWN_DISABLE 0X00
#endif

#ifndef EE_I2C3_DUTY_CYCLE
#define EE_I2C3_DUTY_CYCLE I2C_DutyCycle_2
#endif

#define EE_I2C_CLOCK_STANDART 			100000
#define EE_I2C_CLOCK_FAST_MODE 			400000
#define EE_I2C_CLOCK_FAST_MODE_PLUS	1000000
#define EE_I2C_CLOCK_HIGH_SPEED			3400000

typedef enum{
	TM_I2C_PinsPack_1,
	TM_I2C_PinsPack_2,
	TM_I2C_PinsPack_3,
	TM_I2C_PinsPack_Custom
} EE_I2C1_PinsPack_t;

void EE_I2C_Init(I2C_TypeDef* I2Cx , EE_I2C1_PinsPack_t pinspack, uint32_t clockSpeed);

uint8_t EE_I2C_Read(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg);

void EE_I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

uint8_t EE_I2C_ReadNoRegister(I2C_TypeDef* I2Cx, uint8_t address);

void EE_I2C_Write(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data);

void EE_I2C_WriteMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

void EE_I2C_WriteNoRegister(I2C_TypeDef* I2Cx, uint8_t address, uint8_t data);

void EE_I2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t address, uint8_t* data, uint16_t count);

uint8_t EE_I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t address);

int16_t EE_I2C_Start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction, uint8_t ack);

uint8_t EE_I2C_Stop(I2C_TypeDef* I2Cx);

uint8_t EE_I2C_ReadNack(I2C_TypeDef* I2Cx);

uint8_t EE_I2C_ReadAck(I2C_TypeDef* I2Cx);

void EE_I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);

void EE_I2C_InitCustomPinsCallback(I2C_TypeDef* I2Cx, uint16_t AlternateFunction);

#endif