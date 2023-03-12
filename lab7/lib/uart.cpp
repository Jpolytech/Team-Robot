#ifndef F_CPU
#define F_CPU 8000000UL
#include "uart.h"
#include "memoire_24.h"

void ManagementUSART::initialisation(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // permet transmission et réception
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // character size = 8 bits
}

void ManagementUSART::transmission(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = data;
}

void ManagementUSART::transmissionString(char word[], uint8_t length)
{
    for (int i = 0; i < length; i++)
    {
        transmissionUART(word[i]);
    }
}