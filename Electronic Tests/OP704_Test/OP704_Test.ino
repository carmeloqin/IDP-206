/* OP704 Test
See website: https://forum.arduino.cc/t/opb704/286564/4
Use the circuit diagram in website;
1k for the IR LED pull down resistor.
10k  for the pull down resistor on the LDR.

Signal connected to A0 for testing purposes, 
probs will go through comparator and provide a digital signal
on the final circuit board.
*/

int opto0 = 0;
int opto1 = 0;
int opto2 = 0;
int opto3 = 0;
int state = 0;
int threshold = 23;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
  Serial.println("OP704 Test");

}

void loop() {
  // put your main code here, to run repeatedly:
  int opto0 = analogRead(A4);
  int opto1 = analogRead(A3);
  int opto2 = analogRead(A4);
  int opto3 = analogRead(A5);

  Serial.println(opto2);
//  Serial.print('\t');
//  Serial.print(opto1);
//  Serial.print('\t');
//  Serial.print(opto2);
//  Serial.print('\t');
//  Serial.println(opto3);
  //Serial.println(opto2);
  
  delay(100);
}
