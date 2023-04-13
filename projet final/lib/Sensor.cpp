#include "Sensor.h"

Sensor::Sensor() : adc_(can()) {}

uint8_t Sensor::getDistance() {
    uint8_t adcRetour;
    adcRetour = adc_.lecture(0) >> 2;
    lastDistance_ = adcRetour;
    return adcRetour;
}

//methode qui renvoie 1 si le poteau se trouve autour du robot (>=11"), 2 si c'est plus eloigné (>=22") et 0 si il y a rien
uint8_t Sensor::getSpot() {
    getDistance();
    if(lastDistance_ >= distanceMaxFirstPos) {
        return 1; // le poteau est dans l'entourage du robot
    }
    else if(lastDistance_ <= distanceMinSecondPos && lastDistance_ >= distanceMaxSecondPos) {
        return 2;
    }
    return 0;
}

//methode qui renvoie vraie si le poteau est à plus de 10cm
bool Sensor::isSpotFar() {
    getDistance();
    if(lastDistance_ >= distanceMin_) {
        return false;
    }
    return true;
}

bool Sensor::isSpotLost() {
    getDistance();
    if(lastDistance_ > distanceMaxSecondPos) {
        //le robot n'a pas perdu la direction
        return false;
    }
    return true;
}