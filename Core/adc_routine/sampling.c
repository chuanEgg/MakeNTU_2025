/*
 * sampling.c
 *
 *  Created on: May 3, 2025
 *      Author: choua
 */

#include "global_val.h"
#include "sampling.h"
#include "../adc_routine/adc_routine.h"


extern uint8_t is_top_half;      // indicate which half of adc buffer is active, adc-dma end control



// uint8_t adc_buffer[3][4800];
// data points to screen
uint8_t adc_intermediate[ADC_INTERMEDIATE_SIZE][LCD_NUM_POINT] = {0};
// int8_t screen_data[SCREEN_DATA_SIZE];

uint8_t* adc_intermediate_start_ptr;
uint8_t* adc_intermediate_end_ptr;		// closed

int adc_intermediate_index = 0;
uint8_t* adc_intermediate_ptr;
int half_screen_size = LCD_NUM_POINT / 2;
int half_one_adc_buffer_size = ADC_BUFFER_HALF_LEN;

extern uint8_t trigger_level;    // 0-255, 128 is the middle level
extern uint8_t offset;

uint8_t prev_val;
uint8_t curr_val;

// uint8_t* adc_buffer_read_start_ptr;
// uint8_t* adc_buffer_read_end_ptr;
// uint8_t* adc_buffer_read_ptr_arr[3];
// uint8_t* adc_buffer_read_ptr;
// uint8_t* adc_buffer_after_trigger_read_end_ptr;

// uint8_t* adc_buffer_read_find_trigger_start_ptr;
// uint8_t* adc_buffer_read_find_trigger_end_ptr;

int adc_buffer_read_idx;
int adc_buffer_after_trigger_read_end_idx;
int adc_buffer_read_find_trigger_index_start;
int adc_buffer_read_index_end;

// screen end know where to read the 200 signed data
uint8_t* screen_data_start_ptr;
uint8_t* screen_frame_start_ptr;
uint8_t* screen_frame_end_ptr;		// closed
uint8_t* screen_measure_ptr;


double v_pp_output;
double frequency_output;
double period_output;

int trigger_crossing_count;
double screen_frame_time;

int measure_loop_index;
uint8_t max_val;
uint8_t min_val;

const uint8_t zero_val = 0;

int adc_buffer_read_index;

int i = 0;
uint8_t volatile trigger_found = 0;
// uint8_t volatile data_done = 0;
uint8_t volatile measure_done = 0;
uint8_t volatile initial_data = 1;
int screen_frame_point_count = 0;

