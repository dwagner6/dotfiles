#include "i2c0.h"
#include "uclib.h"
#include "tps55289.h"
#include "gpio13_int.h"
#include "pb.h"
#include "lcd.h"
#include "adc.h"
#include "systick_int.h"
#include "interrupt.h"
#include "watchdog.h"
#include <rp2040/i2c.h>
#include <stdbool.h>
#include <stdint.h>

#define VOUT_UP_PB_LOC     15
#define VOUT_DOWN_PB_LOC   14
#define ENABLE_PB_LOC   13

#define VOUT_STEP_MV    100
#define LCD_VOUT_FIELD  0x06
#define LCD_IMON_FIELD  0x06 
#define LCD_EN_FIELD    0x0C
#define DIR_DOWN        0
#define DIR_UP          1





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

