#include "helper.h"
#include "controllers.h"
#include "dummy.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motors::begin();
  sensors::begin();
}

void loop() {
  if (sensors::isStartButtonPressed()) {
    Serial.println("Starting..");
      line_follower.run(FORWARD, isArrivingJunctionBack, 2);
      line_follower.run(FORWARD, isDummyFound);
      
      indicator::indicate(last_dummy_found);
      delay(1000);
      indicator::indicate(NO_DUMMY);

      simple_controller.rotate(CLOCKWISE, isGettingOnLineFront);
      line_follower.run(FORWARD, isArrivingJunctionBack, 2);
  }
}
