#include "Button.h"

ButtonD2::ButtonD2(InterruptMode mode) : Button(InterruptNumber::INT0, mode) {}
ButtonD3::ButtonD3(InterruptMode mode) : Button(InterruptNumber::INT1, mode) {}
ButtonB2::ButtonB2(InterruptMode mode) : Button(InterruptNumber::INT2, mode) {}

Button::Button(InterruptNumber number, InterruptMode mode) : interruptNumber_(number)
{
    setPinMode(number);
    initialisation(mode);
}

void Button::setPinMode()
{
    switch (interruptNumber_)
    {
    case InterruptNumber::INT0:
        DDRD &= ~(1 << PIND2);
        break;

    case InterruptNumber::INT1:
        DDRD &= ~(1 << PIND3);
        break;

    case InterruptNumber::INT2:
        DDRB &= ~(1 << PINB2);
        break;
    }
}

void Button::initialisation(InterruptMode mode)
{
    cli();
    setInterruptMode(mode);
    disableInterrupt();
    sei();
}

void Button::clearInterruptFlag()
{
    _delay_ms(DEBOUNCE_DELAY);
    switch (interruptNumber_)
    {
    case InterruptNumber::INT0:
        EIFR |= (1 << INTF0);
        break;

    case InterruptNumber::INT1:
        EIFR |= (1 << INTF1);
        break;

    case InterruptNumber::INT2:
        EIFR |= (1 << INTF2);
        break;
    }
}

void Button::setInterruptMode(InterruptMode mode)
{
    cli();

    uint8_t modeFlags[][] = {
        {ISC00, ISC01}, // INT0
        {ISC10, ISC11}, // INT1
        {ISC20, ISC21}, // INT2
    };

    uint8_t ISCn0 = modeFlags[(uint8_t)interruptNumber_][0];
    uint8_t ISCn1 = modeFlags[(uint8_t)interruptNumber_][1];

    switch (mode)
    {
    case InterruptMode::FALLING_EDGE
        EICRA |= (1 << ISCn0);
        EICRA &= ~(1 << ISCn1);
        break;

    case InterruptMode::RISING_EDGE
        EICRA &= ~(1 << ISCn0);
        EICRA |= (1 << ISCn1);
        break;
        
    case InterruptMode::BOTH_EDGES
        EICRA |= (1 << ISCn0);
        EICRA |= (1 << ISCn1);
        break;
    }

    sei();
}

void Button::enableInterrupt()
{
    // TODO faire comme setPinMode :D
    switch (interruptNumber_)
    {
    case InterruptNumber::INT0:
        EIMSK |= (1 << INT0);
        break;

    case InterruptNumber::INT1:
        EIMSK |= (1 << INT1);
        break;

    case InterruptNumber::INT2:
        EIMSK |= (1 << INT2);
        break;
    }
}

void Button::disableInterrupt()
{
    switch (interruptNumber_)
    {
    case InterruptNumber::INT0:
        EIMSK &= ~(1 << INT0);
        break;

    case InterruptNumber::INT1:
        EIMSK &= ~(1 << INT0);
        break;

    case InterruptNumber::INT2:
        EIMSK &= ~(1 << INT0);
        break;
    }
}
