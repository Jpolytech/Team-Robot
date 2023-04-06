#include "Position.h"

Position::Position(uint8_t angle) {
    orientation_ = newOrientation(angle);

    currentPosition_[0] = 0;
    currentPosition_[1] = 0;

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
Orientation Position::newOrientation(uint8_t angle) {
    if(angle + angle_ >= 360) { 
        angle_ += angle - 360;
    }
    else { angle_ = angle; }
    
    if((angle_ > 0 && angle_ < 23) || (angle_ < 360 && angle_ >= 338)) {
        return Orientation::EAST;
    }
    else if(angle_ > 23 && angle_ < 68) {
        return Orientation::NORTHEAST;
    }
    else if(angle_ > 68 && angle_ < 113) {
        return Orientation::NORTH;
    }
    else if(angle_ > 113 && angle_ < 158) {
        return Orientation::NORTHWEST;
    }
    else if(angle_ > 158 && angle_ < 203) {
        return Orientation::WEST;
    }
    else if(angle_ > 203 && angle_ < 248) {
        return Orientation::SOUTHWEST;
    }
    else if(angle_ > 248 && angle_ < 293) {
        return Orientation::SOUTH;
    }
    else if(angle_ > 293 && angle_ < 338) {
        return Orientation::SOUTHEAST;
    }
};

uint8_t Position::getCurrentPositionX() {
    return currentPosition_[0];
};

uint8_t Position::getCurrentPositionY() {
    return currentPosition_[1];
};

//met à jour la position du robot
//prend en parametre nPost: le nombre d'unité entre le robot et le plot (2 max, 15.6 >= 1 unité >= 11 pouces)
// angle: angle de rotation du robot lors du deplacement
bool Position::newPosition(uint8_t nPost, uint8_t angle) {
    uint8_t testCurrentPosition[2];
    testCurrentPosition[0] = currentPosition_[0];
    testCurrentPosition[1] = currentPosition_[1];

    Orientation testOrientation;
    testOrientation = newOrientation(angle);

    switch(testOrientation) {
        case Orientation::EAST:
            testCurrentPosition[0] += nPost;
            break;
        case Orientation::SOUTHEAST:
            testCurrentPosition[0] += nPost;
            testCurrentPosition[1] -= nPost;
            break;
        case Orientation::SOUTH:
            testCurrentPosition[1] -= nPost;
            break;
        case Orientation::SOUTHWEST:
            testCurrentPosition[0] -= nPost;
            testCurrentPosition[1] -= nPost;
            break;
        case Orientation::WEST:
            testCurrentPosition[0] -= nPost;
            break;
        case Orientation::NORTHWEST:
            testCurrentPosition[0] -= nPost;
            testCurrentPosition[1] += nPost;
            break;
        case Orientation::NORTH:
            testCurrentPosition[1] += nPost;
            break;
        case Orientation::NORTHEAST:
            testCurrentPosition[0] += nPost;
            testCurrentPosition[1] += nPost;
    }

    //verification si l'objet est sur la table
    if(testCurrentPosition[0] < 0 || testCurrentPosition[0] > longueur_ || testCurrentPosition[1] < 0 || testCurrentPosition[1] > largeur_) {
        return false; // dans ce cas, l'objet detecté est en dehors de la table
    }
    orientation_ = testOrientation;
    currentPosition_[0] = testCurrentPosition[0];
    currentPosition_[1] = testCurrentPosition[1];
    matrice_[currentPosition_[0]][currentPosition_[1]] = 1;
    return true;
};