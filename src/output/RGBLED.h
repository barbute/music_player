/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

struct ColorRGB{
  int red;
  int green;
  int blue;
};

// Pre-defined colors for the program
constexpr ColorRGB COLOR_GREEN = { 100, 191, 75 };
constexpr ColorRGB COLOR_ORANGE = { 242, 131, 34 };
constexpr ColorRGB COLOR_RED = { 242, 61, 61 };
constexpr ColorRGB COLOR_OFF = { 0, 0, 0 };

class RGBLED {
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;

  public:
    RGBLED(int redPin, int greenPin, int bluePin);
    void setColor(ColorRGB color);
};

#endif