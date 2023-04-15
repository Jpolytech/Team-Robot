#include "States.h"

StatesMachine::StatesMachine() : led_(Led(&PORTB, &DDRB, PB0, PB1)) {}

void StatesMachine::switchCase(bool isInterruptButtonPressed, bool isInterruptWhiteButtonPressed)
{
    switch (state_) 
    {
        case States::INIT:
            if (isInterruptButtonPressed == true) 
            {
                state_ = States::DETECTION_ORIENTATION;
            }
            else if (isInterruptWhiteButtonPressed == true)
            {
                state_ = States::TRANSMISSION;
            }
            break;

        case States::DETECTION_ORIENTATION: 
            // allumer led en ambre
            led_.switchAmber();
            if (isInterruptButtonPressed == true) 
            {
                // mettre orientation 90
                robot_.setOrientation(90);
                // allumer led_ en vert
                led_.switchGreen();
                // delay 2sec
                _delay_ms(2000);
                state_ = States::START_DETECTION;
            }
            else if (isInterruptWhiteButtonPressed == true)
            {
                // mettre orientation 0
                robot_.setOrientation(0);
                // allumer led_ en rouge
                led_.switchRed();
                // delay 2sec
                _delay_ms(2000);
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
            
            // call transmission method
            led_.switchGreen();
            svgPicture_.transfer();
            // allumer led vert pendant la transmission
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
