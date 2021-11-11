int sensorPin = A0;    // select the input pin for the TSOP

int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(5, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);  
}
