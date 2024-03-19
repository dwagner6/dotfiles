#include "i2c0.h"
#include <stdbool.h>
#include <stdint.h>
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/pads_bank0.h>
#include <rp2040/io_bank0.h>
#include <rp2040/i2c.h>
#include <rp2040/clocks.h>

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl) 

#define I2C0_SDA_LOC 4
#define I2C0_SCL_LOC 5 

#define I2C0_RESETS (RESETS_RESET_I2C0_MASK \ 
                    | RESETS_RESET_IO_BANK0_MASK \ 
                    | RESETS_RESET_PADS_BANK0_MASK)

void configure_i2c0()
{
    resets -> clr_reset = I2C0_RESETS; 

    while( (resets -> reset_done & I2C0_RESETS) != I2C0_RESETS );
    
    pads_bank0 -> GPIO( I2C0_SCL_LOC ) = 
                PADS_BANK0_GPIO25_OD(0)
                | PADS_BANK0_GPIO25_IE(1) 
                | PADS_BANK0_GPIO25_DRIVE(0) 
                | PADS_BANK0_GPIO25_PUE(1) 
                | PADS_BANK0_GPIO25_PDE(0) 
                | PADS_BANK0_GPIO25_SCHMITT(0)
                | PADS_BANK0_GPIO25_SLEWFAST(0);
}