#include <Robot.h>

Robot::Robot() : position_(Position(0)), sensor_(Sensor()), motor_(Pwm()), memory_(Memoire24CXXX()){}

void Robot::initialisation() {
    motor_.initialisation();
    memory_.init();
    rotateTime_ = 0;
    memoryAdress_ = 0x0000;
}

void Robot::setOrientation(uint16_t angle)
{
    position_.setOrientation(angle);
}

bool Robot::isEmptyTable() {
    return isEmptyTable_;
}

void Robot::searchPost() {
    nDistancePost_ = sensor_.getSpot();
    while(nDistancePost_ == 0 && rotateTime_ <= 50) {
        motor_.turnLeftPulse();
        nDistancePost_ = sensor_.getSpot();
        rotateTime_ += 1; //*0.4 secondes
    }
    motor_.turnedOff();
    _delay_ms(400);
    uint16_t angle = round(rotateTime_*rotateConst_);
    angle += rotateTime_/2;
    if(position_.newPosition(nDistancePost_, angle) && nDistancePost_ >= 0) {
        memory_.ecriture(memoryAdress_++, position_.getCurrentPositionX());
        memory_.ecriture(memoryAdress_++, position_.getCurrentPositionY());
        moveToPost();
    }
    else if(nDistancePost_ >= 0){
        motor_.turnLeftPulse();
        searchPost();
    }
    else {
        isEmptyTable_ = true;
        memory_.ecriture(memoryAdress_++, 0xff);
    }
}

//Pour utiliser cette fonction, on suppose que le robot est dejà orienté vers le plot
void Robot::moveToPost() {
    rotateTime_ = 0;
    while(sensor_.isSpotFar()) {
        motor_.movingForward(60);
        if(!sensor_.isSpotFar()) {
            motor_.turnedOff();
            break;
        }
        if(sensor_.isSpotLost()) {
            _delay_ms(400);
            replacePost();
        }
    }
    motor_.turnedOff();
    position_.setOrientation(90); //le robot est orienté vers le haut apres avoir trouvé un poteau
}

void delay_100ms(uint8_t var) {
    for(int i = 0; i<var; i++) {
        _delay_ms(100);
    }
}

//en cas de perte du plot(deviation du robot), le robot le recherche
void Robot::replacePost() {
    for(int i = 0; i < 5; i++) {
        if(!sensor_.isSpotLost()) {
            break;
        }
        motor_.turnRightPulse();
    }
    for(int i = 0; i < 10; i++) {
        if(!sensor_.isSpotLost()) {
            break;
        }
        motor_.turnLeftPulse();
    }
    motor_.turnedOff();
    moveToPost();
}
