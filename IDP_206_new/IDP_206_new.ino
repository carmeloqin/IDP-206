#include "algorithm.h"
#include "debug.h"

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Starting M206 Dummy Picker");
  
  motors::begin();
  sensors::begin();
  indicator::begin();
  servos::begin();
  
  Serial.println("Awaiting Push Button Activiation...");
  Serial.println("");
}

void loop() {
  if (conditionals::isStartButtonPressed()) {
    Serial.println("Starting...");

// DEBUGGING FOR SENSORS/ACTUATORS
//    Serial.println("FL\tFR\tBR\tBL");
//    debug::plotLightValues();
//    debug::plotLightValuesDerivative();

//    debug::findDummy(); //with IR phototransistor
//    debug::plotIRPhototransitorCounts();
//    debug::findDummyaa();

//    debug::plotDistanceUltraSonic();

//    debug::indicatorTest();
//    debug::getDistanceIRTest();
//    debug::trackEncoderCountTest();


//    debug::servoTest();

// DEBUGGING FOR ALGORITHM
//    algo::findDummy(); //Find with ultrasonic

//    algo::getLineDummy();
//    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
//    algo::dropOff(WHITE_DUMMY);
//    debug::debugGeneral();

// FINAL CODE
    algo::rescueLineDummy();



  }
}
