#include <Led.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
    Led led = Led(&DDRA, &PORTA, PA0, PA1);

    led.switchGreen();
    _delay_ms(5000);

    led.switchRed();
    _delay_ms(5000);
}
