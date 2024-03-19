#include "i2c0.h"
#include <stdbool.h>
#include <stdint.h>
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/pads_bank0.h>
#include <rp2040/io_bank0.h>
#include <rp2040/i2c.h>
//#include <rp2040/clocks.h>

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
                | PADS_BANK0_GPIO25_SCHMITT(1)
                | PADS_BANK0_GPIO25_SLEWFAST(0);
    
    pads_bank0 -> GPIO( I2C0_SDA_LOC ) = 
                PADS_BANK0_GPIO25_OD(0)
                | PADS_BANK0_GPIO25_IE(1) 
                | PADS_BANK0_GPIO25_DRIVE(0) 
                | PADS_BANK0_GPIO25_PUE(1) 
                | PADS_BANK0_GPIO25_PDE(0) 
                | PADS_BANK0_GPIO25_SCHMITT(1)
                | PADS_BANK0_GPIO25_SLEWFAST(0);

    io_bank0 -> GPIO_CTRL( I2C0_SCL_LOC ) = 
	                    IO_BANK0_GPIO25_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_FUNCSEL(3);

    io_bank0 -> GPIO_CTRL( I2C0_SDA_LOC ) = 
	                    IO_BANK0_GPIO25_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO25_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO25_CTRL_FUNCSEL(3);
    
    i2c0 -> ic_enable = 0;
    i2c0 -> ic_con = 
                I2C0_IC_CON_IC_SLAVE_DISABLE(1) | 
                I2C0_IC_CON_IC_RESTART_EN(1) | 
                I2C0_IC_CON_IC_10BITADDR_MASTER(0) | 
                I2C0_IC_CON_SPEED(2) | 
                I2C0_IC_CON_MASTER_MODE(1); 
    
    i2c0 -> ic_fs_scl_hcnt = 113; 
    i2c0 -> ic_fs_scl_lcnt = 200; 
    i2c0 -> ic_rx_tl = 15;
    i2c0 -> ic_tx_tl = 15;
}