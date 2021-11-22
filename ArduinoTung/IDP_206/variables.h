#ifndef VARIABLES_H
#define VARIABLES_H

// PID
int KP = 10;
int KI = 0;
int KD = 10;
const int tuningFactor = 100;

// Line follower
int offset = 44;

// Motors
int averagePower = 230;
int defaultDelay = 0;
const byte leftMotorChannel = 4;
const byte rightMotorChannel = 3;

const byte STOP = 0;
const byte CLOCKWISE = 1;
const byte ANTICLOCKWISE = 2;

// Line sensors
const int frontLeftPin = A0;
const int frontRightPin = A1;

const int WHITE = 50;
const int BLACK = 900;
const int THRESHOLD = 20;

struct LightValues {
  int front_left;
  int front_right;
  int back_left;
  int back_right;

  LightValues();
} ;

const int OFF_LINE_TIMEOUT = 1500;

// Distance sensors
const int ultraSonicPin;
const int IRPin;

// Global
bool moving;
bool on_line;
bool at_junction_back;
int last_off_line_millis;

#endif
