/***********************************************************************
* FILENAME :        uclib.c           
*
* DESCRIPTION :     Function definitions of uclib library
*
* AUTHOR :    Doug Wagner        START DATE :    02 OCT 23
*                                LAST UPDATE:    13 OCT 23
* 
************************************************************************/

#include "uclib.h"
#include <stdint.h>
#include <usbcdc.h>

static uint32_t random_number_state;

uint16_t rand() //LCG based on ANSI C
{
    random_number_state= (1103515245*random_number_state+12345)&0x7fffffff;
    return random_number_state>>16;
}

void srand(uint32_t x)
{
    random_number_state=x;
}

void print_string( char const * s)
{
    while( *s && usbcdc_putchar(*s++) )
        continue;
}

void print_hex(uint8_t num_digits, uint32_t value)
{
    int8_t i;

    if( num_digits > 8)
        num_digits = 8;

    for( i=num_digits-1; i>=0 && num_digits--; i-- ){
        uint8_t hex_digit = (value >> 4*i) & 0xf;
        usbcdc_putchar( hex_digit+( (hex_digit < 10)?'0':'A'-10 ) );
    }
}

void hex_dump(uint32_t start, uint8_t bytes)
{
    uint8_t * aligned_start_address = (uint8_t *) (start - (start%8)); 

    if(bytes % 8)
        bytes += bytes % 8;                     // if bytes isn't multiple of 8, make it so

    for(int8_t j = 0; j < bytes/8; j++)         // for each line of 8 bytes
    {
        print_hex(8, (uint32_t) ( aligned_start_address ));     // print beginning address
        print_string("  ");

        for(int8_t i = 0; i<8; i++)                             // print 8 bytes starting at beginning address
        {
            uint8_t contents = *(aligned_start_address + i);
            print_hex(2, (uint32_t) contents);
            print_string("  ");
        }
        aligned_start_address += 8;             // increment address+8 address for beginning of next line
        print_string("\n\r");
    }
}

uint16_t div10( uint16_t x )
{
    return (x * 0x199A) >> 16;
}

uint16_t mod10( uint16_t x )
{
    return x - (div10(x) * 10);
}

uint32_t str_to_uint32(const char * string)
{
    uint32_t result = 0;
    while(*string)
    {
        result = result * 10 + (*string - '0');
        string++;
    }
    return result;
}

void int_to_hex_str(uint8_t num_digits, uint32_t value, char * hex_string)
{
    const char * hex_chars = "0123456789ABCDEF";

    for(int8_t i = num_digits - 1; i >= 0; i--)
    {
        *(hex_string + i) = *(hex_chars + (value & 0xf));
        value >>= 4;
    }
}


void uint16_to_string(uint16_t value, char *string) 
{
    uint16_t temp = value;
    uint8_t length = 0;
    char temp_str[6]; 

    if (temp == 0) 
    {
        string[0] = '0';
        string[1] = '\0';
        return;
    }

    while (temp != 0) 
    {
        temp_str[length++] = '0' + mod10(temp);
        temp = div10(temp);
    }

    for (uint8_t i = 0; i < length; i++) 
    {
        string[i] = temp_str[length - i - 1];
    }

    string[length] = '\0';
}
