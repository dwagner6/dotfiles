#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <rp2040/m0plus.h>
#include <stdint.h>

#define enable_irq() asm volatile ("CPSIE I")
#define disable_irq() asm volatile ("CPSID I")

static uint32_t get_primask()
{
    uint32_t primask;
    __asm__ volatile ("MRS %0, primask" : "=r" (primask) );
    return primask;
}

static void set_primask(uint32_t primask)
{
   __asm__ volatile ("MSR primask, %0" : : "r" (primask) ); 
}

#endif