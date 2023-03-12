#pragma once
#include <avr/io.h>
#include <util/delay.h>

class Led
{
public:
    Led(volatile uint8_t *portx, volatile uint8_t *ddrx, uint8_t redPos, uint8_t greenPos);
    void switchGreen();
    void switchRed();
    void switchAmber();
    void turnedOff();

private:
    volatile uint8_t *portx_;
    volatile uint8_t *ddrx_;

    const uint8_t redPos_;
    const uint8_t greenPos_;

    const uint8_t DELAY_AMBER_GREEN_ = 30;
    const uint8_t DELAY_AMBER_RED_ = 10;
};
