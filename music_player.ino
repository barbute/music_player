/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Author: Jack Demeterio
 * Date: 2026-04-30
 * ---
 */

#include "src/input/Button.h"
#include "src/output/RGBLED.h"

const int BUTTON_PLAY = 13;
const int BUTTON_PREV = 12;
const int BUTTON_NEXT = 11;
const int BUTTON_RAND = 10;

Button playBtn(BUTTON_PLAY);
Button prevBtn(BUTTON_PREV);
Button nextBtn(BUTTON_NEXT);
Button randBtn(BUTTON_RAND);

const int SPEAKER = 7;

const int LED_STATUS_RED = 4;
const int LED_STATUS_BLU = 3;
const int LED_STATUS_GRE = 2;

RGBLED statusLight(LED_STATUS_RED, LED_STATUS_GRE, LED_STATUS_BLU);

const int AUDIO_MEAS = A5;

enum State {
  // "Do nothing"
  IDLE,
  // Playing a song
  PLAYING,
  // Waiting to continue current song
  PAUSED,
  // Randomizing play order. Will queue new song when done
  SHUFFLE
};

void setup() {
  Serial.begin(9600);
  // pinMode(BUTTON_PLAY, INPUT);
  // pinMode(BUTTON_PREV, INPUT);
  // pinMode(BUTTON_NEXT, INPUT);
  // pinMode(BUTTON_RAND, INPUT);
  
  pinMode(SPEAKER, OUTPUT);
  
  // pinMode(LED_STATUS_RED, OUTPUT);
  // pinMode(LED_STATUS_BLU, OUTPUT);
  // pinMode(LED_STATUS_GRE, OUTPUT);
}

void loop() {  
  // setStatusColor(COLOR_RED);
  // tone(SPEAKER, 250);
  
  // if (digitalRead(BUTTON_PLAY)) {
  //   setStatusColor(COLOR_OFF);
  //   noTone(SPEAKER);
  // }
  /*
  if (digitalRead(BUTTON_PLAY)) {
    setStatusColor(COLOR_RED);
    tone(SPEAKER, 250);
  } else {
    setStatusColor(COLOR_OFF);
    noTone(SPEAKER);
  }
  */
  
  // Serial.println(analogRead(AUDIO_MEAS));

  // statusLight.setColor(COLOR_GREEN);
  
  delay(10);
}