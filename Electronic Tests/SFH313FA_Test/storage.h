int d;
int prev_reading;
bool state = false;

int analogReadDerivative() {
  int _read = analogRead(A0);
  d = _read - prev_reading;
  prev_reading = _read;
  return d;
}

void analogCodeBigSmall() {

  int count = 0;
  int smallcount = 0;
  int prevtime = millis();
  while (millis() - prevtime < 1000){
    while (analogRead(A0)> 200){
        int prev = analogRead(A0);
        if (analogRead(A0) > prev){
          state = true;
        }
        if (analogRead(A0) < prev){ 
          state = false;
          smallcount += 1;
        }
      }
    while (analogRead(A0)< 200){}
    count += 1;
  }
  Serial.print(count);
  Serial.print('\t');
  Serial.println(smallcount);
}

void digitalCode(){
    //Serial.println(digitalRead(2));

  int count = 0;
  int prevtime = millis();
  bool state = false;
  while (millis() - prevtime <= 100){ // rollover issue to solve
    if (digitalRead(2)== HIGH && state == false){
      state = true;
    }
    if (digitalRead(2)== LOW && state == true){
      state = false;
      count += 1;  
    }
  }
  Serial.println(count);
  //delay(500);

}


void analogCode(){

  int count = 0;
  int prevtime = millis();
  bool state = false;
  while (millis() - prevtime <= 1000){ // rollover issue to solve
    if (analogRead(A0) > 500 && state == false){
      state = true;
    }
    if (analogRead(A0) < 500 && state == true){
      state = false;
      count += 1;  
    }
  }
  Serial.println(count);
  delay(500);

}
