const int outPin = 3;
const int timeHF = 12;

void setup() {
  pinMode(outPin, OUTPUT);
}

void loop() {
  int i = 0;
  int j = 0;
  for (i = 0; i < 5; i++ ) {
    delayMicroseconds(900);
    for (j = 0; j < 23; j++ ) { // ~600ms
      digitalWrite(outPin, HIGH);
      delayMicroseconds(timeHF);
      digitalWrite(outPin, LOW);
      delayMicroseconds(timeHF);
    } //total de 1100ms
  }
  /*
    delayMicroseconds(550);
    for (i = 0; i < 63; i++ ) { // ~1650ms
      digitalWrite(outPin, HIGH);
      delayMicroseconds(timeHF);
      digitalWrite(outPin, LOW);
      delayMicroseconds(timeHF);
    } //total de 2200ms
  */
  delay(5);
  //analogWrite(outPin, 127);
}
