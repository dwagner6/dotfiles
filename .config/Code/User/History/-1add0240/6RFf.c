#include "i2c0.h"
#include "lis3dh.h"
#include <stdint.h>
#include <stdbool.h>

_Bool lis3dh_do_reading(char axis)
{
    uint16_t trans[3];
    uint8_t axis_beginning_reg;

    switch(axis)
    {
        case 'x':
            axis_beginning_reg = LIS3DH_OUT_X_L;
            break;
        case 'y':
            axis_beginning_reg = LIS3DH_OUT_Y_L;
            break;
        case 'z':
            axis_beginning_reg = LIS3DH_OUT_Z_L;
            break;
        default:
            return false;
    }

    trans[0] = LIS3DH_AUTO_INC | axis_beginning_reg;
    trans[1] = I2C_READ | I2C_RESTART;
    trans[2] = I2C_READ | I2C_STOP;
    return true;
}