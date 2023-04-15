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
    void switchCase(bool isInterruptButtonPressed, bool isInterruptWhiteButtonPressed);

private:
    States state_;
    Led led_;
    SvgPicture svgPicture_;
    Robot robot_;
};
