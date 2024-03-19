/***********************************************************************
* FILENAME :        pb0.h          
*
* DESCRIPTION : Driver declarations for active-low push-button driver
*       
* AUTHOR :    Doug Wagner        START DATE :    01 OCT 23
*
************************************************************************/

#ifndef PB0_H
#define PB0_H

#include <stdbool.h>
#include <stdint.h>

void configure_pb( uint8_t gpio );
_Bool pb0_pressed();

#endif
