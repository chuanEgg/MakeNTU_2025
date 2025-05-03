/*
 * sampling.h
 *
 *  Created on: May 3, 2025
 *      Author: choua
 */

#ifndef ADC_SAMPLING_SAMPLING_H_
#define ADC_SAMPLING_SAMPLING_H_

// #include "main.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "adc_routine.h"
#include "global_val.h"

#define ADC_INTERMEDIATE_SIZE	2

// extern trigger_mode_enum trigger_mode = TRIGGER_MODE_FALLING;

extern int32_t time_scale;             // capture 1 data from every n points

// extern uint8_t adc_buffer[3][4800];
extern uint8_t adc_intermediate[ADC_INTERMEDIATE_SIZE][LCD_NUM_POINT];   // should initialize
// extern int8_t screen_data[SCREEN_DATA_SIZE];

extern uint8_t trigger_level;    // 0-255, 128 is the middle level
extern uint8_t offset;

// screen end know where to read the 200 signed data
extern uint8_t* screen_data_start_ptr;
extern uint8_t* screen_frame_start_ptr;
extern uint8_t* screen_frame_end_ptr;		// closed
extern uint8_t* screen_measure_ptr;

extern double v_pp_output;
extern double frequency_output;
extern double period_output;

extern int adc_intermediate_index;

extern volatile uint8_t trigger_found;
// extern volatile uint8_t data_done;
extern volatile uint8_t measure_done;

int captureData(void);
// void measure(void);


#endif /* ADC_SAMPLING_SAMPLING_H_ */
