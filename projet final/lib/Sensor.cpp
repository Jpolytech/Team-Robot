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
    distance1 = getDistance();
    _delay_ms(5);
    distance2 = getDistance();
    _delay_ms(5);
    distance3 = getDistance();
    _delay_ms(5);
    distance4 = getDistance();
    _delay_ms(5);
    getDistance();
    _delay_ms(5);
    uint8_t distanceMoy = (lastDistance_ + distance1 + distance2 + distance3 + distance4) / 5;
    if(lastDistance_ >= distanceMaxFirstPos) {
        return 1; // le poteau est dans l'entourage du robot
    }
    else if(distanceMoy <= distanceMinSecondPos && distanceMoy >= distanceMaxSecondPos) {
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
