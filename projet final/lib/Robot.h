#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
#include "Position.h"
#include <util/delay.h>
#include "Memoire_24.h"

class Robot {
public:
    Robot();
    void initialisation();
    void searchPost();
    bool isEmptyTable();
    void setOrientation(uint16_t angle);

private: // TODO: remettre private
    void moveToPost();
    void replacePost();
    Position position_;
    Sensor sensor_;
    Pwm motor_;
    Memoire24CXXX memory_;
    const uint8_t rotateConst_ = 7; // Ã  partir de tests (7.5 est la valeur de base)
    uint8_t nDistancePost_;
    uint8_t rotateTime_;
    uint16_t memoryAdress_;
    bool isEmptyTable_ = false;
};
