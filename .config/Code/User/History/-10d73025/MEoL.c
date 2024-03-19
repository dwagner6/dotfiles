#include "i2c0.h"
#include "uclib.h"
#include <rp2040/i2c.h>
#include <stdint.h>
#include <stdbool.h>

#define I2C_ADDR            0x74
#define REF_LSB_REG         0x00
#define REF_MSB_REG         0x01 
#define REF_MSB_REG_MASK    0x03 
#define IOUT_LIMIT_REG      0x02 
#define VOUT_FS_REG         0x04
#define VOUT_FS_REG_MASK    0x83 
#define MODE_REG            0x06
#define STATUS_REG          0x07
#define OE_BIT              7
#define DSCHG_BIT           4
#define VOUT_MIN_MV         800
#define VOUT_MAX_MV         20000
#define REF_MIN             0x0000  // Vout = 0.8V
#define REF_MAX             0x0780  // Vout = 20V

_Bool tps55289_enable_output()
{
    uint16_t trans[2];
    trans[0] = MODE_REG;
    trans[1] = (1 << OE_BIT) | I2C_STOP;
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

static uint16_t calculate_ref(uint32_t vout_mv) {
    
    if (vout_mv < VOUT_MIN_MV) 
    {
        vout_mv = VOUT_MIN_MV; 
    } 
    else if (vout_mv > VOUT_MAX_MV) 
    {
        vout_mv = VOUT_MAX_MV;
    }

    uint32_t ref_value = ((vout_mv - VOUT_MIN_MV) * REF_MAX) / (VOUT_MAX_MV - VOUT_MIN_MV);

    return (uint16_t)ref_value;
}

_Bool tps55289_set_vout(uint16_t vout_set_mv)
{
    uint16_t ref_value = calculate_ref(vout_set_mv);
    print_string("ref_value: ");
    print_hex(4, ref_value);
    print_string("\n\r");

    uint16_t trans[3];
    trans[0] = REF_LSB_REG;
    trans[1] = ref_value & 0x00ff;
    trans[2] = ref_value >> 8 | I2C_STOP;
    if(i2c0_do_transaction(I2C_ADDR, 3, trans))
        return true;
    else 
        return false;
}