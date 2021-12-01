#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "sensors.h"

namespace conditionals {
  const int DERIVATIVE_THRESHOLD = 400;
  bool curr_at_junction_front = false;
  bool prev_at_junction_front = false;
  bool curr_at_junction_back = false;
  bool prev_at_junction_back = false;

//---------- Boolean Functions ----------//
  bool isAllWhite(int val_1, int val_2) {
    return sensors::isWhite(val_1) && sensors::isWhite(val_2);
  }

  bool isAllWhiteFront(int val_1, int val_2) {
    return sensors::isWhiteFront(val_1) && sensors::isWhiteFront(val_2);
  }
  bool isAllWhiteBack(int val_1, int val_2) {
    return sensors::isWhiteBack(val_1) && sensors::isWhiteBack(val_2);
  }

  bool isAnyWhite(int val_1, int val_2) {
    return sensors::isWhite(val_1) || sensors::isWhite(val_2);
  }

  bool isAnyBlack(int val_1, int val_2) {
    return sensors::isBlack(val_1) || sensors::isBlack(val_2);
  }


//---------- Junction Functions ----------//
// FRONT SENSORS
  void readFrontValues() {
    LightValues l_value = sensors::getLightValues();
    prev_at_junction_front = curr_at_junction_front;
    curr_at_junction_front = isAllWhiteFront(l_value.front_right, l_value.front_left);
  }

  bool isAtJunctionFront() {
    readFrontValues();
    return curr_at_junction_front;
  }

  bool isArrivingJunctionFront() {
    readFrontValues();
    return curr_at_junction_front && !prev_at_junction_front;
  }

   bool isLeavingJunctionFront() {
    readFrontValues();
    return !curr_at_junction_front && prev_at_junction_front;
  }

// BACK SENSORS
  void readBackValues() {
    LightValues l_value = sensors::getLightValues();
    prev_at_junction_back = curr_at_junction_back;
    curr_at_junction_back = isAllWhiteBack(l_value.back_right, l_value.back_left);
  }
  
  bool isAtJunctionBack() {
    readBackValues();
    return curr_at_junction_back;
  }
  
  bool isArrivingJunctionBack() {
    readBackValues();
    return curr_at_junction_back && !prev_at_junction_back;
  }
  
  bool isLeavingJunctionBack() {
    readBackValues();
    return !curr_at_junction_back && prev_at_junction_back;
  }

  bool isOnLineFront(unsigned long timeout = OFF_LINE_TIMEOUT) {
    if (timeout == 0) {
      return true;
    }
    
    LightValues l_value = sensors::getLightValues();
    bool right = sensors::isBlack(l_value.front_right);
    bool left = sensors::isBlack(l_value.front_left);
    if (!(right && left)) {
       last_on_line_front = millis();
    } else if (millis() - last_on_line_front > timeout) {
      return false;
    }
    return true;
  }

  bool foundLineWhileRotateCW() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return d_l_value.front_left * (-1) > DERIVATIVE_THRESHOLD;
  }

  bool foundLineWhileRotateACW() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return d_l_value.front_right * (-1) > DERIVATIVE_THRESHOLD;
  }

  bool isRotating() {
    return true; // to-do: code checking if it's turning;
  }
  
  bool isMoving() {
    return moving;
  }

  bool isStartButtonPressed() { 
    return !digitalRead(startButtonPin); //1 is button not pressed, 0 is button pressed
  }
  
  bool isWithinRangeUltraSonic(int low, int high) {
    int d = sensors::getDistanceUltraSonic();
    return low < d && d < high;
  }
  
  bool isWithinRangeIR(int low, int high) {
    int d = sensors::getDistanceIR();
    return low < d && d < high;
  }

  bool isDummyDetected() {
    return sensors::findDummy() != NO_DUMMY || isWithinRangeUltraSonic(39, 41);
  }
  
  bool isDummyFound1() {
    byte flag = sensors::findDummy();
    bool found = !(flag == NO_DUMMY) && isWithinRangeUltraSonic(40, 50);
//    Serial.println(found);
    return found;
  }

  bool isDummyFound() {
//    byte flag = sensors::findDummy();
    bool found = isWithinRangeUltraSonic(65, 100); //changed it to 100
//    Serial.println(found);
    return found;
  }

    bool isDummyInRange() { //new, todo
//    byte flag = sensors::findDummy();
    bool found = isWithinRangeUltraSonic(65, 80); //will change this range, control car to this range.
//    Serial.println(found);
    return found;
  }

}

#endif
