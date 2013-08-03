#include "giffer.h"
#include <stdio.h>

int main() {
  
  initArduinoSequence();

  fprintf(stderr,"Calling setup()\n");

  setup();

  fprintf(stderr,"Calling loop()\n");

  loop();

  fprintf(stderr,"After loop()\n");
  
  dumpArduinoSequence();

  return 0;
}
