#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "Pwm.h"

using namespace std;

#define DDR_IN 0x00;
#define DDR_OUT 0xff;
#define DEBOUNCE_TIME 20;

Pwm r = Pwm();

int main()
{
    r.initialisation();
    r.movingForward(100);
    _delay_ms(2000);
    r.movingBackward(100);
    _delay_ms(2000);
    r.turnRight(100);
    _delay_ms(2000);
    r.turnLeft(100);
    _delay_ms(2000);
    r.turnedOff();
    return 0;
}

