#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

{
    class switchingLedColours
    {
    public:
    switchingLedColours(uint8_t* ddrx,
                        volatile uint8_t* portx,
                        uint8_t setPos,
                        uint8_t clearPos) : 
                        ddrx_(ddrx), 
                        portx_(portx), 
                        setPos_(setPos), 
                        clearPos_(clearPos)
    {
        *ddrx_ |= (1 << setPos) | (1 << clearPos);
    }
    void switchLedGreen();
    void switchLedRed();
    void turnedOffLed();
    void switchLedAmber();

private:        
    uint8_t portx_;
    uint8_t setPos_;
    uint8_t clearPos_;
    uint8_t* ddrx_;
    };
}