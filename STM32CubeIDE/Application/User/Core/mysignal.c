/*
 * signal.c
 *
 *  Created on: May 4, 2025
 *      Author: choua
 */

#include "mysignal.h"
#include <stdint.h>


uint8_t start_sample = 0;
uint8_t start_plot = 0; // set to true when graph needs to be updated
uint8_t read_encoder = 0;