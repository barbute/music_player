/*
 * ---
 * Class: CE 1202.004
 * Assignment: Semester Project
 *
 * Date: 2026-04-30
 * ---
 */

// https://github.com/hibit-dev/buzzer/blob/master/src/games/pacman/pacman.ino
// Retrieved 30 April 2026

#include "../util/Pitches.h"

const PROGMEM int PACMAN_NOTES[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
  NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
  
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
  NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
};

const PROGMEM int PACMAN_DURATIONS[] = {
  16, 16, 16, 16,
  32, 16, 8, 16,
  16, 16, 16, 32, 16, 8,
  
  16, 16, 16, 16, 32,
  16, 8, 32, 32, 32,
  32, 32, 32, 32, 32, 16, 8
};

const int PACMAN_LENGTH = sizeof(PACMAN_NOTES) / sizeof(PACMAN_NOTES[0]);