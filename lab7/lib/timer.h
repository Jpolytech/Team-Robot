#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Timer {
    public:
        timer();
        void startTimer(uint6_t duration);
        void stopTimer();
        bool IsTimerRunning();
        void setTimerRunning(bool value);

    private:
        bool timerIsRunning_;       
}