
/*
Websites used:
https://robojax.com/learn/arduino/?vid=robojax-sharp_IR
https://www.youtube.com/watch?v=GL8dkw1NbMc

Test in progress.
*/


#include <SharpIR.h>

#define IR A1 // define signal pin
#define model 20150 // used 20150 because model GP2Y0A02Y is used
// Sharp IR code for Robojax.com
// ir: the pin where your sensor is attached
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y   THIS ONE THIS ONE THIS ONE
//                                            430 for GP2Y0A41SK  

SharpIR IRsensor(IR, model);


void setup() {
  // Sharp IR code for Robojax.com
  Serial.begin(9600);
  Serial.println("Robojax Sharp IR  ");
}

void loop() {
  // Sharp IR code for Robojax.com
  delay(500);   

  float volts = analogRead(IR)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 
  
  if (distance <= 30){
    Serial.println(distance);   // print the distance
  }





  /* Sharp IR code for Robojax.com
  
    unsigned long startTime=millis();  // takes the time before the loop on the library begins

  int dis = IRsensor.getDistance();  // this returns the distance to the object you're measuring
  //Serial.println(dis);

  long a1 = analogRead(A1);
  Serial.println(a1);
  int distance = 9462/(analogRead(A1)-16.92);
  Serial.println(dis);

  if(distance > 150) return 151;
  else if(distance < 20) return 19;
  else return distance;

  /* Sharp IR code for Robojax.com

  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  Serial.println(analogRead(A1));
  unsigned long endTime=millis()-startTime;  // the following gives you the time taken to get the measurement
  Serial.print("Time taken (ms): ");
  Serial.println(endTime);  
  // Sharp IR code for Robojax.com
  */
     
}
