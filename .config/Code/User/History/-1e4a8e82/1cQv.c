#include "gpio11_int.h"
#include <rp2040/io_bank0.h>
#include "gpio_irq.h"

static _Bool pin_state;

_Bool get_gpio11();
static void callback();

void configure_gpio11_irq( void )
{
    register_gpio_irq_callback(11, callback);
    io_bank0 -> proc0_inte1 |= (IO_BANK0_PROC0_INTE1_GPIO11_LEVEL_HIGH_MASK)
}

static void callback()
{
    if(io_bank0 -> proc0_ints1 & IO_BANK0_PROC0_INTS1_GPIO11_LEVEL_HIGH_MASK)
        pin_state = true;
    else
        pin_state = false;
}

_Bool get_gpio11()
{
    return pin_state;
}