#include "MIDIUSB.h"

const byte TOTAL_BUTTONS = 5;

const byte START_NOTE = 48;

const byte BUTTONS_PIN[TOTAL_BUTTONS] = {2, 3, 4, 7, 9};


byte currentRead[TOTAL_BUTTONS];

byte tempRead;


void setup() {

  for (byte i = 0; i < TOTAL_BUTTONS; i++) {
    pinMode(BUTTONS_PIN[i], INPUT_PULLUP);
  }
}


void loop() {
  for (byte i = 0; i < TOTAL_BUTTONS; i++) {
    byte buttonState = digitalRead(BUTTONS_PIN[i]);

    tempRead = buttonState;

    if (currentRead[i] != tempRead) {

      delay(2);

      byte pitch = START_NOTE + i;

      currentRead[i] = tempRead;

      if (buttonState == LOW) {
        noteOn(pitch);
      } else {
        noteOff(pitch);
      }
    }
  }
}

void noteOn(byte pitch) {
  MidiUSB.sendMIDI({0x09, 0x90, pitch, 127});
  MidiUSB.flush();
}

void noteOff(byte pitch) {
  MidiUSB.sendMIDI({0x08, 0x80, pitch, 0});
  MidiUSB.flush();
}
