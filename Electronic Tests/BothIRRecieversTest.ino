int sensorPin = A0;    // select the input pin for the TSOP
int sensorPin1 = A1;

int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  }

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print(sensorValue);  
  Serial.print("\t");              //seperator
  Serial.println(analogRead(sensorPin1));  

}
