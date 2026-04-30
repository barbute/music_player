/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  private:
    int _pin;
    int _startTimeMS;
  	int _debounceThresholdMS = 500;
  	bool _waitOnPoll = false;
  	bool _waitOnRelease = false;

  public:
    Button(int pin);

    void poll(void (*action)());
    
    int getState();
};

#endif