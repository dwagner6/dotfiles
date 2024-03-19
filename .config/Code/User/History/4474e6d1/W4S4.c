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

void configure_pb( uint8_t gpio )
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

    pads_bank0 -> GPIO(gpio);
    io_bank0 -> GPIO_CTRL(gpio);
}

_Bool pb0_pressed()
{
    if( (sio -> gpio_in & (1<<15)) )
        return false;   // active low!
    else
        return true;
}