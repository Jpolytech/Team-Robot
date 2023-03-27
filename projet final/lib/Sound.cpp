#include "Sound.h"

Sound::Sound()
{
    DDRD |= (1 << PD7);
}

void Sound::notePWM(uint8_t index)
{
    TCCR2A = 0;
    TCCR2A |= (1 << COM2A0) | (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21);
    OCR2A = index;
}

void Sound::playNote(uint8_t index)
{
    int freq;
    double puissance = (index - 69) / 12;
    freq = 440 * pow(2, puissance);
    uint8_t out;
    out = (FCPU / (freq * 2 * PRESCALER)) - 1;
    notePWM(out);
}

void Sound::stopNote()
{
    OCR2A = 0;
}
