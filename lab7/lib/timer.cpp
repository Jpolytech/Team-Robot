#include <timer.h>

/*************************/
//constructeur par defaut
//aucun argument et ne renvoie rien
/*************************/
Timer::Timer() {
    timerIsRunning_ = false;
}

/*************************/
//methode qui demarre la minuterie et autorise les interruptions
//prend la duree en argument
/*************************/
void Timer::partirMinuterie(uint6_t duree) {
    timerIsRunning_ = true;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    //mode CTC, TCNT1 et compare match
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = (1 << WGM12) ;
    TCCR1B = (1 << CS12) | (1 << CS10) ;
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A) ;
}

/*************************/
//methode qui arrete la minuterie
//aucun argument et ne renvoie rien
/*************************/
void Timer::stopMinuterie() {
    TIMSK1 &= ~(1 << OCIE1A);
    timerIsRunning_ = false;
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

/*************************/
//methode ISR
//aucun argument et ne renvoie rien
/*************************/
void Timer::newISR(vector vecteur, volatile bool& var) {
    ISR(TIMER1_COMPA_vect) {
        timerIsRunning_ = false;
        &var = false;
    }
}