#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void configure_adc();
void enable_adc();
void disable_adc();
uint16_t adc_to_millivolts(uint16_t adc_value);
uint16_t get_adc_raw();

#endif