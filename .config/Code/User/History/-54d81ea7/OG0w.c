#include "usbcdc.h"
#include "systick.h"
#include "uclib.h"
#include <stdint.h>
#include <rp2040/clocks.h>
#include <rp2040/adc.h>
#include <rp2040/resets.h>
#include <rp2040/io_bank0.h>
#include <rp2040/pads_bank0.h>

#define GPIO26_ADC0_RESETS    (RESETS_RESET_IO_BANK0_MASK | RESETS_RESET_PADS_BANK0_MASK | RESETS_RESET_ADC_MASK | RESETS_RESET_PLL_USB_MASK)

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl)

int main()
{
    clocks->clk_adc_ctrl = CLOCKS_CLK_ADC_CTRL_ENABLE(1); // must enable ADC clock 

    configure_usbcdc();
    configure_systick();
    

    resets -> clr_reset = GPIO26_ADC0_RESETS;

    while( (resets -> reset_done & GPIO26_ADC0_RESETS) != GPIO26_ADC0_RESETS )
        continue; 
    

    uint32_t const out_pads_bank0_gpio =    // OD 1 and IE 0 for ADC on GPIO26 per datasheet
	                    PADS_BANK0_GPIO26_OD(1) 
	                    | PADS_BANK0_GPIO26_IE(0) 
	                    | PADS_BANK0_GPIO26_DRIVE(0) 
	                    | PADS_BANK0_GPIO26_PUE(0) 
	                    | PADS_BANK0_GPIO26_PDE(0) 
	                    | PADS_BANK0_GPIO26_SCHMITT(0) 
	                    | PADS_BANK0_GPIO26_SLEWFAST(0);

    uint32_t const out_io_bank0gpio_ctrl = 
	                    IO_BANK0_GPIO26_CTRL_IRQOVER(0) |
	                    IO_BANK0_GPIO26_CTRL_INOVER(0)  |
	                    IO_BANK0_GPIO26_CTRL_OEOVER(0)  |
	                    IO_BANK0_GPIO26_CTRL_OUTOVER(0) |
	                    IO_BANK0_GPIO26_CTRL_FUNCSEL(5);

    pads_bank0 -> GPIO(26)       = out_pads_bank0_gpio;
	io_bank0 -> GPIO_CTRL(26)   = out_io_bank0gpio_ctrl; 

    adc -> cs = ADC_CS_EN(1);   // enable adc 
    adc -> fcs = ADC_FCS_EN(1); // enable FIFO

    while( !(adc -> cs && ADC_CS_READY_MASK) )
        continue; 

    adc -> cs = ADC_CS_AINSEL(0);  // adc channel set to GPIO26 before conversion starts
    //adc -> cs = ADC_CS_START_MANY(1); // try free-running conversions

    

    while(1)
    {
        if(!systick_has_fired())
            continue;
        
        static uint16_t cnt = 0;

        if(++cnt > 500)
        {
            cnt = 0;
            uint16_t adc_fifo;
            for(uint8_t i = 0; i < 4; i++)
            {
                adc_fifo = adc -> fifo & ADC_FIFO_VAL_MASK;
                print_string("FIFO");
                print_hex(1, i);
                print_string(":\t");
                print_hex(4, adc_fifo);
                print_string("\t");
            }
            print_string("\n\r");


        }

        
    }

    
}
