int modeType;
int red_LED = 0;
int green_LED = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(0, OUTPUT); //Red LED pin
  pinMode(1, OUTPUT); //Green LED pin
  pinMode(2, INPUT); // digital pin
}

void loop() {
  // put your main code here, to run repeatedly:
  modeType = dummyMode();
  if (modeType = 0){
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, HIGH);
  }
  else if (modeType = 1){
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, LOW);    
  }
  else if (modeType = 2){
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, HIGH);    
  }
  else{
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW); 
  }
}
