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

#include "src/songs/Mario.h"
#include "src/songs/Pacman.h"
#include "src/songs/Tetris.h"

const int BUTTON_PLAY = 13;
const int BUTTON_PREV = 12;
const int BUTTON_NEXT = 11;
const int BUTTON_RAND = 10;

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

// Data structure of a song. Each index in the notes array corresponds to the
// index in the duration array for how long that note should be played for.
struct Song {
  const int *notes; // Pointer to array of integers representing notes. The  
                    // array should consist of notes from `pitches.h`
  const int *duration; // Pointer to array of integers for how long each note
                       // should be played for. Should be in milliseconds.
  int length; // Length of the array, used for calculations
};

Song marioSong = { MARIO_NOTES, MARIO_DURATIONS, MARIO_LENGTH };
Song pacmanSong = { PACMAN_NOTES, PACMAN_DURATIONS, PACMAN_LENGTH };
Song tetrisSong = { TETRIS_NOTES, TETRIS_DURATIONS, TETRIS_LENGTH };

// The final amount of songs that can be on the playlist. This MUST be updated
// if more songs are expected to be added in setup()
const int PLAYLIST_LENGTH = 3;
// Create playlist of songs
Song* playlist = new Song[PLAYLIST_LENGTH];

// State variable used to track the current song (as an index in our playlist)
int currentSongIndex = 0;
// State variable used to track the last song played
int previousSongIndex = 0;

// State variable used to tell if the next played song should be random or not
bool randomNextSong = false;

// State variable used to track the current index of the note in the song's
// notes array
int currentNote = 0;

// State variable used to mark when a note started playing. Used to ensure the
// program is non-blocking
int noteStartTimeMS = 0;

// State variable that will be used to check if the note that is being played
// should be stopped and the next one queued
bool finishedNote = true;

// State variable used to check if the song is complete
bool isSongDone = false;

// Initialize with a default value
Song currentSong = playlist[currentSongIndex];

// Begin the music player in an "idle" state
enum State currentState = IDLE;

// Returns the index in the playlist of the song chosen at random
int getRandomSong(int currentSongIndexPlaylist) {
  // Save the current index of the song
  int savedIndex = currentSongIndexPlaylist;
  // Declare variable to store the new index
  int newSongIndex = 0;
  // If at the end of the playlist, loop back to start...
  if (savedIndex == PLAYLIST_LENGTH - 1) {
    newSongIndex = 0;
  }
  // ...otherwise try to generate a random index in the playlist for the next song
  else {
    // Try 1000 times to find a random song that doesn't match our current
    // song. If not, oh well we're playing the same song twice
    for (int i = 0; i < 1000; i++) {
      newSongIndex = (int) random(0, PLAYLIST_LENGTH);
      if (newSongIndex == currentSongIndexPlaylist) {
        continue;
      } else {
        break;
      }
    }
  }
  Serial.println(newSongIndex);
  return newSongIndex;
}

// Completely resets all state variables and clears audio output
void resetState() {
    // Stop playing when song is done
    noTone(SPEAKER);
    statusLight.setColor(COLOR_OFF);
    
    // Reset everything
    currentNote = 0;
    noteStartTimeMS = 0;
    finishedNote = true;
    isSongDone = false;
    randomNextSong = false;
}

// These functions are to be used within the button lambda functions; they need
// to be able to set variables without capturing them in the scope of the
// lambda. Thus the program instead calls these methods.

void idle() {
  Serial.println("IDLE");
  currentState = IDLE;
}

void play() {
  if (currentState == PLAYING) {
    Serial.println("PAUSED");
    currentState = PAUSED;
  } else {
    Serial.println("PLAYING");
    currentState = PLAYING;
  }
}

void pause() {
  Serial.println("PAUSED");
  currentState = PAUSED;
}

// TODO Add this logic 
void prev() {

}

void next() {

}

void shuffle() {
  Serial.println("SHUFFLE");
  currentState = SHUFFLE;
}

// Define hardware down here to make compiler happy
Button playBtn(BUTTON_PLAY, play);
Button prevBtn(BUTTON_PREV, prev);
Button nextBtn(BUTTON_NEXT, next);
Button randBtn(BUTTON_RAND, shuffle);

void setup() {
  Serial.begin(9600);
  
  pinMode(SPEAKER, OUTPUT);

  playlist[0] = marioSong;
  playlist[1] = pacmanSong;
  playlist[2] = tetrisSong;
}

void loop() {

}