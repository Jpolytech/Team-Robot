#include "States.h"

StatesMachine state;
ButtonD2 buttonInterrupt = ButtonD2(InterruptMode::RISING_EDGE);
ButtonD3 buttonWhite = ButtonD3(InterruptMode::RISING_EDGE);
volatile bool gInterruptButtonPressed;
volatile bool gWhiteButtonPressed;

ISR(INT0_vect)
{
    _delay_ms(30);
    gInterruptButtonPressed = true;
    buttonInterrupt.clearInterruptFlag();
}

ISR(INT1_vect)
{
    _delay_ms(30);
    gWhiteButtonPressed = true;
    buttonWhite.clearInterruptFlag();
}

int main() 
{
    buttonInterrupt.enableInterrupt();
    buttonWhite.enableInterrupt();
    while (true)
    {
    state.switchCase(gInterruptButtonPressed, gWhiteButtonPressed);
    }
    return 0;
}