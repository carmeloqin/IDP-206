#include <Servo.h>
#include "Arduino.h"
#include "variables.h"

Servo grabberServo;  
Servo lifterServo;

namespace servos{
  void openGrabber(){
    grabberServo.attach(grabberServoPin);
    for (pos = 0; pos <= 60; pos += 1) { 
      grabberServo.write(pos);              
        delay(100);                      
    }
  }

  void closeGrabber(){
    grabberServo.attach(grabberServoPin);
    for (pos = 60; pos >= 00; pos -= 1) {
      grabberServo.write(pos);              
      delay(100);                       
    }
  }

  void descendLifter(){
    lifterServo.attach(lifterServoPin);
    for (pos = 0; pos <= 60; pos += 1) { 
      // in steps of 1 degree
      lifterServo.write(pos);              
        delay(30);                       
    }
  }

  void ascendLifter(){
    lifterServo.attach(lifterServoPin);
    for (pos = 60; pos >= 00; pos -= 1) { 
      lifterServo.write(pos);              
      delay(30);                       
    }
  }
}
