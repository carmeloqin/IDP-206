// NB Using 190R RD, 4k7 RL. All this code does is reads the (digital) output pin of the photointerruptor - very simple.
const int outputPin = 5; // Output port of the photointerruptor 

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  pinMode(outputPin,INPUT);
  Serial.print(digitalRead(outputPin)); // Output to Serial - 0 = Light not blocked, 1 = Blocked
  Serial.println();
  delay(50);
}
