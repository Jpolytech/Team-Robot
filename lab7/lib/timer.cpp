#include <timer.h>

/*************************/
//constructeur par defaut
//aucun argument et ne renvoie rien
/*************************/
Timer::timer() {
    timerIsRunning_ = false;
}

/*************************/
//methode qui demarre la minuterie et autorise les interruptions
//prend la duree en argument
/*************************/
void Timer::startTimer(uint6_t duration) {
    timerIsRunning_ = true;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    //mode CTC, TCNT1 et clear on compare match
    TCNT1 = 0;
    OCR1A = duration;
    TCCR1A = (1 << WGM12);
    TCCR1B = (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

/*************************/
//methode qui arrete la minuterie
//aucun argument et ne renvoie rien
/*************************/
void Timer::stopTimer() {
    TIMSK1 &= ~(1 << OCIE1A);
}

/*************************/
//methode qui renvoie le dernier etat de la minuterie
//renvoie un booleen: vrai si la minuterie est demarree
/*************************/
bool Timer::IsTimerRunning() {
    return timerIsRunning_;
}

void Timer::setTimerRunning(bool value) {
    timerIsRunning_ = value;
}