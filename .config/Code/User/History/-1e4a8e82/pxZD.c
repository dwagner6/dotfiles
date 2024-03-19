#include "gpio13_int.h"
#include <rp2040/io_bank0.h>
#include "gpio_irq.h"

static _Bool pin_state;

_Bool get_gpio13();
static void callback();

void configure_gpio13_irq( void )
{
    register_gpio_irq_callback(13, callback);
    io_bank0 -> proc0_inte1 |= (IO_BANK0_PROC0_INTE1_GPIO13_EDGE_LOW_MASK 
    | IO_BANK0_PROC0_INTE1_GPIO13_EDGE_HIGH_MASK);
}

static void callback()
{
    if(io_bank0 -> proc0_ints1 & IO_BANK0_PROC0_INTS1_GPIO13_EDGE_LOW_MASK)
        pin_state = true;
    else
        pin_state = false;
}

_Bool get_gpio13()
{
    if(pin_state == true)
        return true;
    else
    {
        pin_state = false;
        return false;
    }
}