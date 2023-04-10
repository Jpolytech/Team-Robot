#include "Position.h"

Position::Position(uint16_t angle) {
    orientation_ = newOrientation(angle);

    currentPositionX_ = 0;
    currentPositionY_ = 0;

    longueur_ = 8;
    largeur_ = 4;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            matrice_[i][j] = 0;
        }
    }
}

//methode pour determiner l'orientation du robot à partir de l'angle
//prend en parametre un angle (en degre)
Orientation Position::newOrientation(uint16_t angle) {
    if(angle + angle_ >= 360) { 
        angle_ += angle - 360;
    }
    else { angle_ += angle; }
    
    if((angle_ >= 0 && angle_ < 23) || (angle_ <= 360 && angle_ >= 338)) {
        angle_ = 0;
        return Orientation::EAST;
    }
    else if(angle_ > 23 && angle_ < 68) {
        angle_ = 45;
        return Orientation::NORTHEAST;
    }
    else if(angle_ > 68 && angle_ < 113) {
        angle_ = 90;
        return Orientation::NORTH;
    }
    else if(angle_ > 113 && angle_ < 158) {
        angle_ = 135;
        return Orientation::NORTHWEST;
    }
    else if(angle_ > 158 && angle_ < 203) {
        angle_ = 180;
        return Orientation::WEST;
    }
    else if(angle_ > 203 && angle_ < 248) {
        angle_ = 225;
        return Orientation::SOUTHWEST;
    }
    else if(angle_ > 248 && angle_ < 293) {
        angle_ = 270;
        return Orientation::SOUTH;
    }
    else if(angle_ > 293 && angle_ < 338) {
        angle_ = 315;
        return Orientation::SOUTHEAST;
    }
};

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
            testCurrentPositionY -= nPost;
            break;
        case Orientation::SOUTH:
            testCurrentPositionY -= nPost;
            break;
        case Orientation::SOUTHWEST:
            testCurrentPositionX -= nPost;
            testCurrentPositionY -= nPost;
            break;
        case Orientation::WEST:
            testCurrentPositionX -= nPost;
            break;
        case Orientation::NORTHWEST:
            testCurrentPositionX -= nPost;
            testCurrentPositionY += nPost;
            break;
        case Orientation::NORTH:
            testCurrentPositionY += nPost;
            break;
        case Orientation::NORTHEAST:
            testCurrentPositionX += nPost;
            testCurrentPositionY += nPost;
    }

    //verification si l'objet est sur la table
    if(testCurrentPositionX < 0 || testCurrentPositionX >= longueur_ || testCurrentPositionY < 0 || testCurrentPositionY >= largeur_) {
        return false; // dans ce cas, l'objet detecté est en dehors de la table
    }
    orientation_ = testOrientation;
    currentPositionX_ = testCurrentPositionX;
    currentPositionY_ = testCurrentPositionY;
    matrice_[currentPositionX_][currentPositionY_] = 1;
    return true;
};