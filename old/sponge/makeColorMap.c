/****************************************************************************

makeColorMap.c

Given an array of colors, make a color map containing those colors.

*/

#include "makeColorMap.h"

ColorMapObject * makeColorMap(HexColor colors[], int numColors) {

  if (numColors >= 256) {
    fprintf(stderr,
	    "%s %d: Too many colors (%d) in call to makeColorMap\n",
	    __FILE__,__LINE__,numColors);
    exit(1);
  }

  ColorMapObject* outputPalette = NULL;

  // First, allocate an image that is one pixel high, and
  // numColors pixels wide, and set it entirely to 0 (black).

  int size = sizeof(GifByteType) * numColors * 3;
  GifByteType *frame = (GifByteType *) malloc(sizeof(GifByteType) * numColors * 3);
  memset((void *) frame, 0, (size_t) size);
  
  // Now, set the colors up in the image.

  int i;
  for (i=0; i<numColors; i++) {
    frame[i*3 + 0] = EXTRACT_R(colors[i]);
    frame[i*3 + 1] = EXTRACT_G(colors[i]);
    frame[i*3 + 2] = EXTRACT_B(colors[i]);
  }
  
  // Now the frame contains the colors we want.  Set up a colormap.
  // We need the smallest power of two >=4, <=256 and >= numColors.
  
  int p;
  for (p=4; (p<256) && (p<numColors); p*=2)
    ; // this loop deliberately empty

  // post condition; either p is 256, or p >= numColors 
  // and we already established that 256 >= numColors,
  // so if p is 256, then p >= numColors must hold.

  int paletteSize = p;

  // The fake frame is the one that will get the assignment of the color indices
  // The r,g,b frames are ones that will contain the three layers (r,g,b)

  GifByteType *fakeFrame = (GifByteType *) malloc(sizeof(GifByteType) * numColors); 
  GifByteType *r = (GifByteType *) malloc(sizeof(GifByteType) * numColors); 
  GifByteType *g = (GifByteType *) malloc(sizeof(GifByteType) * numColors); 
  GifByteType *b = (GifByteType *) malloc(sizeof(GifByteType) * numColors); 

  // Separate out the colors into separate arrays.

  int j;
  for (i=0, j=0; i<numColors; i++){
    r[i]=frame[j++];
    g[i]=frame[j++];
    b[i]=frame[j++];
  }

  GifColorType *ScratchMap = 
    (GifColorType *) malloc(sizeof(GifColorType) * paletteSize);

  for (i=0; i<paletteSize; i++) {
      ScratchMap[i].Red = 0;
      ScratchMap[i].Green = 0;
      ScratchMap[i].Blue = 0;
    }
    
  outputPalette = GifMakeMapObject(paletteSize, ScratchMap);

  if (!outputPalette) return NULL;
  
  if (GifQuantizeBuffer(numColors, 1, &paletteSize, 
			&(r[0]),&(g[0]),&(b[0]), &(fakeFrame[0]), 
			outputPalette->Colors) == GIF_ERROR) return NULL;
  
  return outputPalette;

}
