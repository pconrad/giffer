// An Arduino Sketch

#include <arduino.h>

void setup() {
  int i;
  for (i=2; i<=15; i++)
    pinMode(i,OUTPUT);

}


void loop() {
  int i;
  for (i=2; i<=15; i++) {
    digitalWrite(i,HIGH);
    delay(500);
    digitalWrite(i,LOW);
    delay(250);
  }
}
