/***********************************************************************
* FILENAME :        keypad.h          
*
* DESCRIPTION :     Driver function declarations for 12-key keypad driver
*                   connected to pins 15-21 of RPI Pico
*
* AUTHOR :    Doug Wagner        START DATE :    12 OCT 23
* 
************************************************************************/

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

void configure_keypad();
void keypad_scan_column(uint8_t col);
uint8_t keypad_get_row();
_Bool get_key(char * key);

#define ALL_KEYPAD_COLUMNS  0xf

#endif