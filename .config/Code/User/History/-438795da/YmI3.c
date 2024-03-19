#include <stdint.h>

uint16_t div10( uint16_t x )
{
    return x/10;
}

uint16_t mod10( uint16_t x )
{
    return x%10;
}

int main()
{
    volatile x = div10(1932);
    volatile y = mod10(x);
}