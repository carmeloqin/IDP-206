#include "helper.h"
#include "controllers.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motors::begin();
  sensors::begin();

  moving = false;
}

void loop() {
  if (sensors::isStartButtonPressed()) {
    Serial.println("Starting..");
    while(true) {
//      Serial.println(sensors::getDistanceUltraSonic());
        sensors::getDistanceUltraSonic();
    }
//    line_follower.run(FORWARD, isArrivingJunctionBack, 3, [](){Serial.println("haha");});
//    simple_controller.rotate(CLOCKWISE, isGettingOnLineFront, 2);
//    delay(1000);
//    line_follower.run(FORWARD, isArrivingJunctionBack, 3, [](){Serial.println("haha");});
    
    // Run forward until a dummy is found
//    line_follower.run(FORWARD, isDummyFound);
  
    // Run forever
//    line_follower.run(FORWARD, [](){return false;});
  
    // Turn around until touching the line
//    simple_controller.rotate(CLOCKWISE, isGettingOnLineFront);
  
    // Run forward until having arrived at the 2nd junctions
//    line_follower.run(FORWARD, isArrivingJunctionBack, 2);
  }
}
