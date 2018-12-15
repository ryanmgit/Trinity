#define LED 2

void setup() {
  // Set pin mode
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(5000);
  digitalWrite(LED, HIGH);
  delay(5000);
  digitalWrite(LED, LOW);
}
