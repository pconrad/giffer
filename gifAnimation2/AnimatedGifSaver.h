#include <cstddef>
#include <vector>
#include <gif_lib.h>

using namespace std;

typedef unsigned char Byte;

typedef vector<GifByteType> Frame;


/*
  AnimatedGifSaver! 
  by Marco Tarini
  
  A simple class to define simple looped animations
  and save them as gif.
  
  Usage: 
  Just include this file in your code and use the class. 
  Does not need to include giflib.
  Include gifSave.cpp in your project and link with -lgif
  
  This is a quick and dirty class. 
  At any given time, at most one instance of AnimatedGifSaver must exist!
   
*/

typedef unsigned char Byte;

class AnimatedGifSaver{
public:
  
  // Constructor. Use a new instance for each new animation you want to save.
  // All the frames will be sized [sx]X[sy]
  AnimatedGifSaver(int sx, int sy);

  // Constructor. Use a new instance for each new animation you want to save.
  // All the frames will be sized the same as the source frame
  AnimatedGifSaver(const char * const filename);

  // Destructor
  ~AnimatedGifSaver();

  bool FakeFrame(Byte* data); // fake frame that defines color palette
  // must contain all colors to be used.

  // Adds a frame that is to last [dt] seconds
  // "data" is the image (r,g,b,r,g,b,r,g,b...), bottom-to-top

  bool AddFrame(Byte* data,  float dt);

  // Saves the results in a gif file
  bool Save(const char* filename);

 private:

  std::vector<Frame> frames;
  std::vector<int> delay;
  
  ColorMapObject* outputPalette;
  
  int gifsx, gifsy;


  
};
