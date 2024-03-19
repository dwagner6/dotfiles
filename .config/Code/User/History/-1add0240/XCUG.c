#include "i2c0.h"
#include "lis3dh.h"
#include "uclib.h"
#include <stdint.h>
#include <stdbool.h>

void configure_lis3dh()
{
    uint16_t trans[7];
    trans[0] = LIS3DH_AUTO_INC| LIS3DH_CTRL_REG_1;
    trans[1] = LIS3DH_EN_ALL_AXES | LIS3DH_1HZ_MODE; 
    trans[2] = 0x00;
    trans[3] = 0x00;
    trans[4] = LIS3DH_BLOCK_DATA_UPDATE | LIS3DH_HIGH_RES_OUTPUT;
    trans[5] = 0x00;
    trans[6] = 0x00 | I2C_STOP;

    i2c0_do_transaction(LIS3DH_ADDR, 7, trans);
}

_Bool lis3dh_do_reading(char axis)
{
    uint16_t trans[3];
    uint8_t axis_beginning_reg;

    switch(axis)
    {
        case 'x':
            axis_beginning_reg = LIS3DH_OUT_X_L;
            print_string("X-axis: \n\r");
            break;
        case 'y':
            axis_beginning_reg = LIS3DH_OUT_Y_L;
            print_string("Y-axis: \n\r");
            break;
        case 'z':
            axis_beginning_reg = LIS3DH_OUT_Z_L;
            print_string("Z-axis: \n\r");
            break;
    }

    trans[0] = LIS3DH_AUTO_INC | axis_beginning_reg;
    trans[1] = I2C_READ | I2C_RESTART;
    trans[2] = I2C_READ | I2C_STOP;
    i2c0_do_transaction(LIS3DH_ADDR, 3, trans);
    
    return true;
}

uint16_t lis3dh_print_data()
{
    _Bool flag;
    uint16_t byte;
    uint16_t data;

    while(i2c0_get_data(&byte))
    {
        static uint8_t i = 0;
        data = byte << (i);
        i++;
    }   

    print_string("0x");
    print_hex(2, data);
    print_string("\n\r");

    return data;
}