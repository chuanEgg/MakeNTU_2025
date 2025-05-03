/*
 * AD9850.c
 *
 *  Created on: May 3, 2025
 *      Author: tom1484
 */

#include "AD9850.h"

#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal.h"


const GPIO_Port AD9850_DATA_Ports[8] = {
	  { .channel = GPIOF, .pin = GPIO_PIN_10 },
	  { .channel = GPIOF, .pin = GPIO_PIN_9 },
	  { .channel = GPIOF, .pin = GPIO_PIN_8 },
	  { .channel = GPIOF, .pin = GPIO_PIN_7 },
	  { .channel = GPIOF, .pin = GPIO_PIN_5 },
	  { .channel = GPIOI, .pin = GPIO_PIN_3 },
	  { .channel = GPIOH, .pin = GPIO_PIN_6 },
	  { .channel = GPIOI, .pin = GPIO_PIN_0 },
};
const GPIO_Port AD9850_WORD_LD_Port = { .channel = GPIOI, .pin = GPIO_PIN_1 };
const GPIO_Port AD9850_FREQ_UP_Port = { .channel = GPIOB, .pin = GPIO_PIN_14 };
const GPIO_Port AD9850_RESET_Port   = { .channel = GPIOB, .pin = GPIO_PIN_15 };

uint8_t AD9850_buffer[5];
float AD9850_freq = 0.0;
float AD9850_phase = 0.0;

void GPIO_Write(const GPIO_Port *pin, uint16_t state)
{
	HAL_GPIO_WritePin(pin->channel, pin->pin, state);
}

void AD9850_Init()
{
	GPIO_Write(&AD9850_RESET_Port, GPIO_PIN_SET);
//	HAL_Delay(1);
	GPIO_Write(&AD9850_RESET_Port, GPIO_PIN_RESET);
//	HAL_Delay(1);
}

void AD9850_WriteByte(uint8_t data)
{
	for (int d = 0; d < 8; d++)
	{
		if (data & (1 << d)) GPIO_Write(&AD9850_DATA_Ports[d], GPIO_PIN_SET);
		else                 GPIO_Write(&AD9850_DATA_Ports[d], GPIO_PIN_RESET);
	}
//	HAL_Delay(1);

	GPIO_Write(&AD9850_WORD_LD_Port, GPIO_PIN_SET);
//	HAL_Delay(1);
	GPIO_Write(&AD9850_WORD_LD_Port, GPIO_PIN_RESET);
//	HAL_Delay(1);
}

void AD9850_Write(float freq, float phase)
{
	if (freq == AD9850_freq && phase == AD9850_phase)
		return;
	AD9850_freq = freq;
	AD9850_phase = phase;

	float freq_scale  = freq / BASE_FREQ;
	float phase_scale = phase / BASE_PHASE;

	*((uint32_t *)(AD9850_buffer + 0)) = (uint32_t)freq_scale;
	*((uint8_t *)(AD9850_buffer + 4))  = (uint8_t)phase_scale;

	for (int i = 0; i < 5; i++)
		AD9850_WriteByte(AD9850_buffer[4 - i]);

	GPIO_Write(&AD9850_FREQ_UP_Port, GPIO_PIN_SET);
//	HAL_Delay(1);
	GPIO_Write(&AD9850_FREQ_UP_Port, GPIO_PIN_RESET);
//	HAL_Delay(1);
}
