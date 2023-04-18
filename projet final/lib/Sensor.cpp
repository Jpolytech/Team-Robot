#include "Sensor.h"

Sensor::Sensor() {
    DDRA &= ~(1 << DDA0);
}

uint8_t Sensor::getDistance() {
    const uint8_t N_READ = 5;
    
    uint32_t distanceSum = 0;
    for (int i = 0; i < N_READ; i++)
    {
        uint8_t distance = adc_.lecture(PA0) >> 2;
        distanceSum += distance;
    }
    return distanceSum / N_READ;
}

//methode qui renvoie 1 si le poteau se trouve autour du robot (>=11"), 2 si c'est plus eloigné (>=22") et 0 si il y a rien
Sensor::PolePosition Sensor::getSpot() { 
    uint8_t distance = getDistance();

    if(distance >= distanceMaxFirstPos) 
    {
        return PolePosition::CLOSE;
    }
    else if(distance >= distanceMaxSecondPos) 
    {
        return PolePosition::FAR;
    }
    return PolePosition::NONE;
}

bool Sensor::isSpotEncountered() {
    return getDistance() >= finalDistance;
}

bool Sensor::isSpotLost() {
    return getSpot() == PolePosition::NONE;
}
