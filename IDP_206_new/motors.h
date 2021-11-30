#ifndef MOTORS_H
#define MOTORS_H

#include <Adafruit_MotorShield.h>
#include "variables.h"
#include "indicator.h"

namespace motors {
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
  Adafruit_DCMotor *left_motor = AFMS.getMotor(leftMotorChannel);
  Adafruit_DCMotor *right_motor = AFMS.getMotor(rightMotorChannel);

  void setMotorsSpeed(int turn, int average = (-1)) {
      if (average == (-1)) {
        average = averagePower;
      }

      int left = average + turn;
      int right = average - turn;
      if (left > 255) {
        left = 255;
        right = 255 - turn * 2;
      }

      if (right > 255) {
        right = 255;
        left = 255 + turn * 2;
      }

      motors::left_motor->setSpeed(left);
      motors::right_motor->setSpeed(right);

      delay(defaultDelay);
    }

  void _run(Adafruit_DCMotor *motor, byte flag) {
    switch (flag) {
      case RELEASE:
        motor->setSpeed(0);
        indicator::stopped();
        moving = false;
        break;
      case FORWARD:
      case BACKWARD:
        indicator::moving();
        moving = true;
    }
    motor->run(flag);
  }

  void runLeft(byte flag) {
    _run(left_motor, flag);
  }

  void runRight(byte flag) {
    _run(right_motor, flag);
  }

  void begin() {
    Serial.println("Initializing Motors... ");
    AFMS.begin();
    moving = false;
  }
}

#endif
