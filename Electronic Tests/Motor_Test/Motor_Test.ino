#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *myMotor = AFMS.getMotor(1); // connect motor to channel 1

void setup() {
  Serial.begin(9600);         // set up Serial library at 9600 bps
  Serial.println("Motor test");
  
  AFMS.begin();

  // Test by initiating with a set speed
  myMotor->setSpeed(150);
  delay(1000);
  myMotor->run(FORWARD);
  delay(1000);
  
}

void loop() {
  Serial.print("tick ");
  
  myMotor->run(FORWARD);      // turn it on going forward
  myMotor->setSpeed(150);     // redundunt, for testing purposes only

  Serial.print("tock ");
  myMotor->run(BACKWARD);     // the other way
  myMotor->setSpeed(150);
  
  Serial.println("tack; ");
  myMotor->run(RELEASE);      // stopped
  myMotor->setSpeed(150);
}
