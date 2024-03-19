/***********************************************************************
* FILENAME :        pb0.c           
*
* DESCRIPTION : Driver definitions for active-low pushbutton on GPIO15 (pin 20)
*       
* AUTHOR :    Doug Wagner        START DATE :    01 OCT 23
*
************************************************************************/

#include "pb0.h"
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>
#include <stdbool.h>

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

void configure_pb0( uint8_t gpio )
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
	                    | PADS_BANK0_GPIO25_PUE(1) 
	                    | PADS_BANK0_GPIO25_PDE(0) 
	                    | PADS_BANK0_GPIO25_SCHMITT(0) 
	                    | PADS_BANK0_GPIO25_SLEWFAST(0);
    
    uint32_t const out_io_bank0gpio_ctrl = 
	                    IO_BANK0_GPIO25_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_FUNCSEL(5);

    pads_bank0 -> gpio15 = 
        PADS_BANK0_GPIO15_OD(0)
        | PADS_BANK0_GPIO15_IE(1)
        | PADS_BANK0_GPIO15_DRIVE(0)
        | PADS_BANK0_GPIO15_PUE(1)      // enable pullup on button pin
        | PADS_BANK0_GPIO15_PDE(0)      // disable default pulldown
        | PADS_BANK0_GPIO15_SCHMITT(0)
        | PADS_BANK0_GPIO15_SLEWFAST(0);

    io_bank0 -> gpio15_ctrl = 
        IO_BANK0_GPIO15_CTRL_IRQOVER(0) |
        IO_BANK0_GPIO15_CTRL_INOVER(0)  |
        IO_BANK0_GPIO15_CTRL_OEOVER(0)  |
        IO_BANK0_GPIO13_CTRL_OUTOVER(0) |
        IO_BANK0_GPIO15_CTRL_FUNCSEL(5);

}

_Bool pb0_pressed()
{
    if( (sio -> gpio_in & (1<<15)) )
        return false;   // active low!
    else
        return true;
}