#pragma once

#include <stdint.h>

void adcInit();
float adc_voltage();
float adc_temp();


typedef enum
{
	ADC_TASK_STATE_IDLE = 0,
	ADC_TASK_STATE_RUN = 1,
} adc_task_state_t;

void adc_task_handle();
void adc_task_set_state();