/* Low-level driver for NHD-0216K1Z wired in 4-Bit mode.
 *
 */
#include "lcdold.h"
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>
#include <stdint.h>
#include <stdbool.h>

/*Important: This driver is written under the assumption that the LCD data bus
 * is mapped to four consecutive GPIO pins to facilitate bus writes
 */
#define DB4_LOC 10
#define DB5_LOC 11
#define DB6_LOC 12
#define DB7_LOC 13
#define E_LOC 17
#define RS_LOC 16

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

static void lcd_output_nibble( uint8_t data)
{
	sio->gpio_out = (sio->gpio_out & ~(0xf<<DB4_LOC)) | (data&0xf)<<DB4_LOC;
}
static void lcd_set_e()
{
	sio->gpio_out_set = (1<<E_LOC);
}
static void lcd_clr_e()
{
	sio->gpio_out_clr = (1<<E_LOC);
}

static void lcd_set_rs()
{
	sio->gpio_out_set = (1<<RS_LOC);
}
static void lcd_clr_rs()
{
	sio->gpio_out_clr = (1<<RS_LOC);
}

#define LCD_RESETS ( RESETS_RESET_IO_BANK0_MASK \
	    | RESETS_RESET_PADS_BANK0_MASK)
void configure_lcd()
{
    resets -> clr_reset = LCD_RESETS;

    while( (resets -> reset_done & LCD_RESETS) != LCD_RESETS )
    	continue;

    uint32_t const out_pads_bank0_gpio = 
	PADS_BANK0_GPIO25_OD(0) 
	| PADS_BANK0_GPIO25_IE(0) 
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

    	pads_bank0 -> GPIO(E_LOC) = out_pads_bank0_gpio;
    	pads_bank0 -> GPIO(DB4_LOC) = out_pads_bank0_gpio;
    	pads_bank0 -> GPIO(DB5_LOC) = out_pads_bank0_gpio;
    	pads_bank0 -> GPIO(DB6_LOC) = out_pads_bank0_gpio;
    	pads_bank0 -> GPIO(DB7_LOC) = out_pads_bank0_gpio;
    	pads_bank0 -> GPIO(RS_LOC) = out_pads_bank0_gpio;
	io_bank0 -> GPIO_CTRL(RS_LOC) = out_io_bank0gpio_ctrl;
	io_bank0 -> GPIO_CTRL(E_LOC) = out_io_bank0gpio_ctrl;
	io_bank0 -> GPIO_CTRL(DB4_LOC) = out_io_bank0gpio_ctrl;
	io_bank0 -> GPIO_CTRL(DB5_LOC) = out_io_bank0gpio_ctrl;
	io_bank0 -> GPIO_CTRL(DB6_LOC) = out_io_bank0gpio_ctrl;
	io_bank0 -> GPIO_CTRL(DB7_LOC) = out_io_bank0gpio_ctrl;
	sio->gpio_out_clr = (0xf<<DB4_LOC) | (1<<RS_LOC) | (1<<E_LOC);
	sio->gpio_oe_set =  (0xf<<DB4_LOC) | (1<<RS_LOC) | (1<<E_LOC);
}

_Bool lcd_fsm(_Bool is_cmd, uint8_t value)
{
	static enum {RESET,IDLE,CMD1,CMD2,CMD3} state=RESET;
	static uint8_t cntr=50;
	static uint8_t data;
	_Bool retval=false;

		switch( state )
		{
			case RESET:
				cntr--;
				if( cntr == 0 )
					state=IDLE;
				break;
			case IDLE:
				if( is_cmd || value != 0)
				{
					data=value;
					if( is_cmd )
						lcd_clr_rs();
					else
						lcd_set_rs();
					lcd_output_nibble(data>>4);
					state=CMD1;
					cntr=2;
					retval=true;
					break;
				}
				break;
			case CMD1:
				lcd_set_e();
				state=CMD2;
				break;
			case CMD2:
				lcd_clr_e();
				state=CMD3;
				break;
			case CMD3:
				if( --cntr != 0 )
				{
					state=CMD1;
					lcd_output_nibble(data);
				}
				else
					state=IDLE;
				break;
		}
	return retval;
}
