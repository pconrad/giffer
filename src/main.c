#include "giffer.h"
#include <stdio.h>

int main() {

  fprintf(stderr,"Calling setup()\n");

  setup();

  fprintf(stderr,"Calling loop()\n");

  loop();

  fprintf(stderr,"After loop()\n");
  
  return 0;
}
