#include <Robot.h>

Robot::Robot() : sensor_(Sensor()), motor_(Pwm()), usart_(ManagementUSART()), position_(Position(0)) {

}

void Robot::initialisation() {
    motor_.initialisation();
    usart_.initialisation();
    rotateTime_ = 0;
}

void Robot::searchPost() {
    rotateTime_ = 0;
    nDistancePost_ = sensor_.getSpot();
    while(nDistancePost_ == 0) {
        motor_.turnLeftPulse();
        nDistancePost_ = sensor_.getSpot();
        rotateTime_ += 1; //*0.4 secondes
    }
    motor_.turnedOff();
    _delay_ms(400);
    uint8_t angle = round(rotateTime_*rotateConst_);
    angle += rotateTime_/2;
    if(position_.newPosition(nDistancePost_, angle)) {
        moveToPost();
    }
    else {
        motor_.turnLeftPulse();
        searchPost();
    }
    //moveToPost();
}

//Pour utiliser cette fonction, on suppose que le robot est dejà orienté vers le plot
void Robot::moveToPost() {
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
    while(true) {
        usart_.transmitData(nDistancePost_);
        //usart_.transmitData(angle);
        usart_.transmitData(position_.getCurrentPositionX());
        usart_.transmitData(position_.getCurrentPositionY());
        _delay_ms(5000);
        }
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