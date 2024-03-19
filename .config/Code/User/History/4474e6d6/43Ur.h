/***********************************************************************
* FILENAME :        pb0.h          
*
* DESCRIPTION : Driver declarations for active-low push-button driver
*       
* AUTHOR :    Doug Wagner        START DATE :    01 OCT 23
*
************************************************************************/

#ifndef PB_H
#define PB_H

#include <stdbool.h>
#include <stdint.h>

void configure_pb( uint8_t gpio );
_Bool get_pb_state(uint8_t gpio);

#endif
