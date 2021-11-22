#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "variables.h"

namespace sensors {
  int analogReadAverage(int pin, int times = 3) {
    int sum = 0;
    for (int i=0; i<times; i++) {
      sum += analogRead(pin);
    }
    return sum / times;
  }
  
  int getDistanceUltraSonic() {
    // Use this pin ultraSonicPin for analogRead/digitalRead
  }

  int getDistanceIR() {
    // Use this pin: IRPin for analogRead/digitalRead
  }

  LightValues getLightValues() {
    return LightValues::LightValues();
  }

  void begin() {
    pinMode(frontLeftPin, INPUT);
    pinMode(frontRightPin, INPUT);
    pinMode(ultraSonicPin, INPUT);
    pinMode(IRPin, INPUT);
  }
}

LightValues::LightValues() {
  front_left = sensors::analogReadAverage(frontLeftPin);
  front_right = sensors::analogReadAverage(frontRightPin);
}

#endif
