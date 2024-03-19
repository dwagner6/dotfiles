/***********************************************************************
* FILENAME :        watchdog.h            
*
* DESCRIPTION : Function declarations RP2040 watchdog timer
*
* AUTHOR :    Doug Wagner        START DATE :    25 OCT 23
*
************************************************************************/
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdint.h>

void configure_watchdog( uint32_t reload );
void feed_the_watchdog();
void enable_watchdog();
void disable_watchdog();

#endif