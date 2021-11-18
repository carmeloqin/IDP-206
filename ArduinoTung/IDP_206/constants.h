#ifndef Controller_h
#define Controller_h

#include <Adafruit_MotorShield.h>

namespace constants {
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

  Adafruit_DCMotor *left_motor = AFMS.getMotor(3); // connect motor to channel 1
  Adafruit_DCMotor *right_motor = AFMS.getMotor(4); // connect motor to channel 1

  
}

#endif
