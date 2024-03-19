#include "systick_int.h"
#include <stdint.h>
#include "led.h"
#include "interrupt.h"

void foo();

int main (void)
{
    uint16_t cnt = 0;

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

void foo()
{
    if(++cnt == 500)
    {
        toggle_led();
        cnt = 0;
    } 
}