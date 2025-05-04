/*
 * global_val.h
 *
 *  Created on: May 4, 2025
 *      Author: choua
 */

#ifndef __GLOBAL_VAL_H_
#define __GLOBAL_VAL_H_

#include "global_val.h"

#include <stdint.h>

#define M_PI 3.14159265358979323846

#define LCD_NUM_POINT  200 // num of points on the screen

typedef enum
{
    TRIGGER_MODE_RISING,
    TRIGGER_MODE_FALLING,
//    NUM_TRIGGER_MODES,
	TRIGGER_MODE_BOTH
} trigger_mode_typedef;

extern uint8_t trigger_level; // 0-255, maintained by GFX
extern uint8_t v_offset; // 0-255, maintained by GFX

extern trigger_mode_typedef trigger_mode;
extern int32_t time_scale;             // capture 1 data from every n points

extern uint8_t *screen_buff_head;
extern uint8_t *screen_buff_tail;
extern uint8_t *screen_buff_start;

extern float input_v_pp;
extern float input_frequency;
extern float input_period;

#endif /* APPLICATION_USER_GLOBAL_VAL_H_ */
