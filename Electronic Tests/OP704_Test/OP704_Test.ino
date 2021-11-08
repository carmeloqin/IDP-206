int optoswitch = 0;
int state = 0;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Serial.println("OP704 Test");

}

void loop() {
  // put your main code here, to run repeatedly:
  int optoswitch = analogRead(A0);

  Serial.print(optoswitch);

  if (optoswitch > 22){
    Serial.println(": WHITE");
  }
  else{
    Serial.println(": BLACK");
  }
  
  delay(100);
}
