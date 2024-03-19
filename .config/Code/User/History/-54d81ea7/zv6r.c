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

#define ADC_RESOLUTION 4095 
#define VOLTAGE_RANGE 3000

uint16_t adc_to_millivolts(uint16_t adc_value);

int main()
{
    clocks->set_clk_adc_ctrl = CLOCKS_CLK_ADC_CTRL_ENABLE(1); // must enable ADC clock 

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
convertToMillivolts
    while(1)
    {
        if(!systick_has_fired())
            continue;
        
        static uint16_t cnt = 0;

        if(++cnt > 500)
        {
            
            cnt = 0;
            uint16_t adc_result = adc -> result;
            uint16_t adc_millivolts = convertToMillivolts(adc_result);
        
            print_string("ADC raw: ");
            print_hex(4, adc_result);
            print_string("\n\r");
            print_string("ADC mV: ");
            print_hex(4, adc_millivolts);
            print_string("\n\r");
        }

        
    }

    
}

uint16_t adc_to_millivolts(uint16_t adc_value) 
{
    uint32_t voltage_step = (VOLTAGE_RANGE << 8) / ADC_RESOLUTION;
    uint32_t voltage = (uint32_t)adc_value * voltage_step; 
    
    return (uint16_t)(voltage >> 8);
}