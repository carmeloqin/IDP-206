#ifndef HELPER_H
#define HELPER_H

#include "Arduino.h"
#include "sensors.h"

bool isAtJunction(int left_value, int right_value) {
  bool left = sensors::isWhite(left_value);
  bool right = sensors::isWhite(right_value);
  
  if (left && right) {
    return true;
  }
  return false;
}

bool isAtJunctionFront() {
  LightValues l_value = sensors::getLightValues();
  return isAtJunction(l_value.front_left, l_value.front_right);
}

bool isAtJunctionBack() {
  LightValues l_value = sensors::getLightValues();
  return isAtJunction(l_value.back_left, l_value.back_right);
}

bool isPrevAtJunctionFront() {
  return isAtJunction(last_l_value.front_left, last_l_value.front_right);
}

bool isPrevAtJunctionBack() {
  return isAtJunction(last_l_value.back_left, last_l_value.back_right);
}

bool isArrivingJunctionBack1() {
  bool arrived = !isPrevAtJunctionBack() && isAtJunctionBack();
  if (arrived) {
    Serial.println("arrived");
  }
  return arrived;
}

bool isArrivingJunctionBack() {
  bool arrived = false;
  if (millis() - last_at_junction > 2000) {
    if (isAtJunctionBack()) {
      last_at_junction = millis();
      arrived = true;
      delay(200);
    }
  }
//  if (arrived) {
//    Serial.println("Junction arrived");
//  }
//  Serial.println(arrived);
  return arrived;
}

bool isLeavingJunctionBack() {
  return isPrevAtJunctionBack() && !isAtJunctionBack();
}

bool isRotating() {
  return true; // to-do: code checking if it's turning;
}


bool isMoving() {
  return moving;
}

//bool isOnLineFront(int timeout = OFF_LINE_TIMEOUT) {
//  LightValues l_value = sensors::getLightValues();
//  bool right = sensors::isBlack(l_value.front_right);
//  bool left = sensors::isBlack(l_value.front_left);
//  if (!(right && left)) {
//     last_on_line_front = millis();
//  } else if (millis() - last_on_line_front > timeout) {
//    return false;
//  }
//  return true;
//}

bool isOnLineFront(int timeout = 0) {
  LightValues l_value = sensors::getLightValues();
  return true;
}
//
//bool isPrevOnLineFront() {
//  bool right = sensors::isBlack(last_l_value.front_right);
//  bool left = sensors::isBlack(last_l_value.front_left);
//  return !(left && right);
//}
//
//bool isGettingOnLineFront() {
//  return !isPrevOnLineFront() && isOnLineFront(0);
//}
//
//bool isGettingOffLineFront() {
//  return isPrevOnLineFront() && !isOnLineFront(0);
//}

bool isGettingOnLineFront() {
  LightValues l_value = sensors::getLightValues();
  bool right = sensors::isWhite(l_value.front_right);
  bool left = sensors::isWhite(l_value.front_left);
  return right || left;
  
}

bool isDummyFound() {
  return false;
}

bool isWithinRangeUltraSonic(int range) {
  return sensors::getDistanceUltraSonic() < range;
}

bool isWithinRangeIR(int range) {
  return sensors::getDistanceIR() < range;
}
#endif
