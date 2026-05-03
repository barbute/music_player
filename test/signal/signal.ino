#include "Arduino.h"

const int OUTPUT_PORT = 9;
const int TEST_PORT = 3;
const int READ_PORT = A5;

void setup() {
  Serial.begin(9600);

  pinMode(OUTPUT_PORT, OUTPUT);
  pinMode(READ_PORT, INPUT);
  pinMode(TEST_PORT, OUTPUT);
}

void loop() {
  // tone(OUTPUT_PORT, 250);
  analogWrite(TEST_PORT, 250);

  Serial.println(analogRead(READ_PORT));

  delay(10);
}