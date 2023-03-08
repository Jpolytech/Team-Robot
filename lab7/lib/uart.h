#include <avr/io.h>
#include <util/twi.h>

// Classe pour la gestion de la memoire et la transmission de l'UART
class ManagementUSART {
    public:
        ManagementUSART() = default;
        void initialisationUSART();
        void transmissionUSART (uint8_t data);
        void transmissionStringUSART(uint8_t length);
}