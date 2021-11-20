bool state = false;
int prev_reading;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\t");
  pinMode(A0, INPUT);
  prev_reading = analogRead(A0);
}




void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println(analogRead(A0));

  
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
