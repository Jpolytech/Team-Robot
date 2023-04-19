#include "Position.h"

Position::Position(uint16_t angle) {
    orientation_ = newOrientation(angle);

    currentPositionX_ = 0;
    currentPositionY_ = 3;

    longueur_ = 8;
    largeur_ = 4;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            matrice_[i][j] = 0;
        }
    }
    uart.initialisation();
}

//methode pour determiner l'orientation du robot à partir de l'angle
//prend en parametre un angle (en degre)
Orientation Position::newOrientation(uint16_t angle) {

    uint16_t newAngle = (angle_ + angle)%360;
    angle_ = newAngle;
    float jump = 45/2;

    if(newAngle >= 0 - jump && newAngle <= 0 + jump)
        return Orientation::EAST;
    else if(newAngle > 45 - jump && newAngle <= 45 + jump)
        return Orientation::NORTHEAST;
    else if(newAngle > 90 - jump && newAngle <= 90 + jump)
        return Orientation::NORTH;
    else if(newAngle > 135 - jump && newAngle <= 135 + jump)
        return Orientation::NORTHWEST;
    else if(newAngle > 180 - jump && newAngle <= 180 + jump)
        return Orientation::WEST;
    else if(newAngle > 225 - jump && newAngle <= 225 + jump)
        return Orientation::SOUTHWEST;
    else if(newAngle > 270 - jump && newAngle <= 270 + jump)
        return Orientation::SOUTH;
    else
        return Orientation::SOUTHEAST;
}


uint8_t Position::getCurrentPositionX() {
    return currentPositionX_;
};

uint8_t Position::getCurrentPositionY() {
    return currentPositionY_;
};

uint8_t Position::getAngle() {
    return angle_;
}

//met à jour la position du robot
//prend en parametre nPost: le nombre d'unité entre le robot et le plot (2 max, 15.6 >= 1 unité >= 11 pouces)
// angle: angle de rotation du robot lors du deplacement
bool Position::newPosition(uint8_t nPost, uint16_t angle) {
    uint8_t  testCurrentPositionX = currentPositionX_;
    uint8_t  testCurrentPositionY = currentPositionY_;

    Orientation testOrientation;
    testOrientation = newOrientation(angle);

    switch(testOrientation) {
        case Orientation::EAST:
            testCurrentPositionX += nPost;
            break;
        case Orientation::SOUTHEAST:
            testCurrentPositionX += nPost;
            testCurrentPositionY += nPost;
            break;
        case Orientation::SOUTH:
            testCurrentPositionY += nPost;
            break;
        case Orientation::SOUTHWEST:
            testCurrentPositionX -= nPost;
            testCurrentPositionY += nPost;
            break;
        case Orientation::WEST:
            testCurrentPositionX -= nPost;
            break;
        case Orientation::NORTHWEST:
            testCurrentPositionX -= nPost;
            testCurrentPositionY -= nPost;
            break;
        case Orientation::NORTH:
            testCurrentPositionY -= nPost;
            break;
        case Orientation::NORTHEAST:
            testCurrentPositionX += nPost;
            testCurrentPositionY -= nPost;
    }



    orientation_ = testOrientation;
    currentPositionX_ = testCurrentPositionX;
    currentPositionY_ = testCurrentPositionY;

    uart.transmitData((uint8_t)testOrientation);
    uart.transmitData((uint8_t)currentPositionX_);
    uart.transmitData((uint8_t)currentPositionY_);

    matrice_[currentPositionX_][currentPositionY_] = 1;
    return true;
};

void Position::setOrientation(uint16_t angle) {
    angle_ = 0;
    orientation_ = newOrientation(angle);
}
