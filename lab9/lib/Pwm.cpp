#include "Pwm.h"

Pwm::Pwm() 
{
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
}

void Pwm::initialisation()
{
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
}

void Pwm::movingBackward(uint8_t percentage)
{
    OCR1A = percentage*254/100;
    OCR1B = percentage*254/100;
    PORTD |= (1 << PORTD6);
    PORTD |= (1 << PORTD7);
}

void Pwm::movingForward(uint8_t percentage)
{
    OCR1A = percentage*254/100;
    OCR1B = percentage*254/100;
    PORTD &= ~(1 << PORTD6);
    PORTD &= ~(1 << PORTD7);
}

void Pwm::turnedOff()
{
    OCR1A = 0;
    OCR1B = 0;
}

void Pwm::turnRight(uint8_t percentage)
{
    OCR1A = percentage*254/100;
    OCR1B = 0;
    PORTD |= (1 << PORTD6);
    PORTD |= (1 << PORTD7);
}

void Pwm::turnLeft(uint8_t percentage)
{
    OCR1A = 0;
    OCR1B = percentage*254/100;
    PORTD |= (1 << PORTD6);
    PORTD |= (1 << PORTD7);
}
