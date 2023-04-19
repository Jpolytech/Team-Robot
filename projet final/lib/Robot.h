#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sensor.h"
#include "Pwm.h"
#include "Led.h"
#include "Position.h"
#include <util/delay.h>
#include "Memoire_24.h"

class Robot {
public:
    Robot();
    void initialisation();
    void searchPost();
    bool getEmptyTable();
    void setOrientation(uint16_t angle);
    // void playHighNotes();

private: // TODO: remettre private
    void moveToPost();
    void replacePost();

    Position position_;
    Sensor sensor_;
    Pwm motor_;
    Memoire24CXXX memory_;
    // Sound sound_;

    Sensor::PolePosition nDistancePost_;
    uint16_t memoryAdress_;
    uint8_t rotateCount_;
    bool isEmptyTable_ = false;

    const uint8_t ROTATE_CONST = 3;
    const uint8_t FULL_CIRCLE_COUNT = 100;
    const uint8_t ROBOT_SPEED = 40; // 55 avant 
    const uint8_t TOP_ORIENTATION_ANGLE = 90;
    static constexpr uint16_t DELAY_MOTOR = 400;

};
