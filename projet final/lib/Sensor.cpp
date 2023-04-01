#include "Sensor.h"

Sensor::Sensor() : adc_(can()) {}

uint8_t Sensor::getDistance() {
    uint8_t adcRetour;
    adcRetour = adc_.lecture(0) >> 2;
    return adcRetour;
}

uint8_t Sensor::getDistanceInCm() {
    return 27.3645 - 0.118754 * getDistance();
}