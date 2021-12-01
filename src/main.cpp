#include <Arduino.h>

#define CHANNELS_COUNT 8

// Pin mapping
#define Ch1 53
#define Ch2 51
#define Ch3 49
#define Ch4 47
#define Ch5 45
#define Ch6 43
#define Ch7 41
#define Ch8 39

#define OFF HIGH
#define ON LOW

#define SERIAL_BAUD_RATE 57600

#define ON_THRESHOLD 127 // Sainsmart relays are simple and only do off and on.

int Channels[CHANNELS_COUNT] = {Ch1, Ch2, Ch3, Ch4, Ch5, Ch6, Ch7, Ch8};
int incomingByte[CHANNELS_COUNT];   // array to store the values from serial port


void setAll(int val) {
  for (int i = 0; i < CHANNELS_COUNT; i++) {
    digitalWrite(Channels[i], val);
  }
}

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  for (int i = 0; i < CHANNELS_COUNT; i++) {
    pinMode(Channels[i], OUTPUT);
  }

  setAll(OFF);

  // Power on self test.
  for (int i = 0; i < CHANNELS_COUNT; i++) {
    digitalWrite(Channels[i], LOW);
    delay(500);
    digitalWrite(Channels[i], HIGH);
  }

  setAll(ON);
  delay(500);
  setAll(OFF);
}

void loop() {
  if (Serial.available() >= CHANNELS_COUNT) {
    for (int i = 0; i < CHANNELS_COUNT; i++) {
      incomingByte[i] = Serial.read(); // read each byte
      int value = incomingByte[i];
      int digitalValue = value <= ON_THRESHOLD ? ON : OFF; // Convert bytes to HIGH/LOW
      digitalWrite(Channels[i], digitalValue);
    }
  }
}
