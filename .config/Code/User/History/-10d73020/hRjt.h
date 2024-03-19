/***********************************************************************
* FILENAME :        tps55289.h          
*
* DESCRIPTION :     Driver interface for TPS55289EVM board
*
* AUTHOR :    Doug Wagner        START DATE :    12 DEC 23
* 
************************************************************************/

#ifndef TPS55289_H
#define TPS55289_H

#include <stdbool.h>

#define VOUT_DEFAULT_MV 3000
#define VOUT_SET_MAX    20000

_Bool tps55289_enable_output();
_Bool tps55289_disable_output();
_Bool tps55289_set_vout(uint16_t vout_set_mv);

#endif