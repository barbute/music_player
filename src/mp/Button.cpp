/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#include "Button.h"

Button::Button(int pin) {
  _pin = pin;
}

void Button::poll(void (*action)()) {
  int currentTimeMS = millis();
  
  // Wait on release of button before allowing for normal polling
  if (_waitOnRelease) {
    if (!getState()) {
      _waitOnRelease = false;
    }
    // Exit poll if not yet released
    return;
  }
  
  if (!_waitOnPoll) {
    if (getState()) {
      _startTimeMS = currentTimeMS;
      _waitOnPoll = true;
    }     
  } else {
    // Once current time surpasses debounce time...
    if ((_startTimeMS + _debounceThresholdMS) <= currentTimeMS) {
      _waitOnPoll = false;
      _startTimeMS = 0;
      if (getState()) {
        // Set state to waiting on button release before being able to 
        // fire action again (prevents double-firing)
        _waitOnRelease = true;
        Serial.print(_pin);
        Serial.print(" Polled:\n");
        action();
      } else {
        Serial.print(_pin);
        Serial.println(" Not polled");
      }
    }
  }
}

int Button::getState() {
  return digitalRead(_pin);
}