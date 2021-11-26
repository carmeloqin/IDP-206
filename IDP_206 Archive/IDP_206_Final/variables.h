#ifndef VARIABLES_H
#define VARIABLES_H

// Pins
const int frontLeftPin = A0;
const int frontRightPin = A1;
const int backRightPin = A2;
const int backLeftPin = A3;
const int IRDistancePin = A4;
const int IRDistancePin2 = A5;

const int ultraSonicPingPin = 2;
const int ultraSonicEchoPin = 3;
const int leftIRPhototransitorPin = 4;
const int rightIRPhototransitorPin = 5;
const int leftEncoderPin = 6;
const int rightEncoderPin = 7;
const int greenLEDPin = 8;
const int amberLEDPin = 9;
const int redLEDPin = 10;
const int speakerPin = 11;
const int startButtonPin = 12;

// PID
int KP = 3;
int KI = 0;
int KD = 20;
const int tuningFactor = 100;

// Line follower
int offset = 0;

// Motors
int averagePower = 230;
int defaultDelay = 0;
const byte leftMotorChannel = 4;
const byte rightMotorChannel = 3;

const byte STOP = 0;
const byte CLOCKWISE = 1;
const byte ANTICLOCKWISE = 2;

// Line sensors
const int WHITE = 50;
const int BLACK = 900;
const int THRESHOLD = 20;

struct LightValues {
  int front_left;
  int front_right;
  int back_left;
  int back_right;
} current_l_value, last_l_value;

const int OFF_LINE_TIMEOUT = 1500;

// Dummies
const byte WHITE_DUMMY = 0;
const byte RED_DUMMY = 1;
const byte BLUE_DUMMY = 2;
const byte NO_DUMMY = 3;

// Global
bool moving;
int last_on_line_front;

#endif
