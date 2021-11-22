/*
  Arduino Starter Kit example
  Project 5 - Servo Mood Indicator

  This sketch is written to accompany Project 5 in the Arduino Starter Kit

  Parts required:
  - servo motor
  - 10 kilohm potentiometer
  - two 100 uF electrolytic capacitors

  created 13 Sep 2012
  by Scott Fitzgerald

  https://store.arduino.cc/genuino-starter-kit

  This example code is part of the public domain.
*/

// include the Servo library
#include <Servo.h>

Servo myServo;  // create a servo object
Servo myServo2;  // create a servo object

int const potPin = A0; // analog pin used to connect the potentiometer
int const pot2Pin = A1; // analog pin used to connect the potentiometer
int potVal;  // variable to read the value from the analog pin
int pot2Val;  // variable to read the value from the analog pin

int angle;   // variable to hold the angle for the servo motor
int angle2;   // variable to hold the angle for the servo motor


void setup() {
  myServo.attach(9); // attaches the servo on pin 9 to the servo object
  myServo2.attach(10);
  Serial.begin(9600); // open a serial connection to your computer
}

void loop() {
  
  potVal = analogRead(potPin); // read the value of the potentiometer
  // print out the value to the Serial Monitor
  Serial.print("potVal: ");
  Serial.print(potVal);
  // scale the numbers from the pot
  angle = map(potVal, 0, 1023, 0, 179);
  // print out the angle for the servo motor
  Serial.print(", angle: ");
  Serial.println(angle);
  // set the servo position
  myServo.write(angle);

  pot2Val = analogRead(pot2Pin); // read the value of the potentiometer
  // print out the value to the Serial Monitor
  Serial.print("pot2Val: ");
  Serial.print(pot2Val);
  // scale the numbers from the pot
  angle2 = map(pot2Val, 0, 1023, 0, 179);
  // print out the angle for the servo motor
  Serial.print(", angle2: ");
  Serial.println(angle2);
  // set the servo position
  myServo2.write(angle2);



  // wait for the servo to get there
  delay(15);
}
