// giffer is a package to create animated GIFs from Arduino Sketches
//   for the DPEA Light Prototype Board
// P. Conrad, July 2013, UC Santa Barbara

// arduino.c

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

struct ArduinoSequence_S *ss;


// [INPUT]            [OUTPUT]


char lednumToColorChar(struct ArduinoState_S *s, int led) {
  const char ledColors[2][NUM_DIGITAL_PINS+1] = 
    {"xxrgrgrgrooobbyy","XXRGRGRGROOOBBYY"};
  if ( (s->pinMode[led] == INPUT) || (s->pinMode[led] == OUTPUT )) {
    if (s->pinState[led] == LOW) return '_';
    if (s->pinState[led] == HIGH) return ledColors[s->pinMode[led]][led];
  }
  fprintf(stderr,"ERROR: led=%d s->pinMode[%d]=%d s->pinState[%d]=%d\n",
	  led, led, s->pinMode[led], led, s->pinState[led]);
  return '?';
}

const char * pinToModeString(struct ArduinoState_S *s, int pin) {
  if (s->pinMode[pin] == INPUT) return "INPUT";
  if (s->pinMode[pin] == OUTPUT) return "OUTPUT";
  return "MODE??";
}

const char * pinToStateString(struct ArduinoState_S *s, int pin) {
  if (s->pinState[pin] == HIGH) return "HIGH";
  if (s->pinState[pin] == LOW) return "LOW";
  return "ST??";
}

void dumpTwoLEDsState(struct ArduinoState_S *s, int led1, int led2) {

  char led1char = 	  lednumToColorChar(s,led1);
  char led2char = 	  lednumToColorChar(s,led2);

  const char * const pin1ms = 	  pinToModeString(s,led1);
  const char * const pin2ms = 	  pinToModeString(s,led2);

  const char * const pin1ss = 	  pinToStateString(s,led1);
  const char * const pin2ss = 	  pinToStateString(s,led2);
  
  fprintf(stderr,
	  "| [%2d] %c [%6s,%4s]    [%6s,%4s] %c [%2d] |\n",
	  led1, led1char, pin1ms, pin1ss,
	  pin2ms, pin2ss, led2char, led2);

}
	  


void dumpArduinoState(struct ArduinoState_S *s) {

  fprintf(stderr,"+----------------------------------------------+\n",s->millis);
  fprintf(stderr,"|              millis=%10lu               |\n",s->millis);
  //         "| [15] R [OUTPUT,HIGH]    [OUTPUT,HIGH] g [ 8] |\n");
  //         "| [14] R [OUTPUT,HIGH]    [OUTPUT,HIGH] g [ 7] |\n");
  //          ...
  dumpTwoLEDsState(s, 15, 8);
  dumpTwoLEDsState(s, 14, 7);
  dumpTwoLEDsState(s, 13, 6);
  dumpTwoLEDsState(s, 12, 5);
  dumpTwoLEDsState(s, 11, 4);
  dumpTwoLEDsState(s, 10, 3);
  dumpTwoLEDsState(s,  9, 2);
}

void initArduinoGlobals(struct ArduinoState_S *s) {
  // all pins are initially in the INPUT state
  
  int i;
  for (i=0;i<NUM_DIGITAL_PINS;i++) {
    s->pinMode[i] = INPUT;
    s->pinState[i] = LOW;
  }

  s->millis = 0;
}

struct ArduinoState_S *newArduinoState() {
  struct ArduinoState_S *s =
    (struct ArduinoState_S *)
    malloc (sizeof(struct ArduinoState_S));
  initArduinoGlobals(s);
  return s;
}


// Initial allocation has one frame with default state

struct ArduinoSequence_S *newArduinoSequence() {
  struct ArduinoSequence_S *ss =
    (struct ArduinoSequence_S *)
    malloc (sizeof(struct ArduinoSequence_S));
  (ss->head) = (ss->curr) = newArduinoState();  
  return ss;
}



void initArduinoSequence() {
  // initialize global variable ss
  ss = newArduinoSequence();
}

void dumpArduinoSequence() {
  // dump, for debugging, the entire sequence of Arduino states.
  int i;
  struct ArduinoState_S *s;
  for (s= ss->head; s!=NULL; s=s->next) {
    dumpArduinoState(s);
  }
}

// copy of an ArduinoState_S, with delayOffset added

struct ArduinoState_S *copyOfArduinoStateWithDelayOffset 
(
 struct ArduinoState_S *orig,
 unsigned long delayOffset)
{
  struct ArduinoState_S *s =
    (struct ArduinoState_S *)
    malloc (sizeof(struct ArduinoState_S));
  int i;
  for (i=0;i<NUM_DIGITAL_PINS;i++) {
    s->pinMode[i] = orig->pinMode[i];
    s->pinState[i] = orig->pinState[i];
  }
  s->millis = orig->millis + delayOffset;
  s->next = NULL;
  return s;
}


  
void init(void) {

}

void pinMode(uint8_t pin, uint8_t mode) {
  ss->curr->pinMode[pin]=mode;
};

void digitalWrite(uint8_t pin, uint8_t state) {
  ss->curr->pinState[pin]=state;
}

unsigned long millis(void) { 
  return ss->curr->millis;
}

void delay(unsigned long delayMs) {
  
  // Make curr's next (next from current last state in list) 
  // point to new state (with delay offset)

  ss->curr->next = copyOfArduinoStateWithDelayOffset (ss->curr,delayMs);

  // Make that state the current state.
  ss->curr = ss->curr->next;

}

