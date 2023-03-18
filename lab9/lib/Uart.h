/*
Auteurs:
    Andreea Maria Ghioltan
    Maria Bourouisa
    Jean-Philippe Salis Routhier
    Thibault Delahaie

Description de la classe: Cette classe permet de configurer la communication RS232 pour transmettre des
                          données de l'ATMEGA324 vers un PC en ayant le cavalier DbgEN sur la carte mère.


Identifications des broches (Broches I/O): Ne s'applique pas.
*/

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/twi.h>

class ManagementUSART
{
public:
    ManagementUSART() = default;
    void initialisation();
    void transmission(uint8_t data);
    void transmissionString(char word[], uint8_t length);
    uint8_t receiveData();
};