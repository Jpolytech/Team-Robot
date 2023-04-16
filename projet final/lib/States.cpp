#include "States.h"

StatesMachine::StatesMachine() : led_(Led(&PORTB, &DDRB, PB0, PB1)), timer1_(Timer1(WaveformMode::CTC, Prescaler::PRESCALE_1024)) {
    robot_.initialisation();
}

void StatesMachine::updateState()
{
    switch (state_) 
    {
        case States::INIT:
            // pour verifier quon est dans cet etat initialement -> a enlever
            // led_.switchGreen();
            if (isInterruptButtonPressed) 
            {
                isInterruptButtonPressed = false;
                state_ = States::DETECTION_ORIENTATION;
            }
            else if (isWhiteButtonPressed)
            {
                isWhiteButtonPressed = false;
                state_ = States::TRANSMISSION;
            }
            break;

        case States::DETECTION_ORIENTATION: 
            // allumer led en ambre tant quon choisit pas orientation
            while(!isInterruptButtonPressed && !isWhiteButtonPressed)
            {
                led_.switchAmber();
            }

            if (isInterruptButtonPressed) 
            {
                // mettre orientation 90
                robot_.setOrientation(ORIENTATION_UPWARDS);
                // allumer led_ en vert
                led_.switchGreen();
                // delay 2sec
                _delay_ms(DELAY_2SEC);
                led_.turnedOff();
                state_ = States::START_DETECTION;
                isInterruptButtonPressed = false;
            }
            else if (isWhiteButtonPressed)
            {
                // mettre orientation 0
                robot_.setOrientation(ORIENTATION_RIGHT);
                // allumer led_ en rouge
                led_.switchRed();
                // delay 2sec
                _delay_ms(DELAY_2SEC);
                led_.turnedOff();
                state_ = States::START_DETECTION;
                isWhiteButtonPressed = false;
            }
            break;

        case States::START_DETECTION: 
            robot_.searchPost();
            while (!isInterruptButtonPressed){};
            led_.turnedOff();
            break;

        case States::TRANSMISSION: 
            led_.switchGreen();
            _delay_ms(DELAY_2SEC);
            // allumer led vert pendant la transmission avec methode pour lancer une interruption 
            timer1_.startTimer(391);
            // call transmission method
            svgPicture_.transfer();
            timer1_.stopTimer();
            state_ = States::END;
            break;

        case States::END:
            // turned off led
            led_.turnedOff();
            while (true);
            break;
        }
}
