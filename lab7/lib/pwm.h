#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Pwm
{
public:
    Pwm();
    void initialisation();
    void movingForward(uint8_t percentage);
    void movingBackward(uint8_t percentage);
    void turnedOff(uint8_t percentage);
    void turnRight(uint8_t percentage);
    void turnLeft(uint8_t percentage);
};