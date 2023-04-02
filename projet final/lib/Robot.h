#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
#include <util/delay.h>

class Robot {
public:
    Robot();
    void searchPost();
    void moveToPost();
    void initialisation();

private:
    Pwm motor_;
    Sensor sensor_;
    uint8_t distanceObj_;

};