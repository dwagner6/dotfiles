#include "i2c0.h"
#include "uclib.h"
#include <rp2040/i2c.h>
#include <stdint.h>
#include <stdbool.h>

#define I2C_ADDR           0x74
#define REF_LSB_REG        0x00
#define REF_MSB_REG        0x01 
#define REF_MSB_REG_MASK   0x03    // only lowest 3 bits of REF_MSB are used
#define IOUT_LIMIT_REG     0x02 
#define VOUT_FS_REG        0x04
#define VOUT_FS_REG_MASK   0x83    // only bits 7, 1, 0 used
#define MODE_REG           0x06
#define STATUS_REG         0x07
#define OE_BIT             7
#define HICCUP_BIT         5    // default on reset
#define DSCHG_BIT          4

#define FBINT_RATIO 564
#define VREF_STEP   5645
#define VREF_OFFSET 45000

_Bool tps55289_enable_output()
{
    uint16_t trans[2];
    trans[0] = MODE_REG;
    trans[1] = (1 << OE_BIT) | (1 << HICCUP_BIT) | I2C_STOP;
    if(i2c0_do_transaction(I2C_ADDR, 2, trans))
        return true;
    else
        return false;
}

_Bool tps55289_disable_output()
{
    uint16_t trans[2];
    trans[0] = MODE_REG;
    trans[1] = (1 << DSCHG_BIT) | I2C_STOP;
    if(i2c0_do_transaction(I2C_ADDR, 2, trans))
        return true;
    else
        return false;
}

_Bool tps55289_set_vout(uint16_t vout_set_mv)
{
    uint32_t vref = vout_set_mv * VREF_STEP - VREF_OFFSET;
    uint16_t ref_value = (uint16_t)(vref / FBINT_RATIO);

    uint16_t trans[3];
    trans[0] = REF_LSB_REG;
    trans[1] = ref_value & 0x00ff;
    trans[2] = ref_value & 0x0100 | I2C_STOP;
    if(i2c0_do_transaction(I2C_ADDR, 3, trans))
        return true;
    else 
        return false;
}