#include <Button.h>
#include <Led.h>

ButtonD2 button = ButtonD2(InterruptMode::RISING_EDGE);
ButtonD3 button2 = ButtonD3(InterruptMode::RISING_EDGE);
Led led = Led(&PORTB, &DDRB, PB0, PB1);

ISR(INT0_vect)
{
    led.switchAmber(); 
    button.clearInterruptFlag();
}

ISR(INT1_vect)
{
    led.switchGreen();
    button2.clearInterruptFlag();
}

int main()
{
    button.enableInterrupt();
    button2.enableInterrupt();
    while (true);
}