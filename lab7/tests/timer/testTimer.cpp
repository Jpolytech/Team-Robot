#define F_CPU 8000000UL
#include <Timer1.h>
using namespace std;

volatile bool timerIsRunning = false;

void rouge(){
    PORTA &= ~(1 << PORTA0);
    PORTA |= (1 << PORTA1);
}

void eteint(){
    PORTA &= ~(1 << PORTA0);
    PORTA &= ~(1 << PORTA1);
}

void vert(){
    PORTA |= (1 << PORTA0);
    PORTA &= ~(1 << PORTA1);
}

//routines ISR
ISR(TIMER1_COMPA_vect) {
    timerIsRunning = false;
}

int main()
{
    Timer1 t = Timer1(WaveformMode::CTC, Prescaler::PRESCALE_1024);
    t.startTimer(10000);
    timerIsRunning = t.getTimerIsRunning();
    while(timerIsRunning) {
        rouge();
    }
    t.stopTimer();

    t.startTimer(10000, WaveformMode::NORMAL, Prescaler::PRESCALE_1024);
    timerIsRunning = t.getTimerIsRunning();
    while(timerIsRunning) {
        vert();
    }
    t.stopTimer();

    t.startTimer(9000, WaveformMode::CTC, Prescaler::PRESCALE_256);
    timerIsRunning = t.getTimerIsRunning();
    while(timerIsRunning) {
        rouge();
    }
    t.stopTimer();

    t.startTimer(8000, WaveformMode::CTC, Prescaler::PRESCALE_64);
    timerIsRunning = t.getTimerIsRunning();
    while(timerIsRunning) {
        vert();
    }
    t.stopTimer();

    t.startTimer(7000, WaveformMode::NORMAL, Prescaler::PRESCALE_8);
    timerIsRunning = t.getTimerIsRunning();
    while(timerIsRunning) {
        rouge();
    }
    t.stopTimer();

    eteint();
    return 0;
}