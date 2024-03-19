/***********************************************************************
* FILENAME :        lcd.h          
*
* DESCRIPTION :     Driver interface for NHD-021K1Z wired in 4-bit mode
*
* AUTHOR :    Doug Wagner        START DATE :    12 NOV 23
* 
************************************************************************/

#ifndef LCD_H
#define LCD_H

#include <stdbool.h>
#include <stdint.h>

#define LCD_CMD_CLR_DISP    0x01
#define LCD_R1              0x00
#define LCD_R2              0x40
#define LCD_BEGIN_ROW       0x00
#define LCD_CMD_GOTO        0x80

void configure_lcd();
_Bool lcd_command(uint8_t command);
_Bool lcd_putchar(char data);
void lcd_fsm();

#endif