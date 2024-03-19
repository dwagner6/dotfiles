/***********************************************************************
* FILENAME :        assign5.c           
*
* DESCRIPTION :     EECE 458 Embedded Systems Design
*                   Programming Assignment 5 
*           
*           Implements assignment 5, which uses a keypad and LCD 
*           together. Display has format
*               X: AAAAAAAA
*               Y: BBBBBBBB
*           where the series of As are a user-entered BCD, and the
*           series of Bs are the hex representation of the number.
*           The * key moves to leftmost position, # key to the 
*           rightmost. Cursor wraps around to first position.
*
* AUTHOR :    Doug Wagner        START DATE :    12 NOV 23
* 
************************************************************************/

#include "systick.h"
#include "lcd.h"
#include "watchdog.h"
#include "keypad.h"
#include <stdbool.h>
#include <stdint.h>

#define NUM_FIELD_START     0x03
#define NUM_FIELD_END       0x0a
#define NUM_FIELD_LENGTH    8

void lcd_print_string(char const * string);
uint32_t str_to_uint32(const char * string);

int main()
{
    configure_systick();
    configure_watchdog(150000);
    configure_lcd();
    configure_keypad();

    lcd_print_string("X: 00000000");
    lcd_command(LCD_CMD_GOTO | LCD_R2);
    lcd_print_string("Y: 00000000");
    lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START);
    
    while(1)
    {
        if(!systick_has_fired())
            continue;

        static uint8_t row1_pos = 0;
        static char * row1_chars = "00000000";
        static char * row2_chars = "BBBBBBBB";

        static char key;
        if(get_key(&key))
        {
            *(row1_chars + row1_pos) = key;
            lcd_putchar(key);
            row1_pos++;

            if(row1_pos + NUM_FIELD_START > NUM_FIELD_END)
            {
                lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START);
                row1_pos = 0;
            }

            uint32_t row1_value = str_to_uint32(row1_chars);

            for(i = NUM_FIELD_LENGTH - 1; i>=0; i--)
            {
                uint8_t hex_digit = (row1_value >> 4*i) & 0xf;
                *(row2_chars+i) = hex_digit+( (hex_digit < 10)?'0':'A'-10);
            }
            lcd_command(LCD_CMD_GOTO | LCD_R2 | NUM_FIELD_START);
            lcd_print_string(row2_chars);
            lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START + row1_pos);
        }
        lcd_fsm();
        feed_the_watchdog();
    }
    
}

void lcd_print_string(char const * string)
{
    while(*string && lcd_putchar(*string++))
        continue;
}

uint32_t str_to_uint32(const char * string)
{
    uint32_t result = 0;
    const char * start = string;

    while(*string != '\0')
    {
        result = result * 10 + (*string - '0');
        string++;
    }
    return result;
}