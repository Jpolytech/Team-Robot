#include <Robot.h>

Robot::Robot() : position_(Position(0)), sensor_(Sensor()), motor_(Pwm()), memory_(Memoire24CXXX()) {}

void Robot::initialisation() {
    motor_.initialisation();
    memory_.init();
    rotateCount_ = 0;
    memoryAdress_ = 0x0000;
    // sound_.init();
}

void Robot::setOrientation(uint16_t angle)
{
    position_.setOrientation(angle);
}

bool Robot::getEmptyTable() 
{
    return isEmptyTable_;
}

void Robot::searchPost() 
{
    uint8_t rotateTime_ = 0;
    nDistancePost_ = sensor_.getSpot();

    while(nDistancePost_ == Sensor::PolePosition::NONE && rotateCount_ <= FULL_CIRCLE_COUNT) 
    {
        motor_.turnLeftPulse();
        nDistancePost_ = sensor_.getSpot();
        rotateTime_++; //*0.4 secondes
        rotateCount_++;
    }

    motor_.turnedOff();
    _delay_ms(DELAY_MOTOR);
    uint16_t angle = round((float)rotateTime_ * ROTATE_CONST);

    if(rotateCount_ <= FULL_CIRCLE_COUNT && nDistancePost_ != Sensor::PolePosition::NONE) 
    {
        position_.newPosition((uint8_t)nDistancePost_, angle);
        rotateCount_ = 0;
        memory_.ecriture(memoryAdress_++, position_.getCurrentPositionX());
        memory_.ecriture(memoryAdress_++, position_.getCurrentPositionY());
        moveToPost();
        // playSharpNotes();
    }
    else 
    {
        rotateCount_ = 0;
        isEmptyTable_ = true;
        memory_.ecriture(memoryAdress_++, 0xff);
        // sound_.playNote(...); 
    }
}

//Pour utiliser cette fonction, on suppose que le robot est dejà orienté vers le plot
void Robot::moveToPost() 
{
    motor_.movingForward(ROBOT_SPEED, true);
    while(!sensor_.isSpotEncountered()) 
    {
        

        if(sensor_.isSpotEncountered()) 
        {
            break;
        }

        if(sensor_.isSpotLost()) 
        {
            _delay_ms(DELAY_MOTOR);
            replacePost();
            motor_.movingForward(ROBOT_SPEED, true);
        }
    }
    motor_.turnedOff();
    position_.setOrientation(TOP_ORIENTATION_ANGLE); //le robot est orienté vers le haut apres avoir trouvé un poteau
}

//en cas de perte du plot(deviation du robot), le robot le recherche
void Robot::replacePost() 
{
    
    for(int i = 0; i < 10; i++) {
        if(!sensor_.isSpotLost()) 
        {
            motor_.turnLeftPulse();
            motor_.turnLeftPulse();
            motor_.turnLeftPulse();
            break;
        }
        motor_.turnLeftPulse();
    }
    for(int i = 0; i < 20; i++) 
    {
        if(!sensor_.isSpotLost()) 
        {
            motor_.turnRightPulse();
            break;
        }
        motor_.turnRightPulse();
    }
    motor_.turnedOff();
    moveToPost();
}

// void Robot::playHighNotes() {
//     sound_.playNote(HIGH_NOTE1);
//     _delay_ms(NOTE_DELAY);
//     sound_.stopNote();
//     sound_.playNote(HIGH_NOTE2);
//     _delay_ms(NOTE_DELAY);
//     sound_.stopNote();
//     sound_.playNote(HIGH_NOTE3);
//     _delay_ms(NOTE_DELAY);
//     sound_.stopNote();
// }