int captureData(void)
{

    if (is_top_half)
    {
    	adc_buffer_read_idx = 0;
    	adc_buffer_read_index_end = half_one_adc_buffer_size * 3;
    }
    else
    {
    	adc_buffer_read_idx = half_one_adc_buffer_size * 3;
    	adc_buffer_read_index_end = half_one_adc_buffer_size * 6;
    }


    if (initial_data || measure_done == 1)
    {
    	initial_data = 0;	// never set high again in program
    	measure_done = 0;
    	trigger_found = 0;
    	// data_done = 0;
    	screen_frame_point_count = 0;

    	if (!initial_data)
    	{
    		adc_intermediate_index = adc_intermediate_index == ADC_INTERMEDIATE_SIZE - 1 ? 0 : adc_intermediate_index + 1;
    	}

    	adc_intermediate_start_ptr = adc_intermediate[adc_intermediate_index];
		adc_intermediate_end_ptr = adc_intermediate_start_ptr + LCD_NUM_POINT - 1;

		screen_frame_start_ptr = adc_intermediate_start_ptr;
		screen_frame_end_ptr = adc_intermediate_end_ptr;

		adc_intermediate_ptr = adc_intermediate_start_ptr;

		for (i = 0; i < half_screen_size; i++)
		{
			if (i == half_screen_size - 1)
			{
				prev_val = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
			}
			*adc_intermediate_ptr = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
			adc_intermediate_ptr = adc_intermediate_ptr == adc_intermediate_end_ptr ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
			adc_buffer_read_idx += time_scale;
		}

		for (; adc_buffer_read_idx < adc_buffer_read_index_end; adc_buffer_read_idx += time_scale)
		{
			curr_val = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
			*adc_intermediate_ptr = curr_val;

			switch (trigger_mode)
			{
				case TRIGGER_MODE_RISING :
					trigger_found = (prev_val <= trigger_level && curr_val > trigger_level);
					break;
				case TRIGGER_MODE_FALLING :
					trigger_found = (prev_val >= trigger_level && curr_val < trigger_level);
					break;
				case TRIGGER_MODE_BOTH :
					trigger_found = (prev_val <= trigger_level && curr_val > trigger_level) || (prev_val >= trigger_level && curr_val < trigger_level);
					break;
			}

			if (trigger_found)
			{
				screen_frame_point_count = half_screen_size + 1;

				adc_buffer_read_idx += time_scale;

				adc_intermediate_ptr = (adc_intermediate_ptr == adc_intermediate_end_ptr) ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;

				for (; adc_buffer_read_idx < adc_buffer_read_index_end && screen_frame_point_count < LCD_NUM_POINT; adc_buffer_read_idx += time_scale)
				{
					*adc_intermediate_ptr = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
					adc_intermediate_ptr = (adc_intermediate_ptr == adc_intermediate_end_ptr) ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
					screen_frame_point_count++;
				}

				if (screen_frame_point_count == LCD_NUM_POINT)
				{
					screen_data_start_ptr = adc_intermediate_ptr;
					// data_done = 1;

					trigger_crossing_count = 0;
					screen_measure_ptr = screen_data_start_ptr;
					prev_val = *screen_measure_ptr;
					max_val = prev_val;
					min_val = prev_val;
					screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;

					for (measure_loop_index = 1; measure_loop_index < LCD_NUM_POINT; measure_loop_index++)
					{
						curr_val = *screen_measure_ptr;
						if (((prev_val >= trigger_level) && (curr_val < trigger_level)) || ((prev_val <= trigger_level) && (curr_val > trigger_level)))
						{
							trigger_crossing_count++;
						}

						max_val = (curr_val > max_val) ? curr_val : max_val;
						min_val = (curr_val < min_val) ? curr_val : min_val;

						prev_val = curr_val;
						screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;
					}

					v_pp_output = (double)(max_val - min_val) * (ADC_VOLTAGE_MAX - ADC_VOLTAGE_MIN) / 255.0;
					frequency_output = (double)(1000 * trigger_crossing_count * ADC_SAMPLE_RATE) / (2 * LCD_NUM_POINT * time_scale);
					period_output = 1.0 / frequency_output;

					measure_done = 1;
					return 1;
				}

				break;
			}

			prev_val = curr_val;
			adc_intermediate_ptr = adc_intermediate_ptr == adc_intermediate_end_ptr ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
		}

    }
    else if (trigger_found == 1)
    {
    	for (; adc_buffer_read_idx < adc_buffer_read_index_end && screen_frame_point_count < LCD_NUM_POINT; adc_buffer_read_idx += time_scale)
		{
			*adc_intermediate_ptr = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
			adc_intermediate_ptr = (adc_intermediate_ptr == adc_intermediate_end_ptr) ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
			screen_frame_point_count++;
		}

		if (screen_frame_point_count == LCD_NUM_POINT)
		{
			screen_data_start_ptr = adc_intermediate_ptr;
			// data_done = 1;

			trigger_crossing_count = 0;
			screen_measure_ptr = screen_data_start_ptr;
			prev_val = *screen_measure_ptr;
			max_val = prev_val;
			min_val = prev_val;
			screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;

			for (measure_loop_index = 1; measure_loop_index < LCD_NUM_POINT; measure_loop_index++)
			{
				curr_val = *screen_measure_ptr;
				if (((prev_val >= trigger_level) && (curr_val < trigger_level)) || ((prev_val <= trigger_level) && (curr_val > trigger_level)))
				{
					trigger_crossing_count++;
				}

				max_val = (curr_val > max_val) ? curr_val : max_val;
				min_val = (curr_val < min_val) ? curr_val : min_val;

				prev_val = curr_val;
				screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;
			}

			v_pp_output = (double)(max_val - min_val) * (ADC_VOLTAGE_MAX - ADC_VOLTAGE_MIN) / 255.0;
			frequency_output = (double)(1000 * trigger_crossing_count * ADC_SAMPLE_RATE) / (2 * LCD_NUM_POINT * time_scale);
			period_output = 1.0 / frequency_output;

			measure_done = 1;
			return 1;
		}
    }
    else if (trigger_found == 0)
    {
    	for (; adc_buffer_read_idx < adc_buffer_read_index_end; adc_buffer_read_idx += time_scale)
		{
			curr_val = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
			*adc_intermediate_ptr = curr_val;

			switch (trigger_mode)
			{
				case TRIGGER_MODE_RISING :
					trigger_found = (prev_val <= trigger_level && curr_val > trigger_level);
					break;
				case TRIGGER_MODE_FALLING :
					trigger_found = (prev_val >= trigger_level && curr_val < trigger_level);
					break;
				case TRIGGER_MODE_BOTH :
					trigger_found = (prev_val <= trigger_level && curr_val > trigger_level) || (prev_val >= trigger_level && curr_val < trigger_level);
					break;
			}

			if (trigger_found)
			{
				screen_frame_point_count = half_screen_size + 1;

				adc_buffer_read_idx += time_scale;

				adc_intermediate_ptr = (adc_intermediate_ptr == adc_intermediate_end_ptr) ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;

				for (; adc_buffer_read_idx < adc_buffer_read_index_end && screen_frame_point_count < LCD_NUM_POINT; adc_buffer_read_idx += time_scale)
				{
					*adc_intermediate_ptr = adc_raw_buffer[adc_buffer_read_idx % 3][adc_buffer_read_idx / 3];
					adc_intermediate_ptr = (adc_intermediate_ptr == adc_intermediate_end_ptr) ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
					screen_frame_point_count++;
				}

				if (screen_frame_point_count == LCD_NUM_POINT)
				{
					screen_data_start_ptr = adc_intermediate_ptr;
					// data_done = 1;

					trigger_crossing_count = 0;
					screen_measure_ptr = screen_data_start_ptr;
					prev_val = *screen_measure_ptr;
					max_val = prev_val;
					min_val = prev_val;
					screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;

					for (measure_loop_index = 1; measure_loop_index < LCD_NUM_POINT; measure_loop_index++)
					{
						curr_val = *screen_measure_ptr;
						if (((prev_val >= trigger_level) && (curr_val < trigger_level)) || ((prev_val <= trigger_level) && (curr_val > trigger_level)))
						{
							trigger_crossing_count++;
						}

						max_val = (curr_val > max_val) ? curr_val : max_val;
						min_val = (curr_val < min_val) ? curr_val : min_val;

						prev_val = curr_val;
						screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;
					}

					v_pp_output = (double)(max_val - min_val) * (ADC_VOLTAGE_MAX - ADC_VOLTAGE_MIN) / 255.0;
					frequency_output = (double)(1000 * trigger_crossing_count * ADC_SAMPLE_RATE) / (2 * LCD_NUM_POINT * time_scale);
					period_output = 1.0 / frequency_output;

					measure_done = 1;
					return 1;
				}

				break;
			}

			prev_val = curr_val;
			adc_intermediate_ptr = adc_intermediate_ptr == adc_intermediate_end_ptr ? adc_intermediate_start_ptr : adc_intermediate_ptr + 1;
		}
    }

    return 0;
}

