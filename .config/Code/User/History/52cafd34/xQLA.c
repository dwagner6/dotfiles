#include "power_supply.h"
#include "systick_int.h"
#include "interrupt.h"
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