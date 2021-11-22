#include "variables.h"
#include "motors.h"
#include "sensors.h"
#include "controller.h"
#include "helper.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motors::begin();
  sensors::begin();

  moving = false;
}

void loop() {
  // put your main code here, to run repeatedly:

  // Run forward until dummyFound returns true
  line_follower.run(FORWARD, isDummyFound);

  // Run forever
  line_follower.run(FORWARD, [](){return false;});

  // Turn around until touching the line
  line_follower.turn(CLOCKWISE, isLineFound);

  // Run forward until having passed 2 junctions
  line_follower.run(FORWARD, isJunctionPassedBack, 2);
  line_follower.turn(CLOCKWISE, isLineFound);
}
