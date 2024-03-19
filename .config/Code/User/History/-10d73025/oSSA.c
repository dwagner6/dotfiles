#include "i2c0.h"
#include "uclib.h"
#include <rp2040/i2c.h>
#include <stdint.h>
#include <stdbool.h>

#define TPS55289_I2C_ADDR           0x74
#define TPS55289_REF_LSB_REG        0x00
#define TPS55289_REF_MSB_REG        0x01 
#define TPS55289_REF_MSB_REG_MASK   0x03    // only lowest 3 bits of REF_MSB are used
#define TPS55289_IOUT_LIMIT_REG     0x02 
#define TPS55289_VOUT_FS_REG        0x04
#define TPS55289_VOUT_FS_REG_MASK   0x83    // only bits 7, 1, 0 used
#define TPS55289_MODE_REG           0x06
#define TPS55289_STATUS_REG         0x07
#define TPS55289_OE_BIT             7
#define TPS55289_HICCUP_BIT         5    // default on reset
#define TPS55289_DSCHG_BIT          4

_Bool tps55289_enable_output()
{
    uint16_t trans[2];
    trans[0] = TPS55289_MODE_REG;
    trans[1] = (1 << TPS55289_OE_BIT) | (1 << TPS55289_HICCUP_BIT) | I2C_STOP;
    if(i2c0_do_transaction(TPS55289_I2C_ADDR, 2, trans))
        return true;
    else
        return false;
}

_Bool tps55289_disable_output()
{
    uint16_t trans[2];
    trans[0] = TPS55289_MODE_REG;
    trans[1] = (1 << TPS55289_DSCHG_BIT) | I2C_STOP;
    if(i2c0_do_transaction(TPS55289_I2C_ADDR, 2, trans))
        return true;
    else
        return false;
}

_Bool tps55289_set_vout(uint16_t vout_set)
{
    
}