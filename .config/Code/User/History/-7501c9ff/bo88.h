/***********************************************************************
* FILENAME :        uclib.h          
*
* DESCRIPTION :     Function declarations of uclib library.
*
* AUTHOR :    Doug Wagner        START DATE :    12 OCT 23
* 
************************************************************************/

#ifndef UCLIB_H
#define UCLIB_H

#include <stdint.h>

uint16_t rand();
void srand(uint32_t);
void print_string( char const *s );
void print_hex(uint8_t num_digits, uint32_t value);
void hex_dump(uint32_t start, uint8_t bytes);
uint16_t div10( uint16_t x );
uint16_t mod10( uint16_t x );
uint32_t str_to_uint32(const char * string);
void int_to_hex_str(uint8_t num_digits, uint32_t value, char * hex_string);
void uint16_to_string(uint16_t value, char *string);

#endif 