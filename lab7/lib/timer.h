#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Timer {
    public:
    Minuterie();
    void partirMinuterie(uint6_t duree);
    void stopMinuterie();
    bool IsTimerRunning();
    void setTimerRunning(bool value);
    void newISR(vector vecteur, volatile bool& var); //à verifier

    private:
        bool timerIsRunning_;
}