#pragma once
#include "Led.h"
#include "Robot.h"
#include "SvgPicture.h"
#include "Button.h"
#include "Timer1.h"
#include <util/delay.h>
#include <avr/io.h>

enum class States {
    INIT,
    DETECTION_ORIENTATION,
    START_DETECTION,
    TRANSMISSION,
    END
};

class StatesMachine {

public:
    StatesMachine();
    void updateState();
    volatile bool isInterruptButtonPressed = false;
    volatile bool isWhiteButtonPressed = false;

private:
    Robot robot_;
    States state_;
    Led led_;
    SvgPicture svgPicture_; 
    Timer1 timer1_;

    static constexpr uint16_t DELAY_2SEC = 2000;
    const uint16_t DELAY_HALF_SEC_TICKS = 391;
    const uint8_t ORIENTATION_RIGHT = 0;
    const uint8_t ORIENTATION_UPWARDS = 90;
};
