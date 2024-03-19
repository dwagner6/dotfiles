#include <rp2040/resets.h>
#include <rp2040/pll.h>
#include "pll.h"

void configure_usb_pll()
{
    resets -> clr_reset = RESETS_RESET_PLL_USB_MASK;
    while(! (resets -> reset_done & RESETS_RESET_DONE_PLL_USB_MASK))
        continue;

    pll_usb -> cs = PLL_USB_CS_REFDIV(1);
    pll_usb -> fbdiv_int = 120;
    pll_usb -> pwr = 1;
    while( !(pll_usb -> cs & PLL_USB_CS_LOCK_MASK))
        continue;

    pll_usb -> prim = 
            PLL_USB_PRIM_POSTDIV1(6) | PLL_USB_PRIM_POSTDIV2(5);
}