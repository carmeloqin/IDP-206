#include "helper.h"
#include "controllers.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motors::begin();
  sensors::begin();

  pinMode(7, INPUT);

  moving = false;
//  line_follower.run(FORWARD, isArrivingJunctionBack, 4, [](){Serial.println("haha");});
  simple_controller.rotate(CLOCKWISE, isGettingOnLineFront);
}

void loop() {
//  if (digitalRead(startButtonPin) == HIGH) {
//    Serial.println("Starting..");
    
    // Run forward until a dummy is found
//    line_follower.run(FORWARD, isDummyFound);
  
    // Run forever
//    line_follower.run(FORWARD, [](){return false;});
  
    // Turn around until touching the line
//    simple_controller.rotate(CLOCKWISE, isGettingOnLineFront);
  
    // Run forward until having arrived at the 2nd junctions
//    line_follower.run(FORWARD, isArrivingJunctionBack, 2);
//  }
}
