#include "pin27.h"
#include "systick_int.h"
#include <stdint.h>
#include "led.h"
#include "interrupt.h"

int main (void)
{
    disable_irq();
    configure_systick();
    configure_led();
    enable_irq();
    
    while(1)
    {
        if(!systick_has_fired())
        {
            asm("WFI");
            continue;
        }
    }

    return 0;
}