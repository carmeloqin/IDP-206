int modeType;
//int red_LED = 3;
//int green_LED = 4;
#define red_LED 3
#define green_LED 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(red_LED, OUTPUT); //Red LED pin
  pinMode(green_LED, OUTPUT); //Green LED pin
  pinMode(2, INPUT); // digital pin
}

void loop() { 
  // put your main code here, to run repeatedly:
  modeType = dummyMode();
  if (modeType == 0){
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, HIGH);
    delay(1000);
  }
  else if (modeType == 1){
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, LOW);  
    delay(1000);
  }
  else if (modeType == 2){
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, HIGH);  
    delay(1000);  
  }
  else{
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW); 
    delay(1000);
  }
}
