#include "algorithm.h"
#include "debug.h"

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Starting M206 Dummy Picker");
  
  motors::begin();
  sensors::begin();
  indicator::begin();
  
  Serial.println("Awaiting Push Button Activiation...");
  Serial.println("");
}

void loop() {
  if (conditionals::isStartButtonPressed()) {
    Serial.println("Starting...");
//    algo::getFirstDummy();
//    debug::plotLightValues();
//    debug::plotLightValuesDerivative();
//    debug::findDummy();
//    debug::plotIRPhototransitorCounts();
//    debug::findDummyaa();
//    debug::plotDistanceUltraSonic();

//    debug::indicatorTest();
//    debug::getDistanceIRTest();
      debug::trackEncoderCountTest();
  }
}
