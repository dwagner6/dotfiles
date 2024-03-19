#include "adc.h"
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

void configure_adc()
{
    clocks->set_clk_adc_ctrl = CLOCKS_CLK_ADC_CTRL_ENABLE(1);  
    resets -> clr_reset = GPIO26_ADC0_RESETS;

    while(! (resets -> reset_done && RESETS_RESET_IO_BANK0_MASK))
        continue;
    while(! (resets -> reset_done && RESETS_RESET_PADS_BANK0_MASK))
        continue

    uint32_t const out_pads_bank0_gpio =    
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
}

static void adc_start_continuous_conversions()
{
    adc -> set_cs = ADC_CS_START_MANY(1);
}

void enable_adc()
{
    adc -> set_cs = ADC_CS_EN(1);   
    while( !(adc -> cs && ADC_CS_READY_MASK) )
        continue; 
    adc -> set_cs = ADC_CS_AINSEL(0);
    adc -> set_cs = ADC_CS_START_MANY(1);
}

void disable_adc()
{
    adc -> clr_cs = ADC_CS_EN(1);
}

uint16_t adc_to_millivolts(uint16_t adc_value) 
{
    uint32_t voltage_step = (VOLTAGE_RANGE << 16) / ADC_RESOLUTION; 
    uint32_t voltage = (uint32_t)adc_value * voltage_step;
    
    return (uint16_t)(voltage >> 16);
}

uint16_t get_adc_raw()
{
    return adc -> result;
}