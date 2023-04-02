#define F_CPU 8000000UL
#include <avr/io.h>
#include "../../lib/Robot.h"
#include "../../lib/Can.h"
#include "../../lib/Pwm.h"
#include "../../lib/Sensor.h"

int main() {
    Robot robot = Robot();
    robot.initialisation();
    robot.searchPost();
}