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

    while(1)
    {   
        if(!systick_has_fired)
            continue;
        
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
            

        }
        if( usbcdc_getchar(&c))
        {
            uint16_t data;
            uint16_t trans[8];

            switch(c)
            {
                _Bool flag;
                case 'x':
                    trans[0] = LIS3DH_AUTO_INC | LIS3DH_OUT_X_L;
                    trans[1] = I2C_READ | I2C_RESTART;
                    trans[2] = I2C_READ | I2C_STOP;
                    if(i2c0_do_transaction(LIS3DH_ADDR, 3, trans))
                        print_string("X axis read \n\r");
                    else
                        print_string("X axis not read \n\r");
                    break;
                
                case 's': 
                    trans[0] = LIS3DH_STATUS_REG;
                    trans[1] = I2C_READ | I2C_RESTART | I2C_STOP;
                    if( i2c0_do_transaction(LIS3DH_ADDR, 2, trans))
                        print_string("Status sent \n\r");
                    else 
                        print_string("Status NOT sent \n\r");
                    break;
                
                case 'r': 
                    do
                    {
                        if( flag = i2c0_get_data(&data) )
                        {
                            print_string("Read byte: 0x");
                            print_hex(2, data);
                            print_string("\n\r");
                        }
                        else    
                            print_string("No more data \n\r");
                    }while(flag);
                    break;
                
                case 'a':
                    trans[0] = LIS3DH_AUTO_INC | LIS3DH_OUT_X_L; 
                    trans[1] = I2C_READ | I2C_RESTART;
                    trans[2] = I2C_READ;
                    trans[3] = I2C_READ;
                    trans[4] = I2C_READ;
                    trans[5] = I2C_READ; 
                    trans[6] = I2C_READ | I2C_STOP;
                    if( i2c0_do_transaction(0x19, 7, trans) )
                        print_string("Requested 6B acceleration data\n\r");
                    break;

                case 'p':
                    print_hex(8, i2c0 -> ic_raw_intr_stat);
                    print_string("\n\r");
                    break;
                
                case 'c': 
                    trans[0] = LIS3DH_AUTO_INC| LIS3DH_CTRL_REG_1;
                    trans[1] = LIS3DH_EN_ALL_AXES | LIS3DH_1HZ_MODE; 
                    trans[2] = 0x00;
                    trans[3] = 0x00;
                    trans[4] = LIS3DH_BLOCK_DATA_UPDATE | LIS3DH_HIGH_RES_OUTPUT;
                    trans[5] = 0x00;
                    trans[6] = 0x00 | I2C_STOP;

                    if( i2c0_do_transaction(0x19, 7, trans) )
                        print_string("Sent config\n\r");
                    else
                        print_string("Config failed\n\r");
                    break;
            }
        }

        feed_the_watchdog();
    }
}