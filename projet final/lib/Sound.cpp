#include "Sound.h"

Sound::Sound()
{
	DDRD &= ~(1<<PD6);
}

void Sound::init() {
	TCCR2A |= 0x00;
    TCCR2B |= (1 << CS22) | (1 << CS21);
	//TIMSK2 |= (1<<OCIE2A);
	OCR2B = 127;
}

void Sound::playNote(uint8_t index)
{
	DDRD |= (1 << PD7);
	TCCR2A |= (1 << COM2A0)|(1<<WGM21);
	OCR2A = listOCR2A[index-45]*2;
}

void Sound::stopNote()
{
	TCCR2A = 0x00;
	DDRD &= ~(1 << PD7);
}