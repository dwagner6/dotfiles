#ifndef LIS3DH_H
#define LIS3DH_H

#define LIS3DH_WHO_AM_I 0x0f
#define LIS3DH_OUT_X_L  0X28
#define LIS3DH_OUT_X_H  0x29 
#define LIS3DH_OUT_Y_L  0X2A
#define LIS3DH_OUT_Y_H  0x2B
#define LIS3DH_OUT_Z_L  0X2C
#define LIS3DH_OUT_Z_H  0X2D
#define LIS3DH_ADDR     0X19
#define LIS3DH_STATUS_REG   0x27
#define LIS3DH_CTRL_REG_1   0x20
#define LIS3DH_AUTO_INC     0x80 
#define LIS3DH_EN_ALL_AXES  0x07 
#define LIS3DH_1HZ_MODE     0x10
#define LIS3DH_10HZ_MODE    0x20
#define LIS3DH_BLOCK_DATA_UPDATE    0X80
#define LIS3DH_HIGH_RES_OUTPUT      0X08

_Bool lis3dh_initiate_reading(char axis);
void configure_lis3dh();
uint16_t lis3dh_get_data();
//int16_t lis3dh_cat_reading( uint8_t low, uint8_t high);
#endif