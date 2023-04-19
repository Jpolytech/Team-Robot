#include "Memoire_24.h"
#include "Uart.h"

int main(){
    Memoire24CXXX memory;
    ManagementUSART uart;
    usart.initialisation();
    uint8_t adresse = 0;
    uint8_t data = 0;

    for (int i = 0; i < 17, i++)
    {
        n = memory.lecture(adresse++, data);
        uart.transmitData(n);
    }
}