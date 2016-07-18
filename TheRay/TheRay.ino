
#include <phys253.h>
#include "Controller.hpp"

void setup()
{
#include <phys253setup.txt>
  Serial.begin(9600) ;


}

void loop()
{
Robot robot = Robot();
robot.drive();
}

