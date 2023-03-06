#ifndef F_CPU
# define F_CPU 8000000UL
#include "uart.h"

//initialisation de l'USART
void GestionUSART::initialisationUSART() {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0; //initialisation des Receive complete/Transmit complete flags
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); // permet la reception et transmission
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (3<<UCSZ00);
    //UCSZ00: trame de 8 bits (3<<UCSZn00: 100)
    //UPM01:0 : parité (Usart parity mode)
    //USBS0 : stop bits, deja a 1stop bit
}

// Du USART vers le PC
void GestionUSART::transmissionUSART ( uint8_t donnee ) {
    while ( !( UCSR0A & (1<<UDRE0)) ){}
    UDR0 = donnee;
}
//UCSR0A pour le receive flag
//UDRE0 pour Data Register Empty: s'il y a des donnees recues

//transmission d'un string vers le PC
void GestionUSART::transmissionStringUSART( uint8_t taille ) {
    for (int i = 0; i < taille; i++ ) {
        for (int j=0; j < taille; j++ ) {
            transmissionUART (mots[j]);
        }
    }
}