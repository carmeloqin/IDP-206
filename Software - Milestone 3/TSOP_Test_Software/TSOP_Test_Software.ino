int sensorPin = A0;    // select the input pin for the TSOP

int sensorValue = 0;  // variable to store the value coming from the sensor

int prev = 0;
bool state = false;
int delta_t = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(5, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue < 240 && state == false){
    prev = micros();
    state = true;
  }
  else if (sensorValue > 250 && state == true){
    delta_t = micros() - prev;
    Serial.println(delta_t);
    state = false;
  }
  //Serial.println(sensorValue);  
}
