#include <Servo.h>
#include "Arduino.h"
#include "variables.h"

Servo grabberServo;  
Servo lifterServo;

namespace servos {
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
    for (pos = 0; pos <= 60; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      lifterServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
  }

  void ascendLifter(){
    lifterServo.attach(lifterServoPin);
    for (pos = 60; pos >= 00; pos -= 1) { // goes from 180 degrees to 0 degrees
      lifterServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}  
