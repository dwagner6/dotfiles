/***********************************************************************
* FILENAME :        watchdog.c          
*
* DESCRIPTION : Driver implementation for watchdog timer on RPI Pico board
*       
* AUTHOR :    Doug Wagner        START DATE :    25 OCT 23
*
************************************************************************/

#include "watchdog.h"
#include <rp2040/watchdog.h>
#include <rp2040/psm.h>
#include <stdint.h>

#define PSM_WDSEL_BIT_SELECTIONS        0x0000fffc  
#define WATCHDOG_TICK_PRESCALER         0x000c      
  
static uint32_t reload_value;

void configure_watchdog( uint32_t reload )
{
    watchdog -> clr_ctrl = WATCHDOG_CTRL_ENABLE(1);                             
    psm -> set_wdsel = PSM_WDSEL_BIT_SELECTIONS;                                
    watchdog -> set_tick = WATCHDOG_TICK_ENABLE(1) | WATCHDOG_TICK_CYCLES(WATCHDOG_TICK_PRESCALER); 
    
    reload_value = reload*2;
    feed_the_watchdog();

    watchdog -> set_ctrl = WATCHDOG_CTRL_ENABLE_MASK;       
}

void feed_the_watchdog()
{
    watchdog -> load = reload_value;            
}

void disable_watchdog()
{
    watchdog -> clr_ctrl = WATCHDOG_CTRL_ENABLE(1);
}

void enable_watchdog()
{
    watchdog -> set_ctrl = WATCHDOG_CTRL_ENABLE(1);
}