#include "sound.h"

Sound::Sound()
{
	DDRD &= ~(1<<PD6);
}

void Sound::init() {
	TCCR2A = 0x00;
	OCR2B = 127;
}

void Sound::playNote(uint8_t index)
{
	DDRD |= (1 << PD7);
	TCCR2A |= (1 << COM2A0)|(1<<WGM21);
	if(index < 60) {
		TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // prescaler 1024
		OCR2A = listOCR2A_1024[index-45]*2; //faibles frequences
	}
	else {
		TCCR2B |= (1 << CS22) | (1 << CS21); //prescaler 256
		OCR2A = listOCR2A[index-45]*2; // hautes frequences
	}
}

void Sound::stopNote()
{
	TCCR2A = 0x00;
	DDRD &= ~(1 << PD7);
}