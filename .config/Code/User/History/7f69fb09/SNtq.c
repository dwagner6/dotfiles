/***********************************************************************
* FILENAME :        assign4.c           
*
* DESCRIPTION :     EECE 458 Embedded Systems Design
*                   Programming Assignment 4
*        
*           Implements Assignment 4. FSM scans for key presses and 
*           returns a unique value for each of the 12 keys.
*           Each unique value is mapped to the ASCII character displayed
*           on the keypad.  The mapped keypresses are output on the
*           serial terminal.        
*
* AUTHOR :    Doug Wagner        START DATE :    25 OCT 23
* 
************************************************************************/

#include "watchdog.h"
#include "systick.h"
#include "usbcdc.h"
#include "keypad.h"
#include "uclib.h"
#include <stdint.h>
#include <stdbool.h>

/* #define WATCHDOG_TIMEOUT_US     1500
#define NO_ROWS_DETECTED        0xf     
#define DEBOUNCE_DELAY_MS       100

_Bool get_key(char * key); */

int main(void)
{
    configure_systick();        
    configure_watchdog(WATCHDOG_TIMEOUT_US);
    configure_keypad();
    configure_usbcdc();

    while(1)
    {
        if(!systick_has_fired())
            continue;

        char key;
        if(get_key(&key))
        {
            usbcdc_putchar(key);
            print_string("\n\r");
        }

        feed_the_watchdog();
    }
    
}



/* _Bool get_key(char * key)
{
    const char * ascii_char_map = "#9630852*741";
    typedef enum {WAIT_PRESS, DEBOUNCE, CHECK_C0, 
                CHECK_C1, CHECK_C2, RELEASE} state_t;
    static state_t state = WAIT_PRESS;
    static uint8_t deb_cnt;
    enum {SCAN_C0, SCAN_C1, SCAN_C2};

    uint8_t row = keypad_get_row();

    switch(state)
    {
        case WAIT_PRESS: 
            keypad_scan_column(ALL_KEYPAD_COLUMNS);
            if(row != NO_ROWS_DETECTED)
            {
                state = DEBOUNCE;
                deb_cnt = 0;
            }
            return false;

        case DEBOUNCE:
            if(row != NO_ROWS_DETECTED)
            {
                if(deb_cnt < DEBOUNCE_DELAY_MS)
                    deb_cnt++;
                if(deb_cnt >= DEBOUNCE_DELAY_MS)
                {
                    state = CHECK_C0;
                    keypad_scan_column(SCAN_C0);
                }
            }
            
            return false;

        case CHECK_C0:
            if(row != NO_ROWS_DETECTED)
            {
                state = RELEASE;
                *key = ascii_char_map[(4*SCAN_C0) + row];
                return true;
            }
            else
            {
                state = CHECK_C1;
                keypad_scan_column(SCAN_C1);
                return false;
            }
        
        case CHECK_C1:
            if(row != NO_ROWS_DETECTED)
            {
                state = RELEASE;
                *key = ascii_char_map[(4*SCAN_C1) + row];
                return true;
            }
            else
            {
                state = CHECK_C2;
                keypad_scan_column(SCAN_C2);
                return false;
            }
        
        case CHECK_C2:
            if(row != NO_ROWS_DETECTED)
            {
                state = RELEASE;
                *key = ascii_char_map[(4*SCAN_C2) + row];
                return true;
            }
            else
            {
                state = WAIT_PRESS;
                return false;
            }
        
        case RELEASE:
            if(row == NO_ROWS_DETECTED)
                state = WAIT_PRESS;
            return false;
        
        default:
            return false;
    }

} */