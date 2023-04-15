#include <Timer1.h>
#define F_CPU 8000000UL

Timer1 timer = Timer1(WaveformMode::CTC, Prescaler::PRESCALE_1024);

int main()
{
    timer.startTimer(781);
    PORTA ^= 0b01; 
    timer.stopTimer();
}
