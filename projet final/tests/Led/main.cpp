#include <Led.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
    Led led = Led(&PORTB, &DDRB, PB0, PB1);

    led.switchGreen();
    _delay_ms(2000);

    led.turnedOff();
    _delay_ms(2000);

    led.switchRed();
    _delay_ms(2000);

    led.turnedOff();
    _delay_ms(2000);

    while(true)
    {
        led.switchAmber();
    }
}
