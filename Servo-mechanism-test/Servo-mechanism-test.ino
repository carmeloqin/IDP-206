#include <Servo.h>

Servo grabberServo;  
Servo lifterServo;

int grabberServoPin = 9;
int lifterServoPin =10;
int pos = 0;

void setup() {
  grabberServo.attach(grabberServoPin);
  lifterServo.attach(lifterServoPin);
  Serial.begin(9600);
}

void openGrabber(){
  for (pos =20; pos <= 110; pos += 1) { 
    grabberServo.write(pos);              
      delay(30);                      
  }
}

void closeGrabber(){
  for (pos = 110; pos >= 20; pos -= 1) {
    grabberServo.write(pos);              
    delay(30);                       
  }
}

void ascendLifter(){
  for (pos = 75; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    lifterServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(30);                       // waits 15ms for the servo to reach the position
  }
}

void descendLifter(){
  for (pos = 120; pos >= 75; pos -= 1) { // goes from 180 degrees to 0 degrees
    lifterServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}

void loop() {
  lifterServo.write(120); 
  delay(2000);
  grabberServo.write(110);
  delay(2000);
  openGrabber();
  delay(1000);
  descendLifter();
  delay(1000);
  closeGrabber();
  delay(1000);
  ascendLifter();
  delay(1000);
  descendLifter();
  delay(1000);
  openGrabber();
  delay(1000);
}
