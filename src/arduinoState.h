// giffer is a package to create animated GIFs from Arduino Sketches
//   for the DPEA Light Prototype Board
// P. Conrad, July 2013, UC Santa Barbara

// arduino.c

#ifndef _ARDUINO_STATE_H
#define _ARDUINO_STATE_H

#include "arduino.h"
#include <stdio.h>

struct ArduinoState_S {
  uint8_t pinMode[NUM_DIGITAL_PINS]; 
  uint8_t pinState[NUM_DIGITAL_PINS]; 
  unsigned long millis;
  struct ArduinoState_S *next;
};

struct ArduinoSequence_S {
  struct ArduinoState_S *head;
  struct ArduinoState_S *curr; // tail--also "current state"
};

// GLOBALS

extern struct ArduinoSequence_S *ss;


// [INPUT]            [OUTPUT]


char lednumToColorChar(struct ArduinoState_S *s, int led);

const char * pinToModeString(struct ArduinoState_S *s, int pin);

const char * pinToStateString(struct ArduinoState_S *s, int pin);
void dumpTwoLEDsState(struct ArduinoState_S *s, int led1, int led2);
void dumpArduinoState(struct ArduinoState_S *s);
struct ArduinoState_S *newArduinoState();
struct ArduinoSequence_S *newArduinoSequence();



void initArduinoSequence();

void dumpArduinoSequence();
struct ArduinoState_S * copyOfArduinoStateWithDelayOffset
(
 struct ArduinoState_S *orig,
 unsigned long delayOffset
 );

// Actual arduino.h funcs

/*
void init(void);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t state);
unsigned long millis(void);
void delay(unsigned long delayMs);
*/

#endif
