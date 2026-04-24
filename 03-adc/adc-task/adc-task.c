#include "hardware/adc.h"
#include <stdio.h>
#include "pico/stdio.h"
#include "adc-task.h"
#include "pico/time.h"

const int leg=26;
const int channel=0;
const int t=4;

void adcInit() {
    adc_init();
    adc_gpio_init(leg);
    adc_set_temp_sensor_enabled(true);
}

float adc_voltage() {
    adc_select_input(channel);
    uint16_t voltage_counts = adc_read();
    float voltage_V=(voltage_counts * 3.3f) / 4096.0f;
    return voltage_V;
}

float adc_temp() {
    adc_select_input(t);
    uint16_t voltage_counts = adc_read();
    float temp_V=(voltage_counts * 3.3f) / 4096.0f;
    float temp_C = 27.0f - (temp_V - 0.706f) / 0.001721f;
    return temp_C;
}


int adc_state=ADC_TASK_STATE_IDLE;
uint64_t time;

uint64_t ADC_TASK_MEAS_PERIOD_US=100000;

void adc_task_set_state() {
    if(adc_state==ADC_TASK_STATE_IDLE) {time=time_us_64();adc_state=ADC_TASK_STATE_RUN;}
    else adc_state=ADC_TASK_STATE_IDLE;
}

void adc_task_handle() {
    if(adc_state==ADC_TASK_STATE_IDLE) return;
    uint64_t now = time_us_64();
    if(now - time >= ADC_TASK_MEAS_PERIOD_US) {
        float voltage = adc_voltage();
        float temp = adc_temp();
        printf("%f %f\n", voltage, temp);
        time = now;
    }
}