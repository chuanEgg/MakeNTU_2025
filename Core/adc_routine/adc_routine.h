/*
 * adc_routine.h
 *
 *  Created on: May 3, 2025
 *      Author: choua
 */

#ifndef ADC_ROUTINE_ADC_ROUTINE_H_
#define ADC_ROUTINE_ADC_ROUTINE_H_

#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_adc.h"
#include "../../Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_tim.h"

//total sample rate in kHz
#define ADC_SAMPLE_RATE 	4500
#define ADC_BUFFER_HALF_LEN 1500
#define ADC_BUFFER_LEN 		3000
#define SCREEN_TRIGGERS     4
#define ADC_BUFFER_TIME    		2          // ms
#define ADC_VOLTAGE_MAX         3.3        // V
#define ADC_VOLTAGE_MIN         0		   // V

extern uint8_t adc_raw_buffer[3][ADC_BUFFER_LEN];
extern uint8_t is_top_half; // indicate which half of adc buffer is active

void adcInit(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2, ADC_HandleTypeDef *hadc3, TIM_HandleTypeDef *htim);
void adcStart(TIM_HandleTypeDef *htim);

#endif /* ADC_ROUTINE_ADC_ROUTINE_H_ */
