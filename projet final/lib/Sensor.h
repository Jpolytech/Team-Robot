#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <can.h>

class Sensor 
{
public:
    Sensor();
    uint8_t getDistance();
    uint8_t getDistanceInCm();

private:
    can adc_;
};