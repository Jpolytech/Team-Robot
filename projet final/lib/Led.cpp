#include "Led.h"

Led::Led(volatile uint8_t *portx,
         volatile uint8_t *ddrx,
         uint8_t greenPos,
         uint8_t redPos) : portx_(portx),
                           ddrx_(ddrx),
                           greenPos_(greenPos),
                           redPos_(redPos)
{
    *ddrx_ |= (1 << greenPos) | (1 << redPos);
}

void Led::switchGreen()
{
    *portx_ |= (1 << greenPos_);
    *portx_ &= ~(1 << redPos_);
}

void Led::switchRed()
{
    *portx_ |= (1 << redPos_);
    *portx_ &= ~(1 << greenPos_);
}

void Led::switchAmber()
{
    switchGreen();
    _delay_ms(DELAY_AMBER_GREEN_);
    switchRed();
    _delay_ms(DELAY_AMBER_RED_);
}

void Led::turnedOff()
{
    *portx_ &= ~(1 << greenPos_);
    *portx_ &= ~(1 << redPos_);
}
