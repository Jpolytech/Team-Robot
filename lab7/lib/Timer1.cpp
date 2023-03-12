#include "Timer1.h"

/*************************/
// constructeur par defaut
// aucun argument et ne renvoie rien
/*************************/
Timer1::Timer1(WaveformMode mode, Prescaler prescaler) : mode_(mode),
                                                         prescaler_(prescaler)
{
    timerIsRunning_ = false;
}

void Timer::startTimer(uint16_t duration, WaveformMode newMode, Prescaler newPrescaler)
{
    mode_ = newMode;
    prescaler_ = newPrescaler;
    startTimer(duration);
}

/*************************/
// methode qui demarre la minuterie et autorise les interruptions
// prend la duree en argument
/*************************/
void Timer1::startTimer(uint16_t duration)
{
    cli();
    timerIsRunning_ = true;
    TCNT1 = 0;
    OCR1A = duration;
    setWaveformMode(mode_);
    setPrescaler(prescaler_);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    sei();
}

void Timer1::setWaveformMode(WaveformMode mode)
{
    // TODO : implement
    switch (mode)
    {
    case WaveformMode::Normal:
        break;
    case WaveformMode::CTC:
        break;
    }
}

void Timer1::setPrescaler(Prescaler prescaler)
{
    // TODO : implement
    switch (prescaler)
    {
    case Prescaler::NoPrescaling:
        TCCR1B...;
        break;
    case Prescaler::Prescaling8:
        TCCR1B...;
        break;
    }
}

/*************************/
// methode qui arrete la minuterie
// aucun argument et ne renvoie rien
/*************************/
void Timer1::stopTimer()
{
    // TODO: Mettre prescaler à NO PRESCALER
    timerIsRunning_ = false;
}

/*************************/
// methode qui renvoie le dernier etat de la minuterie
// renvoie un booleen: vrai si la minuterie est demarree
/*************************/
// bool Timer::IsTimerRunning() {
//     return timerIsRunning_;
// } //not sure
