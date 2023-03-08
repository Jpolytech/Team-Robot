#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <switchingLedColours.h>

const uint8_t DELAY_AMBER_GREEN_ = 30;
const uint8_t DELAY_AMBER_RED_ = 10;

switchingLedColours::switchLedGreen()
{
    *portx_ |= (1 << setPos_);
    *portx_ &= ~(1 << clearPos_);
}

switchingLedColours::switchLedRed()
{
    *portx_ &= ~(1 << clearPos_);
    *portx_ |= (1 << setPos_); 
}

switchingLedColours::switchLedAmber()
{
    switchLedGreen();
    _delay_ms(DELAY_AMBER_GREEN_);
    switchLedRed();
    _delay_ms(DELAY_AMBER_RED_);
}

switchingLedColours::turnedOffLed()
{
    *portx_ &= ~(1 << clearPos_);
    *portx_ &= ~(1 << clearPos_);
}

