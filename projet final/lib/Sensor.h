#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Can.h"

class Sensor 
{
public:
    Sensor();
    uint8_t getDistance();
    uint8_t getSpot();
    bool isSpotFar();
    bool isSpotLost();

//private:
    can adc_;
    uint8_t lastDistance_;
    const uint8_t distanceMaxFirstPos = 127;
    const uint8_t distanceMinSecondPos = 90;
    const uint8_t distanceMaxSecondPos = 55; //verifier cette valeur 55
    const uint8_t distanceMin_ = 255;
};