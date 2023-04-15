#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Can.h"
#include <util/delay.h>

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
    uint8_t distance1, distance2, distance3, distance4;
    const uint8_t distanceMaxFirstPos = 127;
    const uint8_t distanceMinSecondPos = 93; //90
    const uint8_t distanceMaxSecondPos = 57; //verifier cette valeur 55
    const uint8_t distanceMin_ = 255;
};