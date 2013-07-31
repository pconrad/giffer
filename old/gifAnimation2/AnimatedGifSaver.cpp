

#include <stdio.h>
#include <cstdlib>
#include <iostream>

#include <vector>

using namespace std;


#include "AnimatedGifSaver.h"

// global vairables


AnimatedGifSaver::AnimatedGifSaver(int sx, int sy){
  outputPalette = NULL;
  gifsx=sx;
  gifsy=sy;

  frames.clear();
  delay.clear();
}

AnimatedGifSaver::AnimatedGifSaver(const char * const filename){


  outputPalette = NULL;

  // The following functions are used to set up input from a GIF:

  int error;

  GifFileType *gf = DGifOpenFileName(filename, &error);
  
  if (gf==NULL) {
    std::cerr << "Error: " << error << endl;
    exit(1);
  }
  
  if (DGifSlurp(gf) != GIF_OK) {
    std::cerr << "Error: DGifSlurp returned error status "  << endl;
    exit(2);
  }

  frames.clear();
  delay.clear();
}

AnimatedGifSaver::~AnimatedGifSaver(){
  frames.clear();
  delay.clear();
}

bool AnimatedGifSaver::AddFrame(Byte* data, float dt){
    
  unsigned int npix=gifsx*gifsy;
  
  int paletteSize=256;

  Frame output(npix);
  

    // maunal assignment of color indices
    for (int i = 0, j=0; i < npix; i++) {
        int minIndex = 0,
            minDist = 3 * 256 * 256;
        GifColorType *c = outputPalette->Colors;
 
        /* Find closest color in first color map to this color. */
        for (int k = 0; k < outputPalette->ColorCount; k++) {
          int dr = (int(c[k].Red) - data[j] ) ;
          int dg = (int(c[k].Green) - data[j+1] ) ;
          int db = (int(c[k].Blue) - data[j+2] ) ;
          
          int dist=dr*dr+dg*dg+db*db;
          
          if (minDist > dist) {
            minDist  = dist;
            minIndex = k;
          }
        }
        j+=3;
        output[i] = minIndex;
    }


  
  frames.push_back(output);

  delay.push_back(int(dt*100.0));
  return true;       
}

bool AnimatedGifSaver::FakeFrame(Byte* data){
    
  unsigned int npix=gifsx*gifsy;
  
  int paletteSize=256;

  Frame output(npix);
  

  
    
    Frame r(npix),g(npix),b(npix);
  
    // de-interlaeve
    for (int i=0, j=0; i<npix; i++){
    r[i]=data[j++];
    g[i]=data[j++];
    b[i]=data[j++];
    }

    GifColorType ScratchMap[256];

    for (int i=0; i<256; i++) {
      ScratchMap[i].Red = 0;
      ScratchMap[i].Green = 0;
      ScratchMap[i].Blue = 0;
    }
    


    // RED
    ScratchMap[0].Red = 248;
    ScratchMap[0].Green = 0;
    ScratchMap[0].Blue = 0;
    // GREEN
    ScratchMap[1].Red = 0;
    ScratchMap[1].Green = 248;
    ScratchMap[1].Blue = 0;
    // BLUE
    ScratchMap[2].Red = 0;
    ScratchMap[2].Green = 0;
    ScratchMap[2].Blue = 248;


    outputPalette = GifMakeMapObject(paletteSize, ScratchMap);
    if (!outputPalette) return false;
    
    if (GifQuantizeBuffer(gifsx, gifsy, &paletteSize, 
                       &(r[0]),&(g[0]),&(b[0]), &(output[0]), 
                       outputPalette->Colors) == GIF_ERROR) return false;

    
  return true;       
}


static bool AddLoop(GifFileType *gf){
  
   int loop_count;
   loop_count=0;
   {

     /* OLD CODE

     char nsle[12] = "NETSCAPE2.0";
     char subblock[3];
     if (EGifPutExtensionFirst(gf, APPLICATION_EXT_FUNC_CODE, 11, nsle) == GIF_ERROR) {
       return false;
     }
     subblock[0] = 1;
     subblock[2] = loop_count % 256;
     subblock[1] = loop_count / 256;
     if (EGifPutExtensionLast(gf, APPLICATION_EXT_FUNC_CODE, 3, subblock) == GIF_ERROR) {
       return false;
     }

     */


     // NEW CODE

     char nsle[12] = "NETSCAPE2.0";
     char subblock[3];
     if (EGifPutExtensionLeader(gf, APPLICATION_EXT_FUNC_CODE) == GIF_ERROR) {
       return false;
     }

     if (EGifPutExtensionBlock(gf, 11, nsle) == GIF_ERROR) {
       return false;
     }

     subblock[0] = 1;
     subblock[2] = loop_count % 256;
     subblock[1] = loop_count / 256;

     if (EGifPutExtensionBlock(gf, 3, subblock) == GIF_ERROR) {
       return false;
     }

     if (EGifPutExtensionTrailer(gf) == GIF_ERROR) {
       return false;
     }
  
    }
    return true;
}


bool AnimatedGifSaver::Save(const char* filename){
  if (frames.size()==0) return false;
  
  
  GifFileType *GifFile = EGifOpenFileName(filename, false, NULL);
  
  if (!GifFile) return false;

  if (EGifPutScreenDesc(
        GifFile,
			  gifsx, gifsy, 8, 0,
        outputPalette
      ) == GIF_ERROR) return false;

  if (!AddLoop(GifFile)) return false;

  for (int ni=0; ni<frames.size(); ni++) {      

    static unsigned char
    ExtStr[4] = { 0x04, 0x00, 0x00, 0xff };
 
    
    ExtStr[0] = (false) ? 0x06 : 0x04;
    ExtStr[1] = delay[ni] % 256;
    ExtStr[2] = delay[ni] / 256;
 
    /* Dump graphics control block. */
    EGifPutExtension(GifFile, GRAPHICS_EXT_FUNC_CODE, 4, ExtStr);
            
    
    if (EGifPutImageDesc(
       GifFile,
		   0, 0, gifsx, gifsy, false, NULL
       ) == GIF_ERROR)  return false;
       
       
    for (int y = 0, j=(gifsy-1)*gifsx; y < gifsy; y++, j-=gifsx) {
  	  if (EGifPutLine(GifFile, &(frames[ni][j]), gifsx) == GIF_ERROR) return false;
    }
  }

  if (EGifCloseFile(GifFile) == GIF_ERROR) return false;

  return true;       
}

  