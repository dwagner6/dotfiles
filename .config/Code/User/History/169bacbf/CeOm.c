#include "gpio12_int.h"
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>
#include "gpio_irq.h"

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

#define PIN12_RESETS    (RESETS_RESET_IO_BANK0_MASK | RESETS_RESET_PADS_BANK0_MASK)

static _Bool pin_state;

_Bool get_gpio12();
static void callback();

void configure_gpio12( void )
{
    resets -> clr_reset = PIN12_RESETS;

    while(! (resets -> reset_done && RESETS_RESET_IO_BANK0_MASK))
        continue;
    
    while(! (resets -> reset_done && RESETS_RESET_PADS_BANK0_MASK))
        continue;
    
    uint32_t const out_pads_bank0_gpio = 
	                    PADS_BANK0_GPIO12_OD(1) 
	                    | PADS_BANK0_GPIO12_IE(1) 
	                    | PADS_BANK0_GPIO12_DRIVE(0) 
	                    | PADS_BANK0_GPIO12_PUE(0) 
	                    | PADS_BANK0_GPIO12_PDE(0) 
	                    | PADS_BANK0_GPIO12_SCHMITT(0) 
	                    | PADS_BANK0_GPIO12_SLEWFAST(0);

    uint32_t const out_io_bank0gpio_ctrl = 
	                    IO_BANK0_GPIO12_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO12_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO12_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO12_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO12_CTRL_FUNCSEL(5);

    pads_bank0 -> GPIO(12)       = out_pads_bank0_gpio;
	io_bank0 -> GPIO_CTRL(12)   = out_io_bank0gpio_ctrl;

    register_gpio_irq_callback(12, callback);
    io_bank0 -> proc0_inte3 |= (IO_BANK0_PROC0_INTE1_GPIO12_LEVEL_LOW_MASK);
}

static void callback()
{
    pin_state = true;
}

_Bool get_gpio12()
{
    if(pin_state == true)
        return true;
    else
    {
        pin_state = false;
        return false;
    }
}