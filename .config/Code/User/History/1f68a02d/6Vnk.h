#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <rp2040/m0plus.h>
#include <stdint.h>

#define enable_irq() asm ("CPSIE I")
#define disable_irq() asm ("CPSID I")
#define set_primask(V) asm ("MSR primask, %0" : : "r" (V) )

uint32_t get_primask()
{
    uint32_t retval;
    asm volatile ("MSR primask, %0" : : "r" (retval) );
    return retval;
}

#endif