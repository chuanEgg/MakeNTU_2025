/*
 * AD9850.h
 *
 *  Created on: May 3, 2025
 *      Author: tom1484
 */

#ifndef AD9850_AD9850_H_
#define AD9850_AD9850_H_

#include "../../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal.h"

typedef struct
{
	GPIO_TypeDef *channel;
	uint16_t pin;
} GPIO_Port;

#define BASE_FREQ  ((62500000.0) / (float)(0x80000000))
#define BASE_PHASE ((1.0) / (float)(0x80))  // WARNING: Not sure about the maximum phase

void GPIO_Write(const GPIO_Port *pin, uint16_t state);
void AD9850_Init();
void AD9850_WriteByte(uint8_t data);
void AD9850_Write(float freq, float phase);

#endif /* ADC_ROUTINE_ADC_ROUTINE_H_ */
