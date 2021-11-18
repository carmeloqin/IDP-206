void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //delay(1);
  
  float a0 = analogRead(A0);
  //float a1 = 1023 - analogRead(A1);
  //float a2 = analogRead(A2);
  //float a3 = analogRead(A3);
  //float a4 = analogRead(A4);
  //float a5 = analogRead(A5);


  Serial.println(a0);
  //Serial.print("\t");

  //Serial.println(a1);
  //Serial.print("\t");
/*
  Serial.print(a2);
  Serial.print("\t");

  Serial.print(a3); 
  Serial.print("\t");

  Serial.print(a4);
  Serial.print("\t");

  Serial.println(a5);
  Serial.println("\t");
*/

}
