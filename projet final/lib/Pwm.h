/*
Auteurs:
    Andreea Maria Ghioltan
    Maria Bourouisa
    Jean-Philippe Salis Routhier
    Thibault Delahaie

Description de la classe: Cette classe permet de contrôler les roues du robot à l'aide du PWM.
                          ELle permet entre autres de configurer les registres OCR1A et OCR1B
                          pour le taux du duty cycle.

Identifications des broches (Broches I/O): Les pins 4, 5, 6 et 7 du Port D sont utilisés pour contrôler les moteurs. Les pins 4 et 5 sont reliés aux pins E des moteurs pour le contrôle de la vitesse.
                                           Et les pins 6 et 7 sont reliés aux pins D des moteurs
                                           pour le contrôle de la direction des moteurs.
*/

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>

class Pwm
{
public:
    Pwm();
    void initialisation();
    void movingForward(uint8_t percentage);
    void movingBackward(uint8_t percentage);
    void turnedOff();
    void turnRight(uint8_t percentage);
    void turnLeft(uint8_t percentage);

private:
    uint8_t convertTicksToPercentage(uint8_t percentage);
    uint8_t NUMBER_OF_TICKS = 254;
    uint8_t PERCENTAGE = 100;
    const uint8_t offsetRight = 0;
    const uint8_t offsetLeft = 5;
};
