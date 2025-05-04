/*
 * global_val.c
 *
 *  Created on: May 4, 2025
 *      Author: choua
 */

#include "global_val.h"
#include <stdint.h>

uint8_t trigger_level = 127; // 0-255
uint8_t offset = 128; // 0-255

trigger_mode_typedef trigger_mode = TRIGGER_MODE_FALLING;
int32_t time_scale = 1;             // capture 1 data from every n points


// the pointers to the screen buffer
uint8_t *screen_buff_head = 0;
uint8_t *screen_buff_tail = 0;
uint8_t *screen_buff_start = 0;

/* measures */
float input_v_pp;
float input_frequency;
float input_period;
float x_unit;
float y_unit;
