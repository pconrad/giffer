#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

/*
Example of usage of AnimatedGifSaver class.
Saves a small looped 0-1-2-3 animation in file "0123.gif".
*/

#include "AnimatedGifSaver.h"


// red and white RGB pixels
#define R 255,0,0
#define W 0,255,0


// Lets define a few frames for this little demo...

// ...red and white RGB pixels
#define R 255,0,0
#define W 0,255,0

// ...frames sizes
const int  SX=5;
const int  SY=7;

// ...and, the frames themselves
// (note: they are defined bottom-to-top (a-la OpenGL) so they appear upside-down).

Byte palette[SX*SY*3] ={0};

Byte frame0[SX*SY*3] ={0};
Byte frame1[SX*SY*3] = {0};
Byte frame2[SX*SY*3]={0};
Byte frame3[SX*SY*3]={0};
Byte frame4[SX*SY*3]={0};
Byte frame5[SX*SY*3]={0};
Byte frame6[SX*SY*3]={0};
Byte frame7[SX*SY*3]={0};

void fillFrame(Byte *frame, int w, int h, int r, int g, int b) {
  int i=0;
  
  while (i<w*h*3) {
    frame[i] = r; frame[i+1] = g; frame[i+2] = b;
    i+=3;
  }

}


void fillFakeFrame(Byte *frame, int w, int h) {
  int i=0;
  
  while (i<w*h*3) {
    frame[i] = 0; frame[i+1] = 0; frame[i+2] = 0; // Black
    i+=3;
  }

  frame[0] = 255; frame[1]=0; frame[2]=0;  // Red
  frame[3] =   0; frame[4]=255; frame[5]=0;  // Green
  frame[6] =   0; frame[7]=0; frame[8]=255;  // Blue
  frame[9] = 255; frame[10]=255; frame[11]=255; // White
  frame[12] = 255; frame[13]=255; frame[14]=0;  // Yellow
  frame[15] =  0; frame[16]=255; frame[17]=255; // Cyan
  frame[18] = 255; frame[19]=0; frame[20]=255; // Magenta
  
}

int main()
{
  cout << "Before saver" << endl;

  AnimatedGifSaver saver(SX,SY);

  cout << "After saver" << endl;
  
  fillFakeFrame(palette,SX,SY);

  cout << "Before Fake Frame" << endl;

  saver.FakeFrame(palette); // first frame defines color palette

  cout << "After Fake Frame" << endl;

  fillFrame(frame0,SX,SY,255,  0,  0);
  fillFrame(frame1,SX,SY,  0,255,  0);
  fillFrame(frame2,SX,SY,  0,  0,255);
  fillFrame(frame3,SX,SY,255,255,  0);
  fillFrame(frame4,SX,SY,  0,255, 255);
  fillFrame(frame5,SX,SY,255,  0,  255);
  fillFrame(frame6,SX,SY,255,255,  255);
  fillFrame(frame6,SX,SY,  0,  0,   0);

  saver.AddFrame(frame0,0.5); // first frame: three secs
  saver.AddFrame(frame1,0.5); // first frame: one and half secs
  saver.AddFrame(frame2,0.5); // first frame: one and half secs
  saver.AddFrame(frame3,0.5); // first frame: one and half secs
  saver.AddFrame(frame4,0.5); // first frame: one and half secs
  saver.AddFrame(frame5,0.5); // first frame: one and half secs
  saver.AddFrame(frame6,0.5); // first frame: one and half secs
  saver.AddFrame(frame7,0.5); // first frame: one and half secs

  cout << "Before Save" << endl;

  saver.Save("0123.gif");
}
