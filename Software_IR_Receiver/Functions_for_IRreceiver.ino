int digitalnum;

int digitalCount(){
    //Serial.println(digitalRead(2));

  int count = 0;
  unsigned long prevtime = millis();
  bool state = false;
  int pin2val;
  while (millis() - prevtime <= 1000){ // rollover issue to solve
    pin2val = digitalRead(2);
    if (pin2val == HIGH && state == false){
      state = true;
    }
    if (pin2val == LOW && state == true){
      state = false;
      count += 1;  
    }
  }
  Serial.println(count);
  return count;
  //delay(500);

}

int dummyMode(){
  int modeAverage = 0;
  int modeSum = 0;
  for ( int i = 0; i <= 9; i++){
    digitalnum = digitalCount();
    modeSum = modeSum + digitalnum;
    }
  modeAverage = modeSum / 10;
  if (modeAverage > 3000 && modeAverage < 4000){
    return 0;
  }
  else if (modeAverage > 50 && modeAverage < 300){
    return 1;
  }
  else if (modeAverage > 1400 && modeAverage < 2600){
    return 2;
  }
  else {
    return 3;
  }
}
