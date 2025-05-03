/*
 * adc_routine.c
 *
 *  Created on: May 3, 2025
 *      Author: choua
 */

#include "adc_routine.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_adc.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_tim.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_def.h"

#include <stdint.h>

uint8_t adc_raw_buffer[3][ADC_BUFFER_LEN] = {0};
uint32_t adc_conv_cplt[3] = {0};
uint32_t adc_half_conv_cplt[3] = {0};

void adcInit(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2, ADC_HandleTypeDef *hadc3, TIM_HandleTypeDef *htim)
{
    HAL_ADC_Start_DMA(hadc1, (uint32_t*)(adc_raw_buffer[0]), ADC_BUFFER_LEN);
    HAL_ADC_Start_DMA(hadc2, (uint32_t*)(adc_raw_buffer[1]), ADC_BUFFER_LEN);
    HAL_ADC_Start_DMA(hadc3, (uint32_t*)(adc_raw_buffer[2]), ADC_BUFFER_LEN);
    /* Set the TIM channel state */
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
    /* Enable the Output compare channel */
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_BUSY);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_3, TIM_CCx_ENABLE);
    __HAL_TIM_MOE_ENABLE(htim);
}

void adcStart(TIM_HandleTypeDef *htim)
{
    __HAL_TIM_ENABLE(htim);
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance == ADC1)
    {
	      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);
        adc_half_conv_cplt[0]++;
    }
    else if(hadc->Instance == ADC2)
    {
        adc_half_conv_cplt[1]++;
    }
    else if(hadc->Instance == ADC3)
    {
        adc_half_conv_cplt[2]++;
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC1)
	{
	      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);
		adc_conv_cplt[0]++;
	}
	else if(hadc->Instance == ADC2)
	{
		adc_conv_cplt[1]++;
	}
	else if(hadc->Instance == ADC3)
	{
		adc_conv_cplt[2]++;
	}
}
