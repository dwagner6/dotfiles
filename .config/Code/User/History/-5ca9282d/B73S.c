#include "gpio13_int.h"
#include "pb.h"
#include "systick.h"
#include <stdint.h>
#include "led.h"
#include "interrupt.h"

int main (void)
{
    disable_irq();
    configure_systick();
    configure_pb(13);
    configure_gpio13_irq();
    configure_led();
    enable_irq();
    
    while(1)
    {
        asm("WFI");
        if(!systick_has_fired())
            continue;
        
        if(get_gpio13())
            turn_on_led();
        else 
            turn_off_led();
    }

    return 0;
}