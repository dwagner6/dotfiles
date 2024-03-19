#include "gpio11_int.h"
#include <rp2040/io_bank0.h>
#include "gpio_irq.h"

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

static _Bool pin_state;

_Bool get_gpio11();
static void callback();

void configure_gpio11_irq( void )
{
    resets -> clr_reset = 
        RESETS_RESET_IO_BANK0_MASK
        | RESETS_RESET_PADS_BANK0_MASK;

    while(! (resets -> reset_done & RESETS_RESET_IO_BANK0_MASK));
    while(! (resets -> reset_done & RESETS_RESET_PADS_BANK0_MASK));

    uint32_t const out_pads_bank0_gpio = 
	                    PADS_BANK0_GPIO25_OD(0) 
	                    | PADS_BANK0_GPIO25_IE(1) 
	                    | PADS_BANK0_GPIO25_DRIVE(0) 
	                    | PADS_BANK0_GPIO25_PUE(0) 
	                    | PADS_BANK0_GPIO25_PDE(0) 
	                    | PADS_BANK0_GPIO25_SCHMITT(0) 
	                    | PADS_BANK0_GPIO25_SLEWFAST(0);
    
    uint32_t const out_io_bank0gpio_ctrl = 
	                    IO_BANK0_GPIO25_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_FUNCSEL(5);

    pads_bank0 -> GPIO(11) = out_pads_bank0_gpio;
    io_bank0 -> GPIO_CTRL(11) = out_io_bank0gpio_ctrl;

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