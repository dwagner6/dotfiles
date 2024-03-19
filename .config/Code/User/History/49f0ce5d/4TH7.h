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
#define LCD_CMD_R2_MASK     0xC0
#define LCD_POS_BEGIN       0x00

void configure_lcd();
_Bool lcd_command(uint8_t command);
_Bool lcd_putchar(char data);
void lcd_fsm();

#endif