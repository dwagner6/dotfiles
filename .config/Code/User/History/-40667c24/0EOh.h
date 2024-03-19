/***********************************************************************
* FILENAME :        gpio_irq.h         
*
* DESCRIPTION :     Driver interface for IRQ on RPI Pico GPIO pins
*
* AUTHOR :    Doug Wagner        START DATE :    12 DEC 23
* 
************************************************************************/

#ifndef GPIO_IRQ_H
#define GPIO_IRQ_H

#include <stdint.h>

void register_gpio_irq_callback(uint8_t gpio, void (*pf)());

#endif