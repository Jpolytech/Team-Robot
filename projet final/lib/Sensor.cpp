#include "Sensor.h"

Sensor::Sensor() {}

uint8_t Sensor::getDistance() {
    uint8_t adcRetour;
    adcRetour = adc_.lecture(PA0) >> 2; // TODO : nb magique 
    lastDistance_ = adcRetour;
    return adcRetour;
}

//methode qui renvoie 1 si le poteau se trouve autour du robot (>=11"), 2 si c'est plus eloigné (>=22") et 0 si il y a rien
uint8_t Sensor::getSpot() { // TODO: Retourner un enum plutot qu'un uint8_t ex: enum {NOTHING, CLOSE, FAR}
    const uint8_t N_READ = 5;
    uint8_t distanceSum = 0;
    
    for (int i = 0; i < N_READ; i++)
    {
        distanceSum += getDistance();
        _delay_ms(5); // TODO: nb magique -> a verifier
    }

    uint8_t distanceMoy = distanceSum / N_READ;

    if(lastDistance_ >= distanceMaxFirstPos) { // TODO: distanceMoy ???
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
    // TODO: Return (lastDistance_ < distanceMin_)
}

bool Sensor::isSpotLost() {
    getDistance();
    if(lastDistance_ > distanceMaxSecondPos) {
        //le robot n'a pas perdu la direction
        return false;
    }
    return true;
    // TODO: Return (lastDistance_ <= distanceMin_)
}
