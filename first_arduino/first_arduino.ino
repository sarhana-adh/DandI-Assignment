#define LED 10

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  //this is my change
  digitalWrite(LED, HIGH);
}
