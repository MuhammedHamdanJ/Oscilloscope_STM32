#pragma once 

#include "main.h"

void init_adc(void);
uint16_t read_adc(void);

extern ADC_HandleTypeDef adc_handle;

