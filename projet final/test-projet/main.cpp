#include "States.h"

static constexpr uint8_t DEBOUNCE_DELAY = 30;

StatesMachine state;

ButtonD2 buttonInterrupt = ButtonD2(InterruptMode::RISING_EDGE);
ButtonD3 buttonWhite = ButtonD3(InterruptMode::RISING_EDGE);
// volatile bool gTransmissionStarted = false;

ISR(INT0_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    state.isInterruptButtonPressed = true;
    buttonInterrupt.clearInterruptFlag();
}

ISR(INT1_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    state.isWhiteButtonPressed = true;
    buttonWhite.clearInterruptFlag();
}

ISR(TIMER1_COMPA_vect)
{

}

void initialisation() {
    buttonInterrupt.enableInterrupt();
    buttonWhite.enableInterrupt();
}

int main() 
{
    initialisation();

    while (true)
    {
        state.updateState();
    }

    return 0;
}