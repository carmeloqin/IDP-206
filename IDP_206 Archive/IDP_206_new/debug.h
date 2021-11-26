#ifndef DEBUG_H
#define DEBUG_H

#include "sensors.h"

namespace debug {
  void plotLightValues() {
    Serial.println("FL\tFR\tBR\tBL");

    while(true) {
      LightValues l_value = sensors::getLightValues();

      Serial.print(l_value.front_left);
      Serial.print('\t');
      Serial.print(l_value.front_right);
      Serial.print('\t');
      Serial.print(l_value.back_right);
      Serial.print('\t');
      Serial.println(l_value.back_left);

      delay(50);
    }
  }

  void plotLightValuesDerivative() {
    Serial.println("FL\tFR\tBR\tBL");

    while(true) {
      LightValues l_value = sensors::getLightValuesDerivative();

      Serial.print(l_value.front_left);
      Serial.print('\t');
      Serial.print(l_value.front_right);
      Serial.print('\t');
      Serial.print(l_value.back_right);
      Serial.print('\t');
      Serial.println(l_value.back_left);
      
      delay(50);
    }
  }

  void plotDistanceUltraSonic() {
    while(true) {
      Serial.println(sensors::getDistanceUltraSonic());
      delay(50);
    }
  }

  void plotIRPhototransitorCounts(int period = 100) {
    Serial.println("Left\tRight");

    while(true) {
      Serial.print(sensors::getIRPhototransitorCounts(leftIRPhototransitorPin, period));
      Serial.print("\t");
      Serial.println(sensors::getIRPhototransitorCounts(rightIRPhototransitorPin, period));

      delay(50);
    }
  }

  void plotIRPhototransitorCountsPeriod(int periods = 10) {
    Serial.println("Left\tRight");

    while(true) {
      Serial.print(sensors::getIRPhototransitorCountsPeriods(leftIRPhototransitorPin, periods));
      Serial.print("\t");
      Serial.println(sensors::getIRPhototransitorCountsPeriods(rightIRPhototransitorPin, periods));

      delay(50);
    }
  }

  void findDummy() {
    while(true) {
      byte flag = sensors::findDummy();
      switch (flag) {
        case WHITE_DUMMY:
          Serial.println("White dummy");
          break;
        case RED_DUMMY:
          Serial.println("Red dummy");
          break;
        case BLUE_DUMMY:
          Serial.println("Blue dummy");
          break;
        case NO_DUMMY:
          Serial.println("No dummy");
      }
      delay(50);
    }
  }

  void findDummyaa() {
    while(true) {
      Serial.println(conditionals::isDummyFound());
      delay(50);
    }
  }
}

#endif
