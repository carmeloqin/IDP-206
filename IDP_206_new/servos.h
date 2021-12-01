#include <Servo.h>
#include "Arduino.h"
#include "variables.h"

Servo grabberServo;  
Servo lifterServo;

namespace servos {
  int up = 135;
  int down = 75;
  int posSpeed = 1;
  
  void openGrabber(){
    for (int pos = 20; pos <= 110; pos += posSpeed) { 
      //grabberServo.attach(grabberServoPin);
      grabberServo.write(pos);              
        delay(30);                      
    }
  }

  void closeGrabber(){
    for (int pos = 110; pos >= 20; pos -= posSpeed) {
      //grabberServo.attach(grabberServoPin);
      grabberServo.write(pos);              
      delay(30);                       
    }
  }

  void ascendLifter(){
    for (int pos = 75; pos <= 135; pos += posSpeed) {
      //lifterServo.attach(lifterServoPin);
      // in steps of 1 degree
      lifterServo.write(pos);              
      delay(30);                       
    }
  }

  void descendLifter(){
    for (int pos = 135; pos >= 75; pos -= posSpeed) { 
      //lifterServo.attach(lifterServoPin);
      lifterServo.write(pos);              
      delay(30);                       
    }
  }

  void pickUp() {
    descendLifter();
    delay(1000);
    closeGrabber();
    delay(1000);
    ascendLifter();
  }

  void dropOff() {
    descendLifter();
    delay(1000);
    openGrabber();
    delay(1000);
    ascendLifter();
  }

  void begin() {

    grabberServo.attach(grabberServoPin);
    lifterServo.attach(lifterServoPin);
    lifterServo.write(135);
    grabberServo.write(110);
  }
}
