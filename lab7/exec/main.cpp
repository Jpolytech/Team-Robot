#include <avr/io.h>

ISR(INT0_vect)
{
    // Do something
}

int main()
{

    ButtonD2 button = ButtonD2();

    button.enableInterrupt();
}