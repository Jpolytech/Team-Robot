#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Uart.h"

enum class Orientation {
    NORTH =0,
    NORTHEAST =1,
    EAST =2,
    SOUTHEAST =3,
    SOUTH =4,
    SOUTHWEST =5,
    WEST =6,
    NORTHWEST =7
};

class Position {
public:
    Position(uint16_t angle);
    bool newPosition(uint8_t nPost, uint16_t angle);
    uint8_t getCurrentPositionX();
    uint8_t getCurrentPositionY();
    uint8_t getAngle();
    void setOrientation(uint16_t angle);

private:
    Orientation newOrientation(uint16_t angle);
    Orientation orientation_;
    ManagementUSART uart;
    uint16_t angle_ = 0;
    uint8_t matrice_[4][8];
	uint8_t longueur_; //nb colonnes
	uint8_t largeur_; //nb lignes
	uint8_t currentPositionX_;
    uint8_t currentPositionY_;
};
