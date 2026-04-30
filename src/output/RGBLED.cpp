/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#include "RGBLED.h"

RGBLED::RGBLED(int redPin, int greenPin, int bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void RGBLED::setColor(struct ColorRGB color) {
  analogWrite(_redPin, color.red);
  analogWrite(_greenPin, color.green);
  analogWrite(_bluePin, color.blue);
}