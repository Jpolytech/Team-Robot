#include "States.h"

StatesMachine state;
ButtonD2 buttonInterrupt = ButtonD2(InterruptMode::RISING_EDGE);
ButtonD3 buttonWhite = ButtonD3(InterruptMode::RISING_EDGE);
volatile bool gInterruptButtonPressed = false;
volatile bool gInterruptWhiteButtonPressed = false;
// Led ledTest = Led(&PORTB, &DDRB, PB0, PB1);

ISR(INT0_vect)
{
    gInterruptButtonPressed = true;
    buttonInterrupt.clearInterruptFlag();
}

ISR(INT1_vect)
{
    gInterruptWhiteButtonPressed = true;
    buttonWhite.clearInterruptFlag();
}

int main() 
{
    while (true){
        buttonInterrupt.enableInterrupt();
        buttonWhite.enableInterrupt();
        state.switchCase(gInterruptButtonPressed, gInterruptWhiteButtonPressed);
    }
    return 0;
}