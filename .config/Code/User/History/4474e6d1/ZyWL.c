/***********************************************************************
* FILENAME :        pb0.c           
*
* DESCRIPTION : Driver definitions for active-low pushbutton on GPIO15 (pin 20)
*       
* AUTHOR :    Doug Wagner        START DATE :    01 OCT 23
*
************************************************************************/

#include "pb.h"
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>
#include <stdbool.h>

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

#define DEBOUNCE_DELAY_MS   150

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

    switch(gpio)
    {
        case 13:
            pads_bank0 -> GPIO(13) = out_pads_bank0_gpio;
            io_bank0 -> GPIO_CTRL(13) = out_io_bank0gpio_ctrl;
            break;
        case 14:
            pads_bank0 -> GPIO(14) = out_pads_bank0_gpio;
            io_bank0 -> GPIO_CTRL(14) = out_io_bank0gpio_ctrl;
            break;
        case 15:
            pads_bank0 -> GPIO(15) = out_pads_bank0_gpio;
            io_bank0 -> GPIO_CTRL(15) = out_io_bank0gpio_ctrl;
            break;
    }
    
}

static _Bool pb_pressed(uint8_t gpio)
{
    if( (sio -> gpio_in & (1<<gpio)) )
        return false;   // active low!
    else
        return true;
}

_Bool get_pb(uint8_t gpio)
{
    typedef enum {WAIT_PRESS, DEBOUNCE, PRESSED, RELEASE} state_t;
    static state_t state = WAIT_PRESS;
    static uint8_t deb_cnt;

    _Bool pb = pb_pressed(gpio);

    switch(state)
    {
        case WAIT_PRESS:
            if(pb)
            {
                state = DEBOUNCE;
                deb_cnt = 0;
            }
            return false;
        
        case DEBOUNCE:
            if(pb)
            {
                if(deb_cnt < DEBOUNCE_DELAY_MS)
                    deb_cnt++;
                if(deb_cnt >= DEBOUNCE_DELAY_MS)
                {
                    state = PRESSED;
                }
            }
            return false;
        
        case PRESSED:
            if(pb)
            {
                state = RELEASE;
                return true;
            }
            else
                return false;
        
        case RELEASE:
            if(!pb)
                state = WAIT_PRESS;
            return false;

        default:
            return false;

    }
    
}