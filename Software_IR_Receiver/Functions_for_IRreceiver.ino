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
  //Serial.println(count);
  return count;
  //delay(500);

}

int dummyMode(){
  int modeAverage = 0;
  int modeSum = 0;
  int output;
  int repetition = 3;
  for ( int i = 0; i < repetition; i++){
    digitalnum = digitalCount();
    Serial.print("Digital Count:");
    Serial.println(digitalnum);
    modeSum = modeSum + digitalnum;
    }
  modeAverage = modeSum / repetition;
  Serial.println(modeAverage);
  if (modeAverage > 3000 && modeAverage < 4000){
    output = 0;
  }
  else if (modeAverage > 50 && modeAverage < 300){
    output = 1;
  }
  else if (modeAverage > 1400 && modeAverage < 2600){
    output = 2;
  }
  else {
    output = 3;
  }
  Serial.println(output);
  return output;
}
