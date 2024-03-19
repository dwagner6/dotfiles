/***********************************************************************
* FILENAME :        lis3dh.c           
*
* DESCRIPTION :     Driver implementation for LIS3DH on the Pico
*                   I2C only, currently
*
* AUTHOR :    Doug Wagner        START DATE :    08 DEC 23
*                                LAST UPDATE:    11 DEC 23
* 
************************************************************************/

#include "i2c0.h"
#include "lis3dh.h"
#include "uclib.h"
#include "usbcdc.h"
#include <stdint.h>
#include <stdbool.h>

void configure_lis3dh()
{
    uint16_t trans[7];
    trans[0] = LIS3DH_AUTO_INC| LIS3DH_CTRL_REG_1;
    trans[1] = LIS3DH_EN_ALL_AXES | LIS3DH_10HZ_MODE; 
    trans[2] = 0x00;
    trans[3] = 0x00;
    trans[4] = LIS3DH_BLOCK_DATA_UPDATE | LIS3DH_HIGH_RES_OUTPUT;
    trans[5] = 0x00;
    trans[6] = 0x00 | I2C_STOP;

    i2c0_do_transaction(LIS3DH_ADDR, 7, trans);
}

_Bool lis3dh_initiate_reading(char axis)
{
    uint16_t trans[3];
    uint8_t axis_beginning_reg;

    switch(axis)
    {
        case 'x':
            axis_beginning_reg = LIS3DH_OUT_X_L;
            print_string("X-axis:\t");
            break;
        case 'y':
            axis_beginning_reg = LIS3DH_OUT_Y_L;
            print_string("Y-axis:\t");
            break;
        case 'z':
            axis_beginning_reg = LIS3DH_OUT_Z_L;
            print_string("Z-axis:\t");
            break;
        default:
            return false;
    }

    trans[0] = LIS3DH_AUTO_INC | axis_beginning_reg;
    trans[1] = I2C_READ | I2C_RESTART;
    trans[2] = I2C_READ | I2C_STOP;
    i2c0_do_transaction(LIS3DH_ADDR, 3, trans);
    
    return true;
}

uint16_t lis3dh_get_data()
{
    uint16_t byte;
    uint16_t data = 0;
    uint8_t i = 0;

    while(i2c0_get_data(&byte))
    {
        data |= (byte << i*8);
        i++;
    }   

    return data;
}

void lis3dh_print_accel(uint16_t data)
{
    int16_t g = data;

    if(g<0)
    {
        usbcdc_putchar('-');
        g = -g;
    }

    g = (g * 10000 + 5) >> 14;

    for(uint8_t i = 0; i < 4; i++)
    {
        int16_t g_char = g;

        for(uint8_t j = 0; j < 4-i; j++)
            g_char = div10(g_char);

        usbcdc_putchar(mod10(g_char) + 48);

        if(i == 0)
            usbcdc_putchar('.');
    }
    
    print_string("\n\r");

}