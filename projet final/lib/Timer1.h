/*
Auteurs:
    Andreea Maria Ghioltan
    Maria Bourouisa
    Jean-Philippe Salis Routhier
    Thibault Delahaie

Description de la classe: Cette classe permet de configurer le Timer 1 de l'ATMEGA328 en donnant le choix du
                          de la durée qu'il doit compter, du prescaler ainsi que du mode de Waveform.

Identifications des broches (Broches I/O): Ne s'applique pas.
*/

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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

    WaveformMode mode_;
    Prescaler prescaler_;
    volatile bool timerIsRunning_ = false;
};
