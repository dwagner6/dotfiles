#ifndef TPS55289_H
#define TPS55289_H

#include <stdbool.h>

_Bool tps55289_enable_output();
_Bool tps55289_disable_output();
_Bool tps55289_set_vout(uint16_t vout_set_mv);