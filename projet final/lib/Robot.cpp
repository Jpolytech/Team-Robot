#include <Robot.h>

Robot::Robot() : sensor_(Sensor()), motor_(Pwm()), usart_(ManagementUSART()) {

}

void Robot::initialisation() {
    motor_.initialisation();
    usart_.initialisation();
    rotateTime_ = 0;
}

void Robot::searchPost() {
    nDistancePost_ = sensor_.getSpot();
    usart_.transmitData(nDistancePost_);
    if(nDistancePost_ == 0) {
        motor_.turnLeft(50);
    }
    while(nDistancePost_ == 0) {
        nDistancePost_ = sensor_.getSpot();
        _delay_ms(10);
        rotateTime_ += 10;
    }
    motor_.turnedOff();
    _delay_ms(400);
    moveToPost();
}

//si le robot tournait trop vite lors de la recherche du poteau, cette methode permet de faire une rotation dans l'autre sens pour retrouver le poteau
void Robot::backToSpot() {
    while(sensor_.isSpotLost()){
        motor_.turnRight(70);
        _delay_ms(300);
        motor_.turnedOff();
        _delay_ms(400);
    }
    moveToPost();
}

//Pour utiliser cette fonction, on suppose que le robot est dejà orienté vers le plot
void Robot::moveToPost() {
    while(sensor_.isSpotFar()) {
        motor_.movingForward(70);
        if(!sensor_.isSpotFar()) {
            motor_.turnedOff();
            break;
        }
        if(sensor_.isSpotLost()) {
            replacePost();
        }
    }
    motor_.turnedOff();
}

void delay_100ms(uint8_t var) {
    for(int i = 0; i<var; i++) {
        _delay_ms(100);
    }
}

//en cas de perte du plot(deviation du robot), le robot le recherche
void Robot::replacePost() {
    int delay_var = 3;
    while(sensor_.isSpotLost()) {
        usart_.transmitData(sensor_.getDistance());
        motor_.turnLeft(50);
        delay_100ms(delay_var);
        motor_.turnedOff();
        _delay_ms(200);
        if(sensor_.isSpotLost()) {
            //recherche du plot de l'autre coté
            motor_.turnRight(50);
            delay_100ms(delay_var);
            motor_.turnedOff();
            _delay_ms(200);
            sensor_.getDistance();
        }
        else {break;}
        delay_var++;
    }
    motor_.turnedOff();
    moveToPost();
}