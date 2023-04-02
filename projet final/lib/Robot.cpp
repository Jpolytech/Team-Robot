#include <Robot.h>

Robot::Robot() : sensor_(Sensor()), motor_(Pwm()) {

}

void Robot::initialisation() {
    motor_.initialisation();
}

void Robot::searchPost() {

}

void Robot::moveToPost() {
    distanceObj_ = sensor_.getDistanceInCm();
    while(distanceObj_ <= 27 && distanceObj_ >= 10) {
        distanceObj_ = sensor_.getDistanceInCm();
        motor_.movingForward(50);
        if(distanceObj_ <= 10) {
            motor_.turnedOff();
            break;
        }
    }
    
    //en cas de perte de l'objet (deviation du robot), le robot le recherche
    /*if(sensor_.getDistanceInCm() >= 27) {
        //recherche du plot
        motor_.turnLeft(100);
        _delay_ms(10);
        motor_.turnedOff();
        if(sensor_.getDistanceInCm() >= 27) {
            //recherche du plot de l'autre coté
            motor_.turnRight(100);
            _delay_ms(20);
            motor_.turnedOff();
        }
    }*/
}