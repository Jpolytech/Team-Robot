#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <switchingLedColours.h>

switchingLedColours::switchLedGreen(){
    *port_ |= (1 << setPos_);
    *port_ &= ~(1 << clearPos_);
}

switchingLedColours::switchLedRed()
{
    *port_ &= ~(1 << clearPos_);
    *port_ |= (1 << setPos_); 
}

switchingLedColours::switchLedAmber()
{
    switchLedGreen();
    _delay_ms(DELAY_AMBER_GREEN_);
    switchLedRed();
    _delay_ms(DELAY_AMBER_RED_);
}

switchingLedColours::turnedOffLed(){
    *port_ &= ~(1 << clearPos_);
    *port_ &= ~(1 << clearPos_);
}

