#define F_CPU 8000000UL
#include <Led.h>
#include <Uart.h>
#include <util/delay.h>
#include <Debug.h>

Led led = Led(&PORTA, &DDRA, PA0, PA1);
ManagementUSART managementUSART;
    
void testClasseLed()
{
    led.switchGreen();
    _delay_ms(2000);

    led.turnedOff();
    _delay_ms(2000);

    led.switchRed();
    _delay_ms(2000);

    led.turnedOff();
    _delay_ms(2000);
}

void testClasseUart()
{
    managementUSART.initialisation();
    char word[] = "Je suis à bout :D\n";
    managementUSART.transmissionString(word, sizeof(word));
}

void testDebug()
{
    DEBUG_PRINT("justine the goat\n");
}

int main()
{

    // decommenter chaque fonction pour tester
    testClasseLed();
    //testClasseUart();
    //testDebug();

}
