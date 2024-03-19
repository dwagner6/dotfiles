#include "pin27.h"
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>
#include "gpio_irq.h"
#include <stdbool.h>

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

#define PIN27_RESETS    (RESETS_RESET_IO_BANK0_MASK | RESETS_RESET_PADS_BANK0_MASK)

static _Bool pin_state;

_Bool get_pin27();
static void callback();

void configure_pin27( void )
{
    resets -> clr_reset = PIN27_RESETS;

    while(! (resets -> reset_done && RESETS_RESET_IO_BANK0_MASK))
        continue;
    
    while(! (resets -> reset_done && RESETS_RESET_PADS_BANK0_MASK))
        continue;
    
    uint32_t const out_pads_bank0_gpio = 
	                    PADS_BANK0_GPIO27_OD(0) 
	                    | PADS_BANK0_GPIO27_IE(1) 
	                    | PADS_BANK0_GPIO27_DRIVE(0) 
	                    | PADS_BANK0_GPIO27_PUE(1) 
	                    | PADS_BANK0_GPIO27_PDE(0) 
	                    | PADS_BANK0_GPIO27_SCHMITT(0) 
	                    | PADS_BANK0_GPIO27_SLEWFAST(0);

    uint32_t const out_io_bank0gpio_ctrl = 
	                    IO_BANK0_GPIO27_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO27_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO27_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO27_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO27_CTRL_FUNCSEL(5);

    pads_bank0 -> GPIO(13)       = out_pads_bank0_gpio;
	io_bank0 -> GPIO_CTRL(13)   = out_io_bank0gpio_ctrl;

    register_gpio_irq_callback(13, callback);
    io_bank0 -> proc0_inte2 |= (IO_BANK0_PROC0_INTE3_GPIO27_EDGE_HIGH_MASK
                                | IO_BANK0_PROC0_INTE3_GPIO27_EDGE_LOW_MASK);
}

static void callback()
{
    if( io_bank0 -> proc0_ints2 & IO_BANK0_PROC0_INTS3_GPIO27_EDGE_HIGH_MASK)
        pin_state = true;            
    if( io_bank0 -> proc0_ints2 & IO_BANK0_PROC0_INTS3_GPIO27_EDGE_LOW_MASK)
        pin_state = false;
}

_Bool get_pin27()
{
    return pin_state;
}