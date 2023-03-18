/*
Auteurs:
    Andreea Maria Ghioltan
    Maria Bourouisa
    Jean-Philippe Salis Routhier 
    Thibault Delahaie

Description de la classe: Cette classe gère n'importe quel bouton relié au robot selon les pins D2, D3 ou B2.

Identifications des broches (Broches I/O): D2, D3 et B2 tous en tant qu'output. 
*/

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum class InterruptMode
{
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES
};

enum class InterruptNumber
{
    INTERRUPT0 = 0,
    INTERRUPT1 = 1,
    INTERRUPT2 = 2
};

class Button
{
public:
    void setInterruptMode(InterruptMode mode);
    void setPinMode(InterruptNumber number);
    void enableInterrupt();
    void disableInterrupt();
    void clearInterruptFlag();

private:
    void initialisation(InterruptMode mode);

    const InterruptNumber interruptNumber_;
    static const uint8_t DEBOUNCE_DELAY_ = 30;

protected:
    Button(InterruptNumber number, InterruptMode mode);
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
