#include "i2c0.h"
#include "tps55289.h"
#include "pb.h"
#include "lcd.h"
#include "adc.h"
#include "power_supply.h"
#include <rp2040/i2c.h>
#include <stdint.h>
#include <stdbool.h>

#define VOUT_UP_PB_LOC     15
#define VOUT_DOWN_PB_LOC   14
#define ENABLE_PB_LOC   13

#define VOUT_STEP_MV    100
#define LCD_VOUT_FIELD  0x06
#define LCD_IMON_FIELD  0x06 
#define LCD_EN_FIELD    0x0C

void configure_power_supply()
{
    configure_adc();
    configure_pb(VOUT_UP_PB_LOC);
    configure_pb(VOUT_DOWN_PB_LOC);
    configure_pb(ENABLE_PB_LOC);
}