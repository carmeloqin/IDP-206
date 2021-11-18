#include "constants.h"
#include "line_follower.h"

bool done = false;
using namespace linefollower;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!done) {
    linefollower::goForward();
  }
}
