#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>

enum class Orientation {
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
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
    uint16_t angle_ = 0;
    uint8_t matrice_[4][8];
	uint8_t longueur_; //nb colonnes
	uint8_t largeur_; //nb lignes
	uint8_t currentPositionX_;
    uint8_t currentPositionY_;
};