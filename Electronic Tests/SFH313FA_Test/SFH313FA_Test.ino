#include "storage.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(A0, INPUT); // analog pin
  pinMode(2, INPUT); // digital pin
  prev_reading = analogRead(A0);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalCode();
}
