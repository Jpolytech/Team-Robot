#include "Led.h"

Led::Led(volatile uint8_t *ddrx,
         volatile uint8_t *portx,
         uint8_t greenPos,
         uint8_t redPos) : ddrx_(ddrx),
                           portx_(portx),
                           greenPos_(greenPos),
                           redPos_(redPos)
{
    *ddrx_ |= (1 << greenPos) | (1 << redPos);
}

Led::switchGreen()
{
    *portx_ |= (1 << greenPos_);
    *portx_ &= ~(1 << redPos_);
}

Led::switchRed()
{
    *portx_ &= ~(1 << greenPos_);
    *portx_ |= (1 << redPos_);
}

Led::switchAmber()
{
    switchGreen();
    _delay_ms(DELAY_AMBER_GREEN_);
    switchRed();
    _delay_ms(DELAY_AMBER_RED_);
}

Led::turnedOff()
{
    *portx_ &= ~(1 << greenPos_);
    *portx_ &= ~(1 << redPos_);
}
