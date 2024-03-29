//code permettant de recevoir des donnees d'un ordinateur via UART et de l'ecrire dans la memoire externe EEPROM

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../lib/Led.h"
#include "../../lib/Memoire_24.h"
#include "../../lib/Uart.h"

int main() {
    //creation des objets
    Led led = Led(&PORTB, &DDRB, PB0, PB1);
    ManagementUSART usart = ManagementUSART();
    Memoire24CXXX memory = Memoire24CXXX();

    uint8_t data;
    uint16_t address = 0x0000;

    usart.initialisation();
    memory.init();

    while(true) {
        led.switchRed();
        data = usart.receiveData();
        led.switchGreen();
        memory.ecriture(address++, data);
    }
}