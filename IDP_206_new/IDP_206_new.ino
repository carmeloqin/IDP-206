#include "algorithm.h"
#include "debug.h"

void setup() {
  Serial.begin(9600);
  motors::begin();
  sensors::begin();
}

void loop() {
  if (conditionals::isStartButtonPressed()) {
    Serial.println("Starting..");
//    algo::getFirstDummy();
    debug::plotLightValues();
//    debug::plotLightValuesDerivative();
//      debug::findDummy();
//    debug::plotIRPhototransitorCounts();
//   debug::findDummyaa();
  }
}
