#pragma once
#include <avr/io.h>
#include <util/delay.h>

enum class WaveformMode
{
    Normal,
    CTC
};

enum class Prescaler
{
    NoPrescaling,
    Prescale8,
    Prescale64,
    Prescale256,
    Prescale1024
};

class Timer1
{
public:
    Timer1(WaveformMode mode, Prescaler prescaler);

    void startTimer(uint16_t duration);
    void startTimer(uint16_t duration, WaveformMode newMode, Prescaler newPrescaler);
    void stopTimer();

private:
    void setWaveformMode(WaveformMode mode);
    void setPrescaler(Prescaler prescaler);

    void enableInterrupt();
    void disableInterrupt();

    Prescaler prescaler_;
    WaveformMode mode_;
    volatile bool timerIsRunning_ = false;
}

// Nice to have: duration in milliseconds