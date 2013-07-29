#include <cstddef>
#include <vector>
#include <gif_lib.h>

using namespace std;

typedef unsigned char Byte;
typedef vector<GifByteType> Frame;


/*
  GifAnimator! 
  by Phill Conrad, based on AnimatedGifSaver by Marco Tarini
  
  This is a quick and dirty class. 
  At any given time, at most one instance of GifAnimator must exist!
   
*/


class GifAnimator{
public:
  
  // Constructor. Use a new instance for each new animation you want to save.
  // All the frames will be sized the same as the source frame
  GifAnimator(const char * const filename);

  // Destructor
  ~GifAnimator();

  // Saves the results in a gif file
  bool Save();

 private:

  GifFileType *gf;

  
};
