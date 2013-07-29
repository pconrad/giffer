/*
Example of usage of GifAnimator class.
Saves a small looped 0-1-2-3 animation in file "0123.gif".
*/

#include "GifAnimator.h"


int main()
{
  GifAnimator reader("../gifs/leds.gif");

  reader.Save();
}
