#include "usbcdc.h"
#include "uclib.h"
#include <stdint.h>
#include <rp2040/spi.h>

int main()
{
    char c;
    configure_spi0();
    configure_usbcdc();

    while(1)
    {
        if( usbcdc_getchar(&c) )
        {
            usbcdc_putchar(':');
            print_hex(2, spi0 -> sspdr);
            print_hex(2, spi0 -> sspdr);
            spi0 -> sspdr = 0x8f;
            spi0 -> sspdr = 00;
        }
    }

    return 0;
}