// An Arduino Sketch

#include "arduino.h"

void setup() {
  pinMode(2,OUTPUT);

}


void loop() {
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  digitalWrite(3,HIGH);
  delay(1000);
  digitalWrite(3,LOW);
  delay(1000);

}