/*
void measure(void)
{
    trigger_crossing_count = 0;
    screen_measure_ptr = screen_data_start_ptr;
    prev_val = *screen_measure_ptr;
    max_val = prev_val;
    min_val = prev_val;
    screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;

    for (measure_loop_index = 1; measure_loop_index < LCD_NUM_POINT; measure_loop_index++)
    {
        curr_val = *screen_measure_ptr;
        if (((prev_val >= trigger_level) && (curr_val < trigger_level)) || ((prev_val <= trigger_level) && (curr_val > trigger_level)))
        {
            trigger_crossing_count++;
        }

        max_val = (curr_val > max_val) ? curr_val : max_val;
        min_val = (curr_val < min_val) ? curr_val : min_val;

        prev_val = curr_val;
        screen_measure_ptr = (screen_measure_ptr == screen_frame_end_ptr) ? screen_frame_start_ptr : screen_measure_ptr + 1;
    }

    v_pp_output = (double)(max_val - min_val) * (ADC_VOLTAGE_MAX - ADC_VOLTAGE_MIN) / 255.0;
<<<<<<< HEAD
    frequency_output = (double)(trigger_crossing_count * ADC_SAMPLE_RATE) / (2 * LCD_NUM_POINT * time_scale);
=======
    frequency_output = (double)(1000 * trigger_crossing_count * ADC_SAMPLE_RATE) / (2 * LCD_NUM_POINT * time_scale);
>>>>>>> b241d7bb1767968b17bb43b6a976625d0412d740
    period_output = 1.0 / frequency_output;

}
*/


