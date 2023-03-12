#include "Timer1.h"

Timer1::Timer1(WaveformMode mode, Prescaler prescaler) : mode_(mode), prescaler_(prescaler)
{
    timerIsRunning_ = false;
}

void Timer1::startTimer(uint16_t duration, WaveformMode newMode, Prescaler newPrescaler)
{
    mode_ = newMode;
    prescaler_ = newPrescaler;
    startTimer(duration);
}

void Timer1::startTimer(uint16_t duration)
{
    cli();
    timerIsRunning_ = true;
    TCNT1 = 0;
    OCR1A = duration;
    setWaveformMode(mode_);
    setPrescaler(prescaler_);
    TCCR1C = 0;
    enableInterrupt();
    sei();
}

void Timer1::setWaveformMode(WaveformMode mode)
{
    switch (mode)
    {
    case WaveformMode::Normal:
        TCCR1A &= ~(1 << WGM10) | (1 << WGM11) | (1 << WGM12) | (1 << WGM13);
        break;

    case WaveformMode::CTC:
        TCCR1A |= (1 << WGM12);
        TCCR1A &= ~(1 << WGM10) | (1 << WGM11) | (1 << WGM13);
        break;
    }
}

void Timer1::setPrescaler(Prescaler prescaler)
{
    switch (prescaler)
    {
    case Prescaler::NoPrescaling:
        TCCR1B |= (1 << CS10);
        TCCR1B &= ~(1 << CS11) | (1 << CS12);
        break;

    case Prescaler::Prescaling8:
        TCCR1B |= (1 << CS11);
        TCCR1B &= ~(1 << CS10) | (1 << CS12);
        break;

    case Prescaler::Prescale64:
        TCCR1B |= (1 << CS10) | (1 << CS11);
        TCCR1B &= ~(1 << CS12);
        break;

    case Prescaler::Prescale256:
        TCCR1B |= (1 << CS12);
        TCCR1B &= ~(1 << CS10) | (1 << CS11);
        break;

    case Prescaler::Prescale1024:
        TCCR1B |= (1 << CS10) | (1 << CS12);
        TCCR1B &= ~(1 << CS11);
        break;
    }
}

void Timer1::stopTimer()
{
    // Is there a way to refactor this? Cus it's redundant (see switch case) - NoPrescaler Case
    TCCR1B |= (1 << CS10);
    TCCR1B &= ~(1 << CS12) | (1 << CS11);
    timerIsRunning_ = false;
}

void Timer1::enableInterrupt()
{
    TIMSK1 = (1 << OCIE1A);
};

void Timer1::disableInterrupt()
{
    TIMSK1 &= ~(1 << OCIE1A);
};