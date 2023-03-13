#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <pwm.h>

using namespace std;

#define DDR_IN 0x00;
#define DDR_OUT 0xff;
#define DEBOUNCE_TIME 20;

int main()
{
    Pwm r = Pwm();
    r.initialisation();
    r.movingForward();
    _delay_ms(2000);
    r.movingBackward();
    _delay_ms(2000);
    r.turnRight();
    _delay_ms(2000);
    r.turnLeft();
    _delay_ms(2000);
    r.turnedOff();
    return 0;
}

