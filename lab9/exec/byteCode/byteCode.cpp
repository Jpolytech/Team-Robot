#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "../../lib/Button.h"
#include "../../lib/Led.h"
#include "../../lib/Memoire_24.h"
#include "../../lib/Timer1.h"
#include "../../lib/Pwm.h"
#include "../../lib/Uart.h"

//constantes
const uint8_t GREEN = 0x01;
const uint8_t RED = 0x02;
volatile uint16_t loopAddress = 0x0000;
volatile uint16_t currentAddress = 0x0000;
volatile uint8_t loopCounter = 0x00;

enum Instructions : const uint8_t
{
    START_CODE = 0x01,
    WAIT = 0x02,
    TURN_ON_LED = 0x44,
    TURN_OFF_LED = 0x45,
    PLAY_NOTE = 0x48,
    STOP_PLAYING_NOTE = 0x09,
    STOP_ENGINE = 0x60,
    STOP_ENGINE2 = 0x61,
    MOVE_FORWARD = 0x62,
    MOVE_BACKWARD = 0x63,
    TURN_RIGHT = 0x64,
    TURN_LEFT = 0x65,
    START_LOOP = 0xC0,
    END_LOOP = 0xC1,
    END_CODE = 0xFF
};

int main() {

    //creation des objets
    Led led = Led(&PORTB, &DDRB, PB0, PB1);
    Pwm motor = Pwm();
    Memoire24CXXX memory;
    ManagementUSART managementUSART;
    managementUSART.initialisation();
    memory.init();

    uint8_t instruction;
    uint8_t operand;

    
    //lecture et execution du code
    while(instruction!=Instructions::START_CODE) {
        memory.lecture(currentAddress++, &instruction);
        _delay_ms(10);
    }
        while(instruction!=Instructions::END_CODE) {
            memory.lecture(currentAddress++, &instruction);
            _delay_ms(10);
            memory.lecture(currentAddress++, &operand);
            while(memory.lecture(currentAddress++, &instruction) == 0) {
            _delay_ms(10);
                switch(instruction) {
                    //attendre 25ms fois l'operandes
                    case Instructions::WAIT:
                        for(int i = 0; i < operand; i++){
                            _delay_ms(25); //timer necessaire?
                        }
                        break;

                    //allumer la led en vert ou rouge selon l'operande
                    case Instructions::TURN_ON_LED:
                        if(operand == GREEN) {led.switchGreen();}
                        if(operand == RED) {led.switchRed();}
                        break;

                    //Eteindre la led
                    case Instructions::TURN_OFF_LED:
                        led.turnedOff();
                        break;
                    
                    //jouer sonorite
                    case Instructions::PLAY_NOTE:
                        //ajouter code pour jouer sonorité
                        break;
                    
                    //arreter de jouer une sonorité
                    case Instructions::STOP_PLAYING_NOTE:
                        //ajouter code pour arreter la sonorite
                        break;

                    //arret des moteurs
                    case Instructions::STOP_ENGINE:
                        motor.turnedOff();
                        break;
                    
                    //arret des moteurs
                    case Instructions::STOP_ENGINE2:
                        motor.turnedOff();
                        break;
                    
                    //avancer
                    case Instructions::MOVE_FORWARD:
                        motor.movingForward(operand);
                        break;
                    
                    //reculer
                    case Instructions::MOVE_BACKWARD:
                        motor.movingBackward(operand);
                        break;
                    
                    //tourner à droite à 90°
                    case Instructions::TURN_RIGHT:
                        motor.turnRight(100);
                        _delay_ms(100); //temps qu'il faut pour que le robot tourne de 90°, à tester
                        motor.turnedOff();
                        break;
                    
                    //tourner à gauche à 90°
                    case Instructions::TURN_LEFT:
                        motor.turnLeft(100);
                        _delay_ms(100);
                        motor.turnedOff();
                        break;
                    
                    //debut de la boucle
                    case Instructions::START_LOOP:
                        if(loopCounter==0)
                            loopCounter = operand;
                        loopAddress = currentAddress;
                        break;
                    
                    //fin de la boucle
                    case Instructions::END_LOOP:
                        if(loopCounter != 0) {
                            //la boucle est en marche, on retourne en haut de la boucle tant que le compteur n'est pas à 0
                            currentAddress = loopAddress;
                            loopCounter--;
                        }
                        break;
                }
        }
    }

    return 0;
}