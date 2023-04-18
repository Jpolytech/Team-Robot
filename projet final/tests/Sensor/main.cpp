#include "Uart.h"
#include "Sensor.h"
#include <util/delay.h>
#include <stdio.h>

// CURRENT AREF: 3.5

const uint8_t distanceMaxFirstPos = 50;
const uint8_t distanceMaxSecondPos = 30; 
const uint8_t distanceFinale = 123;

const bool SHOW_DISTANCE = true; // commencer par prendre les distances (mettre a true)
const bool SHOW_SPOT = false; // quand les distances sont obtenues tester (mettre a true)
const int PRINT_DELAY = 250;

int lastSpot = -1;

uint8_t deduceSpot(uint8_t distance) {
    if(distance >= distanceMaxFirstPos) {
        return 1; // sle poteau est dans l'entourage du robot
    }
    else if(distance >= distanceMaxSecondPos) {
        return 2;
    }
    return 0;
}

int main(){
    ManagementUSART uart;
    Sensor sensor;
    uart.initialisation();

    char buffer[30];

    while (true){
        uint8_t distance = sensor.getDistance();

        if (SHOW_DISTANCE) {
            uart.transmitData(distance);
        }

        if (SHOW_SPOT) {
            uint8_t spot = deduceSpot(distance);
            int n;  
            if (spot == 0) {
                n = sprintf(buffer, "NOTHING MY FRIEND");
            }
            else if (spot == 2) {
                n = sprintf(buffer, "FAR");
            }
            else if (distance >= distanceFinale) {
                n = sprintf(buffer, "ARRIVED");

            }
            else {

                n = sprintf(buffer, "%s", "CLOSE");
            }
            uart.transmitString(buffer, n);
            uart.transmitData('\n');
            lastSpot = spot;
        }

        _delay_ms(PRINT_DELAY);
    }
}
