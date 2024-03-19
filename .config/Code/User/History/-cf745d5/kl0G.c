#include "systick_int.h"
#include <stdint.h>
#include "led.h"

int main (void)
{
    uint16_t cnt = 0;
    configure_systick();
}