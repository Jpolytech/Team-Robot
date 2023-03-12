#pragma once
#include <avr/io.h>
#include <util/delay.h>

enum class WaveformMode
{
    NORMAL,
    CTC
};

enum class Prescaler
{
    NO_PRESCALING,
    PRESCALE_8,
    PRESCALE_64,
    PRESCALE_256,
    PRESCALE_1024
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
    void clearWaveformMode();
    void clearPrescaler();

    void enableInterrupt();
    void disableInterrupt();

    Prescaler prescaler_;
    WaveformMode mode_;
    volatile bool timerIsRunning_ = false;
};

// ✨✨✨ Nice to have: duration in milliseconds ✨✨✨
