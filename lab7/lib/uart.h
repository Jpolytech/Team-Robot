#include <avr/io.h>
#include <util/twi.h>

// Classe pour la gestion de la memoire et la transmission de l'UART

class GestionUSART {
    public:
    GestionUSART() = default;
    void initialisationUART();
    void transmissionUSART ( uint8_t donnee );
    void transmissionStringUSART( uint8_t taille );
}