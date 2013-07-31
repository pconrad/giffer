// giffer is a package to create animated GIFs from Arduino Sketches
//   for the DPEA Light Prototype Board
// P. Conrad, July 2013, UC Santa Barbara

// arduino.c

#include "arduino.h"

struct ArduinoGlobals_S {
  uint8_t pinModes[NUM_DIGITAL_PINS]; 
  uint8_t pinState[NUM_DIGITAL_PINS]; 
  unsigned long millis;
} arduinoGlobals;

void initArduinoGlobals() {
  // all pins are initially in the INPUT state
  
  int i;
  for (i=0;i<NUM_DIGITAL_PINS;i++) {
    arduinoGlobals.pinModes[i] = INPUT;
    arduinoGlobals.pinState[i] = LOW;
  }

  arduinoGlobals.millis = 0;
}

  
void init(void) {

}

void pinMode(uint8_t pin, uint8_t mode) {
  arduinoGlobals.pinModes[pin]=mode;
};
void digitalWrite(uint8_t pin, uint8_t state) {
  arduinoGlobals.pinState[pin]=state;
}

unsigned long millis(void) { 
  return arduinoGlobals.millis;
}

void delay(unsigned long delayMs) {
  arduinoGlobals.millis += delay;
}

