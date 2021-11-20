int analogReadDerivative() {
  int _read = analogRead(A0);
  d = _read - prev_reading;
  prev_reading = _read;
  return d;
}

int countSmall() {
  
}
