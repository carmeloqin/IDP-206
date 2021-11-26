#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "sensors.h"

namespace conditionals {
  const int DERIVATIVE_THRESHOLD = 500;

  bool isAtJunction(int left_value, int right_value) {
    bool left = sensors::isWhite(left_value);
    bool right = sensors::isWhite(right_value);
    
    return left && right;
  }

  bool isAtJunctionFront() {
    LightValues l_value = sensors::getLightValues();
    return isAtJunction(l_value.front_left, l_value.front_right);
  }
  
  bool isAtJunctionBack() {
    LightValues l_value = sensors::getLightValues();
    return isAtJunction(l_value.back_left, l_value.back_right);
  }

  bool isAtEdgeAND(int d1, int d2, int coeff) {
    // Detect a jump in reading of both d1 and d2. coeff=1 means rising edge
    return (d1 * coeff > DERIVATIVE_THRESHOLD)
              && (d2 * coeff > DERIVATIVE_THRESHOLD);
  }

  bool isAtEdgeOR(int d1, int d2, int coeff) {
    // Detect a jump in reading of d1 or d2. coeff=1 means rising edge
    return (d1 * coeff > DERIVATIVE_THRESHOLD)
              || (d2 * coeff > DERIVATIVE_THRESHOLD);
  }
  
  bool isArrivingJunctionBack() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeAND(d_l_value.back_left, d_l_value.back_right, (-1));
  }
  
  bool isArrivingJunctionFront() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeAND(d_l_value.front_left, d_l_value.front_left, (-1));
  }
  
  bool isLeavingJunctionBack() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeAND(d_l_value.back_left, d_l_value.back_right, 1);
  }
  
  bool isLeavingJunctionFront() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeAND(d_l_value.front_left, d_l_value.front_right, 1);
  }

  bool isGettingOnLineFront() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeOR(d_l_value.front_left, d_l_value.front_right, (-1));
  }

  bool isGettingOffLineFront() {
    LightValues d_l_value = sensors::getLightValuesDerivative();
    return isAtEdgeOR(d_l_value.front_left, d_l_value.front_right, 1);
  }

  bool isOnLineFront(unsigned long timeout = OFF_LINE_TIMEOUT) {
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
  
  bool isDummyFound() {
    byte flag = sensors::findDummy();
    return !(flag == NO_DUMMY) && isWithinRangeUltraSonic(40, 60);
  }

}

#endif
