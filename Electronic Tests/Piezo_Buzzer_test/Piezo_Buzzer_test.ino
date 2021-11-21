// create an array of notes
// frequencies of middle C, D, E, and F
int notes[] = {262, 294, 330, 349};

void setup() {
  //start serial communication
  Serial.begin(9600);
}

void loop() {

  for (int i=0; i<4; i++){
    tone(8, notes[i]);
    delay(1000);
  }
  noTone(8);
  delay(1000);
}
