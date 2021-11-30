#include "storage.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(A0, INPUT); // analog pin
  pinMode(4, INPUT); // digital pin
  pinMode(5, INPUT);
  prev_reading = analogRead(A0);
}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("PIN NUMBER 4:  ");
  digitalCode(4);
  digitalCode(5);
//  Serial.print(digitalRead(4));
//  Serial.print('\t');
//  Serial.println(digitalRead(5));
}
