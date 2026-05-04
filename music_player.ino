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
#include "src/songs/Acat.h"

const int BUTTON_PLAY = 13;
const int BUTTON_PREV = 12;
const int BUTTON_NEXT = 11;
const int BUTTON_RAND = 10;

const int SPEAKER = 9;

const int LED_STATUS_RED = 6;
const int LED_STATUS_BLU = 3;
const int LED_STATUS_GRE = 5;

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
  SHUFFLE,
  // Skipping to next song
  NEXT,
  // Going back to previous song
  PREVIOUS,
  // Wait a second before going to next song
  WAIT
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

Song acatSong = { ACAT_NOTES, ACAT_DURATIONS, ACAT_LENGTH };
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

// State variable used to track the current index of the note in the song's
// notes array
int currentNoteIndex = 0;
// Temp vars for retrieving notes and durations from PROGMEM
int currentNote = 0;
int currentDuration = 0;

// State variable used to mark when a note started playing. Used to ensure the
// program is non-blocking
int noteStartTimeMS = 0;

const int WAIT_TIME_MS = 1000;
int waitStartTimeMS = 0;

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
  // Declare variable to store the new index
  int newSongIndex = 0;
  newSongIndex = getNextSong(currentSongIndex);

  // If at the end of the playlist, loop back to start...
  if (newSongIndex == 0) {
    Serial.println(newSongIndex);
    return newSongIndex;
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

int getNextSong(int currentSongIndexPlaylist) {
  // Save the current index of the song
  int savedIndex = currentSongIndexPlaylist;
  previousSongIndex = savedIndex;
  // Declare variable to store the new index
  int newSongIndex = 0;

  // If at the end of the playlist, loop back to start...
  if (savedIndex == PLAYLIST_LENGTH - 1) {
    newSongIndex = 0;
  } else {
    newSongIndex = savedIndex + 1;
  }

  return newSongIndex;
}

int getPreviousSong() {
  return previousSongIndex;
}

// Completely resets all state variables and clears audio output
void resetState() {
    // Stop playing when song is done
    noTone(SPEAKER);
    statusLight.setColor(COLOR_OFF);
    
    // Reset everything
    currentNoteIndex = 0;
    noteStartTimeMS = 0;
    waitStartTimeMS = 0;
    currentNote = 0;
    currentDuration = 0;
    finishedNote = true;
    isSongDone = false;
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

void next() {
  Serial.println("NEXT");
  currentState = NEXT;
}

void prev() {
  Serial.println("PREV");
  currentState = PREVIOUS;
}

void shuffle() {
  Serial.println("SHUFFLE");
  currentState = SHUFFLE;
}

void wait() {
  Serial.println("WAIT");
  currentState = WAIT;
}

// Define hardware down here to make compiler happy
Button playBtn(BUTTON_PLAY, play);
Button prevBtn(BUTTON_PREV, prev);
Button nextBtn(BUTTON_NEXT, next);
Button randBtn(BUTTON_RAND, shuffle);

void setup() {
  Serial.begin(9600);
  
  pinMode(SPEAKER, OUTPUT);

  // playlist[0] = acatSong;
  playlist[0] = marioSong;
  playlist[2] = pacmanSong;
  playlist[1] = tetrisSong;
}

void loop() {
  if (currentState == IDLE) {    
    // If the play/pause button is pressed, begin playing the song
    playBtn.poll();
    // If the shuffle button is pressed, shuffle and start playing
    randBtn.poll();
    // Poll prev/next just in case user presses them
    nextBtn.poll();
    prevBtn.poll();
    // Red indicator LED to tell user no audio is playing
    statusLight.setColor(COLOR_RED);

  } else if (currentState == PLAYING) {
    if (!isSongDone) {
      // If the note is done playing, run the following actions
      if (finishedNote) {
        currentSong = playlist[currentSongIndex];
        noteStartTimeMS = millis();
        currentNoteIndex++;

        // Print the current note for debugging
        // Serial.print("Note: ");
        // Serial.print(currentNoteIndex);
        // Serial.println();
        
        isSongDone = currentNoteIndex == currentSong.length;
        // Print if the song is finished for debugging
        // Serial.print("Is song done: ");
        // Serial.print(isSongDone);
        // Serial.println();

        // Pass ptr b/c that's the address to read from PROGMEM
        currentNote = pgm_read_word_near(&currentSong.notes[currentNoteIndex]);
        currentDuration = 
          pgm_read_word_near(&currentSong.duration[currentNoteIndex]);
        
        tone(SPEAKER, currentNote);

        // Tone is set, so turn on LED to indicate audio output
        statusLight.setColor(COLOR_GREEN);

        finishedNote = false;
      } 
      // If the note is currently playing, simply check to see if it has 
      // reached its duration
      else {
        isSongDone = currentNoteIndex >= currentSong.length;
        
        // Cast millis() to an integer since we wish to perform integer math on
        // it and millis() returns a long
        int timeMS = millis();

        // If the current time is less than the expected end time of the note,
        // keep playing the note
        if ((noteStartTimeMS + (1000 / currentDuration)) 
          >= timeMS) {

          playBtn.poll();
          randBtn.poll();
          nextBtn.poll();
          prevBtn.poll();
        }
        // Otherwise, the note has ended and go to the next note
        else {
          finishedNote = true;
        }
      }
    }
    // If the song is done, do the following: 
    else {
      waitStartTimeMS = millis();

      // GOTO wait
      wait();
    }
  } else if (currentState == PAUSED) {
    // Stop playing when paused
    noTone(SPEAKER);
    
    // Indicator to ORANGE to show paused state
    statusLight.setColor(COLOR_ORANGE);
    
    // If program is paused, simply poll buttons to await next input
    playBtn.poll();
    randBtn.poll();
    nextBtn.poll();
    prevBtn.poll();
  } else if (currentState == SHUFFLE) {
    resetState();

    currentSongIndex = getRandomSong(currentSongIndex);
    currentSong = playlist[currentSongIndex];
    
    // Start playing next song immediately
    play();
  } else if (currentState == NEXT) {
    resetState();

    currentSongIndex = getNextSong(currentSongIndex);
    currentSong = playlist[currentSongIndex];

    Serial.print("NOW PLAYING: ");
    Serial.println(currentSongIndex);

    play();
  } else if (currentState == PREVIOUS) {
    resetState();

    currentSongIndex = getPreviousSong();
    currentSong = playlist[currentSongIndex];

    Serial.print("NOW PLAYING: ");
    Serial.println(currentSongIndex);

    play();
  } else if (currentState == WAIT) {
    int timeMS = millis();

    statusLight.setColor(COLOR_BLUE);

    if ((waitStartTimeMS + WAIT_TIME_MS) <= timeMS) {
      // GOTO next once time has elapsed
      next();
    }
  }
}