
int sensorPin = A0;    // select the input pin for the TSOP
int OutputPin = A1;
int pot = A2;
int sensorValue = 0;  // variable to store the value coming from the sensor
int PhotoTransistorPin = A5;
int FilterPin = A3;
int OutputPinOutput;
int FilterPinOutput;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600); 
  pinMode(5, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  //pinMode(A2, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  OutputPinOutput = analogRead(OutputPin);
  FilterPinOutput = analogRead(FilterPin);
  //Serial.println(digitalRead(5));
 //Serial.print(OutputPinOutput);  
 //Serial.print('\t');
  Serial.println(FilterPinOutput);
  //Serial.print('\t');
  //Serial.println(analogRead(InputPin)-analogRead(OutputPin));
  //Serial.print(analogRead(A0));
  //Serial.print('\t');
  //Serial.println(analogRead(A2));
  //Serial.println(analogRead(PhotoTransistorPin));
}
