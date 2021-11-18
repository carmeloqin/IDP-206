int sensorPin = A0;    // select the input pin for the TSOP
int OutputPin = A1;
int pot = A2;
int sensorValue = 0;  // variable to store the value coming from the sensor
int PhotoTransistorPin = A5;
int InputPin = A3;

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
  Serial.print(analogRead(OutputPin));  
  Serial.print('\t');
  Serial.println(analogRead(InputPin));
  //Serial.print('\t');
  //Serial.println(analogRead(InputPin)-analogRead(OutputPin));
  //Serial.print(analogRead(A0));
  //Serial.print('\t');
  //Serial.println(analogRead(A2));
  //Serial.println(analogRead(PhotoTransistorPin));
}
