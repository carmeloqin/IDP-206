#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "variables.h"
#include <SharpIR.h>

namespace sensors {
//  SharpIR IR1(SharpIR::GP2Y0A02YK0F, IRDistancePin);
//  SharpIR IR2(SharpIR::GP2Y0A21YK0F, IRDistancePin);
  
  int analogReadAverage(int pin, int times = 3) {
    int sum = 0;
    for (int i=0; i<times; i++) {
      sum += analogRead(pin);
    }
    return sum / times;
  }

  int getDistanceUltraSonic() {
    long duration, mm;
    digitalWrite(ultraSonicPingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultraSonicPingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSonicPingPin, LOW);
    duration = pulseIn(ultraSonicEchoPin, HIGH);
    mm = 10 * duration / 29 / 2;
    return mm;
  }

  int getDistanceIR(byte flag = 0) {
//    switch (flag) {
//      case 0:
//        return IR1.getDistance();
//      case 1:
//        return IR2.getDistance();
//    }
  }

  int getIRPhototransitorCounts(int pin, int timeout = 1000) {
    int count = 0;
    unsigned long prevtime = millis();
    bool state = false;
    int reading;
    while (millis() - prevtime <= timeout){ // rollover issue to solve
      reading = digitalRead(pin);
      if (reading == HIGH && state == false){
        state = true;
      }
      if (reading == LOW && state == true){
        state = false;
        count += 1;  
      }
    }
    return count;
  }

  bool isWhite(int value) {
    if (value - WHITE < THRESHOLD) {
      return true;
    }
    return false;
  }
  
  bool isBlack(int value) {
    if (BLACK - value < THRESHOLD) {
      return true;
    }
    return false;
  }
  
  LightValues getLightValues() {
    last_l_value = current_l_value;
    current_l_value.front_left = analogReadAverage(frontLeftPin);
    current_l_value.front_right = analogReadAverage(frontRightPin);
    current_l_value.back_right = analogReadAverage(backRightPin);
    current_l_value.back_left = analogReadAverage(backLeftPin);

//    Serial.print(current_l_value.front_left);
//    Serial.print('\t');
//    Serial.print(current_l_value.front_right);
//    Serial.print('\t');
//    Serial.print(current_l_value.back_right);
//    Serial.print('\t');
//    Serial.println(current_l_value.back_left);
    
    return current_l_value;
  }

  void begin() {
    pinMode(frontLeftPin, INPUT);
    pinMode(frontRightPin, INPUT);
    pinMode(ultraSonicPingPin, OUTPUT);
    pinMode(ultraSonicEchoPin, INPUT);
  }
}
#endif
