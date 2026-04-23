const int BUTTON_PLAY = 13;
const int BUTTON_PREV = 12;
const int BUTTON_NEXT = 11;
const int BUTTON_RAND = 10;

const int SPEAKER = 7;

const int LED_STATUS_RED = 4;
const int LED_STATUS_BLU = 3;
const int LED_STATUS_GRE = 2;

const int AUDIO_MEAS = A5;

struct ColorRGB{
  int red;
  int green;
  int blue;
};

ColorRGB COLOR_GREEN = { 100, 191, 75 };
ColorRGB COLOR_ORANGE = { 242, 131, 34 };
ColorRGB COLOR_RED = { 242, 61, 61 };
ColorRGB COLOR_OFF = { 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_PLAY, INPUT);
  pinMode(BUTTON_PREV, INPUT);
  pinMode(BUTTON_NEXT, INPUT);
  pinMode(BUTTON_RAND, INPUT);
  
  pinMode(SPEAKER, OUTPUT);
  
  pinMode(LED_STATUS_RED, OUTPUT);
  pinMode(LED_STATUS_BLU, OUTPUT);
  pinMode(LED_STATUS_GRE, OUTPUT);
}

void setStatusColor(struct ColorRGB color) {
  analogWrite(LED_STATUS_RED, color.red);
  analogWrite(LED_STATUS_GRE, color.green);
  analogWrite(LED_STATUS_BLU, color.blue);
}

void loop() {  
  setStatusColor(COLOR_RED);
  tone(SPEAKER, 250);
  
  if (digitalRead(BUTTON_PLAY)) {
    setStatusColor(COLOR_OFF);
    noTone(SPEAKER);
  }
  /*
  if (digitalRead(BUTTON_PLAY)) {
    setStatusColor(COLOR_RED);
    tone(SPEAKER, 250);
  } else {
    setStatusColor(COLOR_OFF);
    noTone(SPEAKER);
  }
  */
  
  Serial.println(analogRead(AUDIO_MEAS));
  
  delay(10);
}