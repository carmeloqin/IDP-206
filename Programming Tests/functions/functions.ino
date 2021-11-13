#include "return_variable.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
}

void loop() {

  int x = 0; //insert which number to return (0,1,2)
  
  try_1();
  Serial.println(returns[x]);
  delay(1000);

  Serial.println(try_2(x));
  delay(1000);
}
