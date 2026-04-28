/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-05-28
 * Description: Sketch that can be deployed to the Arduino to ensure that the
 *              deploy process works.
 * ---
 */

const int SCALE_TIME = 3;

const int DOT_MS = 50 * SCALE_TIME;
const int DASH_MS = 100 * SCALE_TIME;
const int BREAK_MS = 50 * SCALE_TIME;
const int WORD_BREAK_MS = 100 * SCALE_TIME;

const int LED = LED_BUILTIN;

void setup() {
  pinMode(LED, OUTPUT);
}

void dot() {
  digitalWrite(LED, HIGH);
  delay(DOT_MS);
  digitalWrite(LED, LOW);
  delay(BREAK_MS);
}

void dash() {
  digitalWrite(LED, HIGH);
  delay(DASH_MS);
  digitalWrite(LED, LOW);
  delay(BREAK_MS);
}

void loop() {
  // Blink "hello world" to board

  dot();
  dot();
  dot();
  dot();

  dot();

  dot();
  dash();
  dot();
  dot();

  dot();
  dash();
  dot();
  dot();

  dash();
  dash();
  dash();

  delay(WORD_BREAK_MS);

  dot();
  dash();
  dash();

  dash();
  dash();
  dash();

  dot();
  dash();
  dot();

  dot();
  dash();
  dot();
  dot();

  dash();
  dot();
  dot();

  delay(WORD_BREAK_MS);
}