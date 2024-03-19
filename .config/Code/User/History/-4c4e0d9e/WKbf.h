#ifndef LCD_FIFO_H
#define LCD_FIFO_H

#include <stdbool.h>
#include <stdint.h>

#define LCD_CLR_DISP    0x02

void configure_lcd();
_Bool lcd_command(uint8_t command);
_Bool lcd_putchar(char data);
void lcd_fsm();

#endif