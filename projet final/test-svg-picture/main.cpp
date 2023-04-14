#include "SvgPicture.h"
#include "Memoire_24.h"
#include "Uart.h"

int main(){
    SvgPicture svg;
    svg.transfer();
    // Memoire24CXXX memoire;
    // ManagementUSART uart;
    // uart.initialisation();
    // uint8_t data[] = {1,0, 3,0, 1,1, 2,1, 4,1, 1,2, 6,2, 3,3, 0xff};
    // int size = sizeof(data);
    // uint8_t byte;

    // for (int i =0; i < size; i++)
    // {
    //     memoire.ecriture(i, data[i]);
    //     _delay_ms(5);
    // }

    // for (int i =0; i < size; i++)
    // {
    //     memoire.lecture(i, &byte);
    //     _delay_ms(5);
    //     uart.transmitData(byte);
    // }
 }