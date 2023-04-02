#include <Robot.h>

Robot::Robot() : sensor_(Sensor()), motor_(Pwm()) {

}

void Robot::initialisation() {
    motor_.initialisation();
}

void Robot::searchPost() {
    motor_.turnLeft(45);
    distanceObj_ = sensor_.getDistance();
    while(distanceObj_ <= 57) { distanceObj_ = sensor_.getDistance(); }
    motor_.turnedOff();
    moveToPost();
}

//Pour utiliser cette fonction, on suppose que le robot est dejà orienté vers le plot
void Robot::moveToPost() {
    distanceObj_ = sensor_.getDistance();
    while(distanceObj_ <= 140 && distanceObj_ >= 57) { // distance comprise entre 27 et 10cm
        distanceObj_ = sensor_.getDistance();
        motor_.movingForward(50);
        if(distanceObj_ >= 140) { // si distance <= 10cm
            motor_.turnedOff();
            break;
        }
    }
    motor_.turnedOff();
    if(distanceObj_ <= 57) { // si distance >= 27cm
        _delay_ms(1000);
        replacePost();
    }
}

//en cas de perte du plot(deviation du robot), le robot le recherche
void Robot::replacePost() {
    while(distanceObj_ <= 57) { // si c'est >= 27cm
        motor_.turnLeft(50);
        _delay_ms(200);
        motor_.turnedOff();
        _delay_ms(200);
        distanceObj_ = sensor_.getDistance();
        if(distanceObj_ <= 57) { // si distance >= 27cm
            //recherche du plot de l'autre coté
            motor_.turnRight(50);
            _delay_ms(200);
            motor_.turnedOff();
            _delay_ms(200);
            sensor_.getDistance();
        }
        else {break;}
    }
    motor_.turnedOff();
    moveToPost();
}