#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

class Led
{
public:
    Led(volatile uint8_t *portx, volatile uint8_t *ddrx, uint8_t greenPos, uint8_t redPos);
    void switchGreen();
    void switchRed();
    void switchAmber();
    void turnedOff();

private:
    volatile uint8_t *portx_;
    volatile uint8_t *ddrx_;

    const uint8_t greenPos_;
    const uint8_t redPos_;

    static constexpr uint8_t DELAY_AMBER_GREEN_ = 30;
    static constexpr uint8_t DELAY_AMBER_RED_ = 10;
};
