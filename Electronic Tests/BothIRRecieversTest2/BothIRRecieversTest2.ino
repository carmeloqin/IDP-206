#include <SharpIR.h>
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int sensorPin = A0;    // select the input pin for the 2Y0A21
int sensorPin1 = A1;   // for 2Y0A02

int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;
int distance_1;
int distance_2;

SharpIR Sensor0 = SharpIR(sensorPin, 1080);
SharpIR Sensor1 = SharpIR(sensorPin1, 20150);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  }

// the loop function runs over and over again forever
void loop() {
  distance_1 = Sensor0.distance();
  distance_2 = Sensor1.distance();
  long distance_ultra, duration;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance_ultra = microsecondsToCentimeters(duration);
  Serial.print("      Distance Ultrasonic: ");
  Serial.print(distance_ultra);
  Serial.print("      IR Distance 1( A21): ");
  Serial.print(distance_1);
  Serial.print("      IR Distance 2 (A02): ");
  Serial.println(distance_2);
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2; 
}
