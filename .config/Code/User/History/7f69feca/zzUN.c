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


uint32_t str_to_uint32(const char * string);
void int_to_hex_str(uint8_t num_digits, uint32_t value, char * hex_string);

int main()
{
    configure_systick();
    configure_watchdog(1500);
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

        static char key;
        if(get_key(&key))
        {
            if(key == '*')
            {
                lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START);
                continue;
            }

            if(key == '#')
            {
                lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_END);
                continue;
            }

            
            static uint8_t row1_pos = 0;
            static char * row1_chars = "00000000";
            static char * row2_chars = "00000000";

            *(row1_chars + row1_pos) = key;
            lcd_putchar(key);
            row1_pos++;

            if(row1_pos + NUM_FIELD_START > NUM_FIELD_END)
            {
                lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START);
                row1_pos = 0;
            }

            uint32_t row1_value = str_to_uint32(row1_chars);

            int_to_hex_str(NUM_FIELD_LENGTH, row1_value, row2_chars);
            
            lcd_command(LCD_CMD_GOTO | LCD_R2 | NUM_FIELD_START);
            lcd_print_string(row2_chars);
            lcd_command(LCD_CMD_GOTO | LCD_R1 | NUM_FIELD_START + row1_pos);
        }
        

        lcd_fsm();
        feed_the_watchdog();
    }
    
}

// Will add these to uclib
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