#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
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
    Sensor sensor_;
    uint8_t distanceObj_;

};