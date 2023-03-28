#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <sound.h>

int main() {
    Sound speaker = Sound();
    speaker.init();
    _delay_ms(3000);
    speaker.playNote(80);
    _delay_ms(2000);
    speaker.stopNote();
    speaker.playNote(58);
    _delay_ms(1000);
    speaker.stopNote();
    return 0;
}