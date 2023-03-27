#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

class Sound
{
public:
    Sound();
    void playNote(uint8_t index);
    void notePWM(uint8_t index);
    void stopNote();

private:
    const uint8_t FCPU = 8000000;
    const uint8_t PRESCALER = 64;
};
