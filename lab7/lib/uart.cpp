#ifndef F_CPU
#define F_CPU 8000000UL
#include "uart.h"
#include "memoire_24.h"

//initialisation de l'USART
void ManagementUSART::initialisationUSART(void) {
// 2400 bauds. Nous vous donnons la valeur des deux
// premiers registres pour vous éviter des complications.
UBRR0H = 0;
UBRR0L = 0xCF;
// permettre la réception et la transmission cpar le UART0
//UCSR0A -> enable des flag mais pas besoin d'y toucher
UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //permet transmission et réception
UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //character size = 8 bits
// Format des trames: 8 bits, 1 stop bits, sans parité
//rien à faire car les bits pour avoir les modes 8NI sont = 0 par défaut
}

// Du USART vers le PC
void ManagementUSART::transmissionUSART (uint8_t data) {
    while ( !( UCSR0A & (1<<UDRE0)) ) {}
    UDR0 = data;
}
//UCSR0A pour le receive flag
//UDRE0 pour Data Register Empty: s'il y a des donnees recues

//transmission d'un string vers le PC -> Voir avec un chargé
void ManagementUSART::transmissionStringUSART(uint8_t length) {
    uint8_t i, j;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            transmissionUART (word[j]);
        }
    }
}