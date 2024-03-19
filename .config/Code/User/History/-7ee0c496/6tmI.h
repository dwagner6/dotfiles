#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdbool.h>

void configure_systick();
_Bool systick_has_fired();
_Bool systick_register_callback( void(*p_fn)() );

#endif