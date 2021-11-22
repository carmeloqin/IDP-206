#ifndef HELPER_H
#define HELPER_H

#include "sensors.h"

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

bool isAtJunctionFront() {
  LightValues l_value = sensors::getLightValues();
  bool left = isWhite(l_value.front_left);
  bool right = isWhite(l_value.front_right);
  
  if (left && right) {
    return true;
  }
  return false;
}

bool isAtJunctionBack() {
  LightValues l_value = sensors::getLightValues();
  bool left = isWhite(l_value.back_left);
  bool right = isWhite(l_value.back_right);
  
  if (left && right) {
    at_junction_back = true;
    return true;
  }
  at_junction_back = false;
  return false;
}

bool isJunctionPassedBack() {
  // Check if a junction is passed
  if (!at_junction_back) {
    if (isAtJunctionBack()) {
      // arrived at a junction
      return false;
    }
  } else if (!isAtJunctionBack()) {
      // left the junction
      return true;
  }
  return false;
}

bool isTurning() {
  return true; // to-do: code checking if it's turning;
}

bool isOnLine() {
  LightValues l_value = sensors::getLightValues();
  bool right = isBlack(l_value.front_right);
  bool left = isBlack(l_value.front_left);
  if (!(right && left)) {
     last_off_line_millis = millis();
     on_line = true;
  }
  
  if (millis() - last_off_line_millis > OFF_LINE_TIMEOUT) {
    on_line = false;
  }
  return on_line;
}

bool isLineFound() {
  if (!on_line) {
    if (isOnLine()) {
      return true;
    }
  } else if (!isOnLine()) {
    return false;
  }
  return false;
}

bool isDummyFound() {
  return false;
}

bool isWithinRangeUltraSonic(int range) {
  if (sensors::getDistanceUltraSonic() < range) {
    return true;
  }
  return false;
}

bool isWithinRangeIR(int range) {
  if (sensors::getDistanceIR() < range) {
    return true;
  }
  return false;
}

void doNothing() {}

#endif
