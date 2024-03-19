#include "i2c0.h"
#include "uclib.h"
#include "tps55289.h"
#include "pb.h"
#include "lcd.h"
#include "adc.h"
#include "systick.h"
#include "interrupt.h"
#include <rp2040/i2c.h>
#include <stdbool.h>
#include <stdint.h>

#define VOUT_UP_PB_LOC     15
#define VOUT_DOWN_PB_LOC   14
#define ENABLE_PB_LOC   13

#define VOUT_STEP_MV    100
#define LCD_VOUT_FIELD  0x06
#define LCD_IMON_FIELD  0x06 
#define LCD_EN_FIELD    0x0C
#define DIR_DOWN        0
#define DIR_UP          1

void configure_power_supply();
void power_supply_fsm();
void initialize_display(char *vout_str, char *imon_str);
void turn_on_power_supply();
void turn_off_power_supply();
void set_vout(uint8_t direction);
void update_imon();
void zero_imon();

char vout_str[6];
char imon_str[6];

int main()
{
    disable_irq();
    configure_power_supply();
    enable_irq();

    while(1)
    {
        if(!systick_has_fired())
            continue;

        lcd_fsm();
        power_supply_fsm();
    }
}

void power_supply_fsm()
{
    _Bool up_pb_pressed = get_pb(VOUT_UP_PB_LOC);
    _Bool down_pb_pressed = get_pb(VOUT_DOWN_PB_LOC);
    _Bool enable_pb_pressed = get_pb(ENABLE_PB_LOC);

    static enum {RESET, OFF, ON} state = RESET;
    static uint16_t loop_cnt = 0;

    switch(state)
    {
        case RESET:
            if(enable_pb_pressed)
            {
                state = ON;
                turn_on_power_supply();
            }   
            
            if(up_pb_pressed)
                state = OFF;
            
            if(down_pb_pressed)
                state = OFF;
    
            break;
        
        case OFF:
            if(enable_pb_pressed)
            {
                state = ON;
                turn_on_power_supply();
            }
            if(down_pb_pressed)
            {
                set_vout(DIR_DOWN);
            }
            if(up_pb_pressed)
            {
                set_vout(DIR_UP);
            }

            
            break;

        case ON:
            if(enable_pb_pressed)
            {
                state = OFF;
                turn_off_power_supply();
                zero_imon();
                break;
            }

            if(down_pb_pressed)
            {
                set_vout(DIR_DOWN);
            }

            if(up_pb_pressed)
            {
                set_vout(DIR_UP);
            }

            if(++loop_cnt > 500)
            {
                loop_cnt = 0;
                update_imon();
            }
            break;
    }
}

void set_vout(uint8_t direction)
{
    static uint16_t vout = VOUT_DEFAULT_MV;

    if(direction == DIR_DOWN)
    {
        if(vout > 800)
            vout -= VOUT_STEP_MV;
        else if(vout <= 800)
            vout = 800;
    }
    else if(direction == DIR_UP)
    {
        if(vout < VOUT_SET_MAX)
            vout += VOUT_STEP_MV;
        else if(vout >= VOUT_SET_MAX)
            vout = VOUT_SET_MAX;
    }

    tps55289_set_vout(vout);
    uint16_to_fixed_str(vout, vout_str);
    lcd_command(LCD_CMD_GOTO | LCD_R1 | LCD_VOUT_FIELD);
    lcd_print_string(vout_str);  
}

void initialize_display(char * vout_str, char * imon_str)
{
    uint16_to_fixed_str(VOUT_DEFAULT_MV, vout_str);
    lcd_print_string("VOUT:       OFF");
    lcd_command(LCD_CMD_GOTO | LCD_R1 | LCD_VOUT_FIELD);
    lcd_print_string(vout_str);
    lcd_command(LCD_CMD_GOTO | LCD_R2);
    lcd_print_string("IMON:     0 MA");
}

void turn_on_power_supply()
{
    tps55289_enable_output();    
    lcd_command(LCD_CMD_GOTO | LCD_R1 | LCD_EN_FIELD);
    lcd_print_string("ON "); 
}

void turn_off_power_supply()
{
    tps55289_disable_output();
    lcd_command(LCD_CMD_GOTO | LCD_R1 | LCD_EN_FIELD);
    lcd_print_string("OFF");
}

void configure_power_supply()
{
    configure_adc();
    enable_adc();
    configure_systick();
    configure_pb(VOUT_UP_PB_LOC);
    configure_pb(VOUT_DOWN_PB_LOC);
    configure_pb(ENABLE_PB_LOC);
    configure_i2c0();
    configure_lcd();
    
    tps55289_set_vout(VOUT_DEFAULT_MV);
    initialize_display(vout_str, imon_str);
}

void update_imon()
{
    uint16_t adc_result = adc_to_millivolts(get_adc_raw());
    lcd_command(LCD_CMD_GOTO | LCD_R2 | LCD_IMON_FIELD);
    uint16_to_fixed_str(adc_result, imon_str);
    lcd_print_string(imon_str);
}

void zero_imon()
{
    lcd_command(LCD_CMD_GOTO | LCD_R2 | LCD_IMON_FIELD);
    uint16_to_fixed_str(0, imon_str);
    lcd_print_string(imon_str); 
}