/* OP704 Test
See website: https://forum.arduino.cc/t/opb704/286564/4
Use the circuit diagram in website;
1k for the IR LED pull down resistor.
10k  for the pull down resistor on the LDR.

Signal connected to A0 for testing purposes, 
probs will go through comparator and provide a digital signal
on the final circuit board.
*/

int optoswitch = 0;
int state = 0;
int threshold = 23;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Serial.println("OP704 Test");

}

void loop() {
  // put your main code here, to run repeatedly:
  int optoswitch = analogRead(A0);

  Serial.print(optoswitch);

  if (optoswitch > threshold){
    Serial.println(": WHITE");
  }
  else{
    Serial.println(": BLACK");
  }
  
  delay(100);
}
