#include "usbcdc.h"
#include "uclib.h"
#include "i2c0.h"
#include "lis3dh.h"
#include "systick.h"
#include "watchdog.h"
#include <stdbool.h>
#include <rp2040/i2c.h>

int main()
{
    char c;
    configure_i2c0();
    configure_usbcdc();
    configure_systick();
    configure_watchdog(1500);
    configure_lis3dh();

    while(1)
    {   
        if(!systick_has_fired())
            continue;
        
        
        static enum {IDLE, READ_AXIS, PRINT_DATA} state = IDLE;

        switch(state)
        {
            uint16_t data;

            case IDLE:
                if( usbcdc_getchar(&c) )
                    state = READ_AXIS;
                else
                    state = IDLE;
                break;
            
            case READ_AXIS:
                if(lis3dh_initiate_reading(c))
                    state = PRINT_DATA;
                else
                    state = IDLE;
                break;
            
            case PRINT_DATA:
                data = lis3dh_print_data();
                state = IDLE;
        }

        feed_the_watchdog();
    }
}