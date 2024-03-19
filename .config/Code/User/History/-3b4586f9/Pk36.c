#include "usbcdc.h"
#include "uclib.h"
#include "i2c0.h"
#include <stdbool.h>
#include <rp2040/i2c.h>

int main()
{
    char c;
    configure_i2c0();
    configure_usbcdc();

    while(1)
    {
        if( usbcdc_getchar(&c))
        {
            uint16_t data;
            uint16_t trans[8];

            switch(c)
            {
                _Bool flag;
                case 'w':
                    trans[0] = 0x0f;
                    trans[1] = I2C_READ | I2C_RESTART | I2C_STOP;
                    if(i2c0_do_transaction(0x19, 2, trans))
                        print_string("WhoamI sent \n\r");
                    else
                        print_string("WhoamI not sent \n\r");
                    break;
                
                case 's': 
                    
            }
        }
    }
}