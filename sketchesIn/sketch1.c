// An Arduino Sketch

#include "arduino.h"

void setup() {
	pinMode(3,OUTPUT);
	pinMode(4, OUTPUT);
}

void loop() {
	digitalWrite(3,HIGH);
	delay(1000);
	digitalWrite(3,LOW);
	digitalWrite(4, HIGH);
	delay(500);
}
