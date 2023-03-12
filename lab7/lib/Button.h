#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

enum class InterruptMode
{
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES
};

enum class InterruptNumber : uint8_t
{
    INT0 = 0,
    INT1 = 1,
    INT2 = 2
};

class Button
{
public:
    void setInterruptMode(InterruptMode mode);
    void enableInterrupt();
    void disableInterrupt();
    void clearInterruptFlag();

private:
    Button(InterruptNumber number, InterruptMode mode);
    void initialisation(InterruptMode mode);

    const uint8_t interruptNumber_;
    static inline const uint8_t DEBOUNCE_DELAY_ = 30;
};

class ButtonD2 : public Button
{
public:
    ButtonD2(InterruptMode mode);
};

class ButtonD3 : public Button
{
public:
    ButtonD3(InterruptMode mode);
};

class ButtonB2 : public Button
{
public:
    ButtonB2(InterruptMode mode);
};
