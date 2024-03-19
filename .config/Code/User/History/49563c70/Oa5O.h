/***********************************************************************
* FILENAME :        adc.h          
*
* DESCRIPTION :     Driver interface for ADC0 on GPIO26 of RPI Pico
*
* AUTHOR :    Doug Wagner        START DATE :    12 DEC 23
* 
************************************************************************/

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void configure_adc();
void enable_adc();
void disable_adc();
uint16_t adc_to_millivolts(uint16_t adc_value);
uint16_t get_adc_raw();

#endif