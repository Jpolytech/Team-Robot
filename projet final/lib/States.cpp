#include "States.h"

StatesMachine::StatesMachine() : led_(Led(&PORTB, &DDRB, PB0, PB1)), timer1_(Timer1(WaveformMode::CTC, Prescaler::PRESCALE_1024)) {
    robot_.initialisation();
}

void StatesMachine::updateState()
{
    switch (state_) 
    {
        case States::INIT:
            if (isInterruptButtonPressed) 
            {
                isInterruptButtonPressed = false;
                state_ = States::DETECTION_ORIENTATION;
                _delay_ms(DELAY_200MS);
            }
            else if (isWhiteButtonPressed)
            {
                isWhiteButtonPressed = false;
                state_ = States::TRANSMISSION;
            }
            break;

        case States::DETECTION_ORIENTATION: 
            while(!isInterruptButtonPressed && !isWhiteButtonPressed)
            {
                led_.switchAmber();
            }

            if (isInterruptButtonPressed) 
            {
                robot_.setOrientation(ORIENTATION_UPWARDS);
                led_.switchGreen();
                _delay_ms(DELAY_2SEC);
                led_.turnedOff();
                state_ = States::START_DETECTION;
                isInterruptButtonPressed = false;
            }
            else if (isWhiteButtonPressed)
            {
                robot_.setOrientation(ORIENTATION_RIGHT);
                led_.switchRed();
                _delay_ms(DELAY_2SEC);
                led_.turnedOff();
                state_ = States::START_DETECTION;
                isWhiteButtonPressed = false;
            }
            break;

        case States::START_DETECTION: 
            robot_.searchPost();
            led_.turnedOff();
            state_ = States::WAIT_DETECTION;
            break;

        case States::WAIT_DETECTION:
            while (!isInterruptButtonPressed)
            {
                led_.toggleAmber(250);
                _delay_ms(250);
            };
            state_ = States::START_DETECTION;
            isInterruptButtonPressed = false;
            break;

        case States::TRANSMISSION: 
            led_.switchGreen();
            _delay_ms(DELAY_2SEC);
            timer1_.startTimer(DELAY_HALF_SEC_TICKS);
            svgPicture_.transfer();
            timer1_.stopTimer();
            state_ = States::END;
            break;

        case States::END:
            led_.turnedOff();
            while (true);
            break;
        }
}
