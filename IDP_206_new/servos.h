#include <Servo.h>
#include "Arduino.h"
#include "variables.h"

Servo grabberServo;  
Servo lifterServo;

namespace servos {
  int posSpeed = 1;
  
  void openGrabber(){
    for (int pos = 20; pos <= 110; pos += posSpeed) { 
      grabberServo.write(pos);              
        delay(100);                      
    }
  }

  void closeGrabber(){
    for (int pos = 110; pos >= 20; pos -= posSpeed) {
      grabberServo.write(pos);              
      delay(100);                       
    }
  }

  void ascendLifter(){
    for (int pos = 0; pos <= 56; pos += posSpeed) { 
      // in steps of 1 degree
      lifterServo.write(pos);              
        delay(30);                       
    }
  }

  void descendLifter(){
    for (int pos = 56; pos >= 0; pos -= posSpeed) { 
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
    lifterServo.write(53);
    grabberServo.write(110);
  }
}
