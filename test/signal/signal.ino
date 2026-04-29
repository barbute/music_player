const int OUTPUT_PORT = 4;

void setup() {
  pinMode(OUTPUT_PORT, OUTPUT);
}

void loop() {
  tone(OUTPUT_PORT, 250);
}