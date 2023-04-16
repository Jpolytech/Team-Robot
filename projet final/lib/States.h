#pragma once
#include "Led.h"
#include "Robot.h"
#include "SvgPicture.h"
#include "Button.h"
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

    const int ORIENTATION_RIGHT = 0;
    const int ORIENTATION_UPWARDS = 90;
};
