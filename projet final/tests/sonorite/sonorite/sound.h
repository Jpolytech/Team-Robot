#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Sound
{
public:
    Sound();
	void init();
    void playNote(uint8_t index);
    void stopNote();
};

//prescaler de 256
const uint8_t listOCR2A[] = {
	141, 133, 125, 118, 112, 105, 99, 94,
	88, 83, 79, 74, 70, 66, 62, 59, 55,
	52, 49, 46, 44, 41, 39, 37, 35, 33,
	31, 29, 27, 26, 24, 23, 21, 20, 19,
	18,	17
}; 

//prescaler de 1024
const uint8_t listOCR2A_1024[] = {
	35, 33, 31, 29, 27,
	26, 24, 23, 21, 20,
	19, 18, 17, 16, 15,
	14, 13, 12, 12, 11,
	10, 10, 9, 8, 8, 7, 
	7, 6, 6, 6, 5, 5, 5, 
	4, 4, 4, 3
};