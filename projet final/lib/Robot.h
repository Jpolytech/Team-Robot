#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
#include "Uart.h"
#include "Position.h"
#include <util/delay.h>

class Robot {
public:
    Robot();
    void initialisation();
    void searchPost();
    void moveToPost();
    void replacePost();

private:
    Pwm motor_;
    ManagementUSART usart_;
    Sensor sensor_;
    Position position_;
    const uint8_t rotateConst_ = 7.5; // à partir de tests
    uint8_t nDistancePost_;
    uint8_t rotateTime_;
};