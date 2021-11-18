bool led_state = true;

void setup() {
     pinMode(NINA_RESETN, OUTPUT);         
     digitalWrite(NINA_RESETN, LOW);
     
     Serial.begin(115200);
     SerialNina.begin(115200);

     pinMode(2, OUTPUT);
     digitalWrite(2, HIGH);
}

void loop() {
  if (Serial.available()) {
  SerialNina.write(Serial.read());}
  if (SerialNina.available()) {
  Serial.write(SerialNina.read());}

//  if (SerialNina.available()) {
//    if (led_state = true){
//      digitalWrite(2, LOW);
//      led_state = false;
//    }
//    else {
//      digitalWrite(2, HIGH);
//      led_state = true;
//    }
//    delay(100);
//  }

  
  
}
