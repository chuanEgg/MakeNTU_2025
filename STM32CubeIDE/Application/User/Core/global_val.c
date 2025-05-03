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
