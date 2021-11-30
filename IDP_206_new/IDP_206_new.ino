#include "algorithm.h"
#include "debug.h"

void setup() {
  Serial.begin(9600);
  Serial.println("");
//  Serial.println("Starting M206 Dummy Picker");
  
  motors::begin();
  sensors::begin();
  indicator::begin();
  servos::begin();
  
//  Serial.println("Awaiting Push Button Activiation...");
  Serial.println("");
}

void loop() {
  if (conditionals::isStartButtonPressed()) {
//    Serial.println("Starting...");
    Serial.println("FL\tFR\tBR\tBL");

//    algo::getFirstDummy();
//    debug::plotLightValues();
//    debug::plotLightValuesDerivative();
//    debug::findDummy();
//    debug::plotIRPhototransitorCounts();
//    debug::findDummyaa();
//    debug::plotDistanceUltraSonic();

//    debug::indicatorTest();
//    debug::getDistanceIRTest();
//    debug::trackEncoderCountTest();

//      algo::getLineDummy();
      algo::dropOff(RED_DUMMY);
//    debug::debugGeneral();
  }
}
