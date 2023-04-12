#include "Pwm.h"

Pwm::Pwm()
{
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
}

void Pwm::initialisation()
{
    TCNT0 = 0;
    OCR0A = 0;
    OCR0B = 0;
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B |= (1 << CS01);
    TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B);
}

uint8_t Pwm::convertTicksToPercentage(uint8_t percentage)
{
    return percentage * NUMBER_OF_TICKS / PERCENTAGE;
}

void Pwm::movingBackward(uint8_t percentage)
{
    OCR0A = convertTicksToPercentage(percentage) - offsetRight;
    OCR0B = convertTicksToPercentage(percentage) - offsetLeft;
    PORTB |= (1 << PORTB2);
    PORTB |= (1 << PORTB5);
}

void Pwm::movingForward(uint8_t percentage)
{
    OCR0A = convertTicksToPercentage(percentage) - offsetRight;
    OCR0B = convertTicksToPercentage(percentage) - offsetLeft;
    PORTB &= ~(1 << PORTB2);
    PORTB &= ~(1 << PORTB5);
}

void Pwm::turnedOff()
{
    OCR0A = 0;
    OCR0B = 0;
}

void Pwm::turnLeft(uint8_t percentage)
{
    OCR0A = convertTicksToPercentage(percentage);
    OCR0B = convertTicksToPercentage(percentage);
    PORTB |= (1 << PORTB2);
    PORTB &= ~(1 << PORTB5);
}

void Pwm::turnRight(uint8_t percentage)
{
    OCR0A = convertTicksToPercentage(percentage);
    OCR0B = convertTicksToPercentage(percentage);
    PORTB &= ~(1 << PORTB2);
    PORTB |= (1 << PORTB5);
}

void delay(uint8_t time) {
    for(int i = 0; i<time; i++) {
        _delay_ms(1);
    }
}

void Pwm::turnRightPulse()
{
    turnRight(pulseSpeed);
    delay(pulseDelay);
    turnedOff();
    delay(pulseDelayOff);
}

void Pwm::turnLeftPulse()
{
    turnLeft(pulseSpeed);
    delay(pulseDelay);
    turnedOff();
    delay(pulseDelayOff);
}