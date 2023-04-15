#include "States.h"

StatesMachine::StatesMachine() : led_(Led(&PORTB, &DDRB, PB0, PB1)) {}

void StatesMachine::switchCase(bool isInterruptButtonPressed, bool isWhiteButtonPressed)
{
    switch (state_) 
    {
        // while (isInterruptButtonPressed == false || isWhiteButtonPressed == false){};
        case States::INIT:
            // a enlever
            led_.switchGreen();
            if (isInterruptButtonPressed == true) 
            {
                isInterruptButtonPressed = false;
                state_ = States::DETECTION_ORIENTATION;
            }
            else if (isWhiteButtonPressed == true)
            {
                isWhiteButtonPressed = false;
                state_ = States::TRANSMISSION;
            }
            break;

        case States::DETECTION_ORIENTATION: 
            // allumer led en ambre
            while(isInterruptButtonPressed == false || isWhiteButtonPressed == false)
            {
                led_.switchAmber();
            }
            if (isInterruptButtonPressed == true) 
            {
                // mettre orientation 90
                robot_.setOrientation(90);
                // allumer led_ en vert
                led_.switchGreen();
                // delay 2sec
                _delay_ms(2000);
                led_.turnedOff();
                state_ = States::START_DETECTION;
            }
            else if (isWhiteButtonPressed == true)
            {
                // mettre orientation 0
                robot_.setOrientation(0);
                // allumer led_ en rouge
                led_.switchRed();
                // delay 2sec
                _delay_ms(2000);
                led_.turnedOff();
                state_ = States::START_DETECTION;
            }
            break;

        case States::START_DETECTION: 
            // call detection method
            robot_.searchPost();
            // quand detection fini dun poteau -> allumer led_ en ambre a 2Hz
            if (isInterruptButtonPressed == true) 
            {
                state_ = States::START_DETECTION;
            }
            // turned off led_
            led_.turnedOff();
            break;

        case States::TRANSMISSION: 
            // allumer led vert pendant la transmission
            while (true)
            {
                led_.turnedOff();
            }
            // call transmission method
            svgPicture_.transfer();
            if (isInterruptButtonPressed == true) 
            {
                state_ = States::END;
            }
            break;

        case States::END:
        // turned off led
        led_.turnedOff();
        while (true);
        break;
        }
}
