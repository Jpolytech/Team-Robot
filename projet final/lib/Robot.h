#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
#include "Uart.h"
#include "Position.h"
#include <util/delay.h>
#include "Memoire_24.h"

class Robot {
public:
    Robot(uint16_t angle);
    void initialisation();
    void searchPost();

private:
    void moveToPost();
    void replacePost();
    Pwm motor_;
    ManagementUSART usart_;
    Sensor sensor_;
    Position position_;
    Memoire24CXXX memory_;
    const uint8_t rotateConst_ = 7; // à partir de tests (7.5 est la valeur de base)
    uint8_t nDistancePost_;
    uint8_t rotateTime_;
    uint16_t memoryAdress_;
};