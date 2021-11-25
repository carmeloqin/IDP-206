/* OP704 Test
See website: https://forum.arduino.cc/t/opb704/286564/4
Use the circuit diagram in website;
1k for the IR LED pull down resistor.
10k  for the pull down resistor on the LDR.

Signal connected to A0 for testing purposes, 
probs will go through comparator and provide a digital signal
on the final circuit board.
*/


void setup() {
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  //pinMode(A2, INPUT);
  Serial.begin(9600);
  Serial.println("OP704 Test");

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(analogRead(A2));
  Serial.print('\t');
  Serial.print(analogRead(A3));
  Serial.print('\t');
  Serial.print(analogRead(A4));
  Serial.print('\t');
  Serial.println(analogRead(A5));

  
  delay(100);
}
