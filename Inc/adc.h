#pragma once 

#include "main.h"

void init_adc(void);

extern ADC_HandleTypeDef adc_handle;
// buf_state: 0 = empty, 1 = half full, 2 = full, i got 8bits might as well use em
extern volatile uint8_t buf_state;
extern volatile uint16_t adc_buf[256];
