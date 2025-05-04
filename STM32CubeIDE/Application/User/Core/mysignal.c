/*
 * signal.c
 *
 *  Created on: May 4, 2025
 *      Author: choua
 */

#include "mysignal.h"
#include <stdint.h>


uint8_t start_sample = 0;
uint8_t start_plot = 0;
uint8_t read_encoder = 0;
// -1: set to full mode, 0: doesn't change, 1: set to half mode
int8_t set_relay = 0;
