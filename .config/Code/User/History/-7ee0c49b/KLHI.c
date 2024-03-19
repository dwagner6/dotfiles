#include <stdint.h>
#include <stdbool.h>

#ifndef NUM_CALLBACKS
#define NUM_CALLBACKS   5
#endif

static void (*callback[NUM_CALLBACKS])();
static uint32_t num_callbacks;

_Bool systick_register_callback( void(*p_fn)() )
{
    if(NUM_CALLBACKS == num_callbacks)
        return false;
    callback[num_callbacks++] = p_fn;
    return true;
}

void __attribute__((isr)) SystickHandler()
{
    systick_fired_flag = true;
    for(uint32_t i = 0; i<num_callbacks; i++)
        callback[i]();
}