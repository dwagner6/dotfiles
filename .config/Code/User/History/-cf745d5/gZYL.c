#include "systick_int.h"
#include <stdint.h>
#include "led.h"

void foo();

int main (void)
{
    uint16_t cnt = 0;
    configure_systick();
    configure_led();

    while(1)
    {
        if(!systick_has_fired())
        {
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