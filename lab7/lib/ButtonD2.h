#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

enum class InterruptMode
{
    RISING_EDGE,
    FALLING_EDGE,
    CHANGE_EDGE
};

class ButtonD2
{
public:
    ButtonD2(InterruptMode mode);

    void enableInterrupt();
    void disableInterrupt();
    void clearInterruptFlag();

private:
    void setInterruptMode(InterruptMode mode);
    void initialisation(InterruptMode mode);
    const uint8_t DEBOUNCE_DELAY = 30;
};
