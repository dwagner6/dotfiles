#include "i2c0.h"
#include <stdbool.h>
#include <stdint.h>
#include <rp2040/resets.h>
#include <rp2040/sio.h>
#include <rp2040/pads_bank0.h>
#include <rp2040/io_bank0.h>
#include <rp2040/i2c.h>
#include <rp2040/clocks.h>

#define CONCAT2(x,y) x##y
#define CONCAT3(x,y,z) x##y##z
#define GPIO(x) CONCAT2(gpio,x)
#define GPIO_CTRL(x) CONCAT3(gpio,x,_ctrl) 

#define I2C0_SDA_LOC 4
#define I2C0_SCL_LOC 5 

#define I2C0_RESETS (RESETS_RESET_IO_BANK0_MASK)