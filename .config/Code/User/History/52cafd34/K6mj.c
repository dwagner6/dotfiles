/***********************************************************************
* FILENAME :        final_project.c         
*
* DESCRIPTION :     Final project for EECE 458 Embedded Systems
*           Implements a programmable power supply with UI pushbuttons,
*           LCD display, current monitoring, and short circuit protection.
*           Based around TPS55289 evaluation board from TI
*
* AUTHOR :    Doug Wagner        START DATE :    12 DEC 23
* 
************************************************************************/

#include "power_supply.h"
#include "systick_int.h"
#include "interrupt.h"
#include "lcd.h"
#include "watchdog.h"
#include <rp2040/i2c.h>
#include <stdbool.h>
#include <stdint.h>

int main()
{
    disable_irq();
    configure_systick();
    systick_register_callback(lcd_fsm);
    systick_register_callback(power_supply_fsm);
    systick_register_callback(feed_the_watchdog);
    configure_watchdog(1500);
    configure_power_supply();
    enable_irq();

    while(1)
    {
        if(!systick_has_fired())
        {
            asm("WFI");
            continue;
        }
    }
    return 0;
}