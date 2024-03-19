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
        if(!systick_has_fired)
            continue;
        
        uint16_t data;
        static enum {IDLE, READ_AXIS, PRINT_DATA} state = IDLE;

        switch(state)
        {
            case IDLE:
                if( usbcdc_getchar(&c) )
                    state = READ_AXIS;
                else
                    state = IDLE;
                break;
            
            case READ_AXIS:
                lis3dh_do_reading(c);
                state = PRINT_DATA;
                break;
            
            case PRINT_DATA:
                lis3dh_print_data(&data);
                state = IDLE;
        }

        feed_the_watchdog();
    }
}