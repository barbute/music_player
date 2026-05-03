/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  private:
    int _pin;
    void (*_action)();
    int _startTimeMS;
  	int _debounceThresholdMS = 50;
  	bool _waitOnPoll = false;
  	bool _waitOnRelease = false;

  public:
    Button(int pin, void (*action)());

    void poll();

    int getState();
};

#endif