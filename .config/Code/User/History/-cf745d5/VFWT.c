#include "systick_int.h"
#include <stdint.h>
#include "led.h"

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
        if(++cnt == 500)
        {
            toggle_led();
            cnt = 0;
        }
    }

    return 0;
}