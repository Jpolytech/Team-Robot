#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Can.h"
#include <util/delay.h>

class Sensor 
{
public:
    enum class PolePosition {
        CLOSE = 1,
        FAR = 2,
        NONE = 0
    };
    
    Sensor();
    uint8_t getDistance();
    PolePosition getSpot();
    bool isSpotEncountered();
    bool isSpotLost();

private:
    can adc_;
    uint8_t lastDistance_;
    const uint8_t distanceMaxFirstPos = 65; // 50
    const uint8_t distanceMaxSecondPos = 30; // 30
    const uint8_t finalDistance = 100; // 123
};

/*
    [distanceMaxFirstPos , 255] - poteau 1
    [distanceMaxSecondPos , distanceMaxFirstPos] - poteau 2

    if(distanceMoy >= distanceMaxFirstPos) {
        return 1; // le poteau est dans l'entourage du robot
    }
    else if(distanceMoy <= distanceMinSecondPos && distanceMoy >= distanceMaxSecondPos) {
        return 2;
    }
    return 0;
}

*/