/***********************************************************************
* FILENAME :        gpio11_int.h          
*
* DESCRIPTION :     Driver interface for LEVEL_HIGH IRQ on GPIO11
*
* AUTHOR :    Doug Wagner        START DATE :    12 DEC 23
* 
************************************************************************/

#ifndef GPIO11_INT_H
#define GPIO11_INT_H

#include <stdbool.h>

_Bool get_gpio11();
void configure_gpio11_irq( void );

#endif