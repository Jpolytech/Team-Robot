#include "ButtonD2.h"

ButtonD2::ButtonD2(InterruptMode mode = InterruptMode::RISING_EDGE)
{
    DDRD &= ~(1 << PIND2);
    initialisation(mode);
}

/*
 * Methode qui initialise le bouton
 *
 * */
void ButtonD2::initialisation(InterruptMode mode)
{
    cli();
    setInterruptMode(mode);
    disableInterrupt();
    sei();
}

void ButtonD2::clearInterruptFlag(void)
{
    _delay_ms(DEBOUNCE_DELAY);
    EIFR |= (1 << INTF0);
}

void ButtonD2::setInterruptMode(InterruptMode mode)
{
    switch (mode)
    {
    case InterruptMode::RISING_EDGE:
        EICRA |= (1 << ISC01) | (1 << ISC00);
        break;
        // TODO: Faire les autres modes
    case InterruptMode::FALLING_EDGE:
        EICRA |= (1 << ISC01);
        EICRA &= ~(1 << ISC00);
        break;

    case InterruptMode::BOTH_EDGE:
        EICRA |= (1 << ISC00);
        EICRA &= ~(1 << ISC01);
        break;
    }
}

void ButtonD2::enableInterrupt(void)
{
    EIMSK |= (1 << INT0);
}

void ButtonD2::disableInterrupt(void)
{
    EIMSK &= ~(1 << INT0);
}

// /*************************/
// // methode qui renvoie le dernier etat connu du bouton
// // renvoie un booleen
// /*************************/
// bool ButtonD2::getButtonState()
// {
//     return buttonIsPushed_;
// }