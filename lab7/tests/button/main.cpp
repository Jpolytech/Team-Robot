#include <ButtonD2.h>

ButtonD2 button = ButtonD2();

ISR(INT0_vect)
{
    PORTA ^= (1 << PA0); // Toggle LED on PA0
    button.clearInterruptFlag();
}

int main()
{
    DDRA = 0xFF;

    button.enableInterrupt();

    _delay_ms(5000);

    button = ButtonD2(InterruptMode::FALLING_EDGE);
    button.enableInterrupt();

    _delay_ms(5000);
}