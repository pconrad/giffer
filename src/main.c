/****************************************************************************

P. Conrad, gifferLoop1.c

Program to demo creating animated gif which flashes LED 2.

Based on gifsponge.c - skeleton file for generic GIF `sponge' program from giflib-5.0.4
Slurp a GIF into core (from stdin), operate on it, spew it out again (on stdout).

****************************************************************************/

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>

#include "gif_lib.h"

void PrintGifError(int ErrorCode); // defined in qprintf.c

#include "arduinoState.h"

extern struct ArduinoSequence_S *ss;

struct namedHexColor {
  const char * const name;
  const int color;
} namedColors[] = { {"red",0xFF0000},
		    {"orange",0xFF9933}, 
		    {"yellow",0xFFFF00}, 
		    {"green",0x00FF66}, 
		    {"blue",0x0066CC}, 
		    {0,0} };

  const int ledNumToX[16] = {0,0,
		       80,80,80,80,80,80,80,
		       5,  5, 5, 5, 5, 5, 5};
  const int ledNumToY[16] = {0,0,
		       165,140,115,90,65,35,10,
		       165,140,115,90,65,35, 7};
  const char * const ledNumToColor[16] = 
    {0,0,
     "red","green","red","green","red","green","red",
     "orange","orange","orange","blue","blue","yellow","yellow"};


void GifAppendExtensionBlocks(int *ExtensionBlockCount,
			ExtensionBlock **ExtensionBlocks,
			int AdditionalExtensionBlockCount,
			ExtensionBlock *AdditionalExtensionBlocks)


{
  int i;
  for (i=0; i<AdditionalExtensionBlockCount; i++) {
    ExtensionBlock *ep;

    ep = (AdditionalExtensionBlocks + i); // ptr arithmetic

    int retVal = GifAddExtensionBlock(ExtensionBlockCount, ExtensionBlocks,
			 ep->Function,
			 ep->ByteCount,
			 ep->Bytes);
    if (retVal != GIF_OK) {
      fprintf(stderr,"Error: %s %d GifAddExtensionBlock failed \n",
	      __FILE__,__LINE__);
      exit(12);
    }
  }
}


void
DumpColorMap(ColorMapObject *Object,
             FILE * fp)
{
  if (Object != NULL) {
    int i, j, Len = Object->ColorCount;

    for (i = 0; i < Len; i += 4) {
      for (j = 0; j < 4 && j < Len; j++) {
	(void)fprintf(fp, "%3d: %02x %02x %02x   ", i + j,
		      Object->Colors[i + j].Red,
		      Object->Colors[i + j].Green,
		      Object->Colors[i + j].Blue);
      }
      (void)fprintf(fp, "\n");
    }
  }
}

int getColor(ColorMapObject *Object, int hexColor)
{
  int r = ((hexColor & 0xFF0000) >> 16);
  int g = ((hexColor & 0x00FF00) >> 8);
  int b = ((hexColor & 0x0000FF));

  if (Object != NULL) {
    int i;
    int Len = Object->ColorCount;

    for (i = 0; i < Len; i++) {
      if( (Object->Colors[i].Red == r) &&
	  (Object->Colors[i].Green == g) &&
	  (Object->Colors[i].Blue == b))
	return (i);
    }
  }
  return -1;
}

/**
   @param Object color map to search
   @param color color name (e.g. "red") from global constant namedColors
   @param exitOnFailure if true, then program will exit if color not found
 */
int getNamedColor(ColorMapObject *Object, 
		  const char * const color,
		  int exitOnFailure) 
{

  int i;
  int retValue = -2;
  for (i=0; namedColors[i].name != 0; i++) {
    if (strcmp(color,namedColors[i].name)==0) {
      retValue = getColor(Object,namedColors[i].color);
      break;
    }
  }
  if (exitOnFailure && retValue < 0) {
    fprintf(stderr,"color %s not found: ",color);
    switch(retValue) {
    case -2: fprintf(stderr,"not found in namedColors\n"); break;
    case -1: 
      fprintf(stderr,"not found in image\n"); 
      DumpColorMap(Object,stderr);
      break;
    default:
      fprintf(stderr,"\n");
    }
    exit(3);
  }
  return retValue;
}



void turnOnLED(int ledNum, SavedImage *image, ColorMapObject *colorMap) {
  
  int left = image->ImageDesc.Left;
  int top = image->ImageDesc.Top;
  // int w = image->ImageDesc.Width;
  // int h = image->ImageDesc.Height;
  
  
  GifDrawRectangle(image, 
		   left + ledNumToX[ledNum],
		     top + ledNumToY[ledNum],
		     15, 15,
		     getNamedColor(colorMap,
				   ledNumToColor[ledNum],
				   1));
}

void turnOnDimLED(int ledNum, SavedImage *image, ColorMapObject *colorMap) {
  
  int left = image->ImageDesc.Left;
  int top = image->ImageDesc.Top;
  // int w = image->ImageDesc.Width;
  // int h = image->ImageDesc.Height;
  
  
  GifDrawRectangle(image, 
		   left + ledNumToX[ledNum] + 5,
		     top + ledNumToY[ledNum] + 5,
		     5, 5,
		     getNamedColor(colorMap,
				   ledNumToColor[ledNum],
				   1));
}


void    addAllLEDs(SavedImage *image, ColorMapObject *colorMap) {
  
  int ledNum;
  for (ledNum = 2; ledNum <=15; ledNum++) {
    turnOnLED(ledNum, image, colorMap) ;
  }
}


/*
 * SavedImageCpy creates a deep copy of a saved image.
 * The storage for the copy should already be allocated.
 * It works like strcpy (dst,src)
 */
void 
SavedImageCpy(SavedImage * const dest, const SavedImage * const src)
{
  SavedImage * const sp = dest;
  const SavedImage * const CopyFrom = src;


 
  if (src == NULL) {
	fprintf(stderr,"Error: %s %d src pointer null\n", __FILE__, __LINE__);
	exit(5);
  }
  if (dest == NULL) {
	fprintf(stderr,"Error: %s %d dest pointer null\n", __FILE__, __LINE__);
	exit(6);
  }

  /* clear, then copy */

  memset((char *)sp, '\0', sizeof(SavedImage));
  memcpy((char *)sp, CopyFrom, sizeof(SavedImage));

  /* 
   * Make our own allocated copies of the heap fields in the
   * copied record.  This guards against potential aliasing
   * problems.
   */
  
  /* first, the local color map */
  if (sp->ImageDesc.ColorMap != NULL) {
    sp->ImageDesc.ColorMap = GifMakeMapObject(
					      CopyFrom->ImageDesc.ColorMap->ColorCount,
					      CopyFrom->ImageDesc.ColorMap->Colors);
    if (sp->ImageDesc.ColorMap == NULL) {
      fprintf(stderr,"Error: %s %d allocated color map failed\n", __FILE__, __LINE__);
      exit(4);
    }
  }
  
  /* next, the raster */

  sp->RasterBits = (unsigned char *)malloc(sizeof(GifPixelType) *
					   CopyFrom->ImageDesc.Height *
					   CopyFrom->ImageDesc.Width);
  if (sp->RasterBits == NULL) {
    fprintf(stderr,"Error: %s %d malloc raster bits failed\n", __FILE__, __LINE__);
    exit(7);
  }

  memcpy(sp->RasterBits, CopyFrom->RasterBits,
	 sizeof(GifPixelType) * CopyFrom->ImageDesc.Height *
	 CopyFrom->ImageDesc.Width);
  
  /* finally, the extension blocks */
  if (sp->ExtensionBlocks != NULL) {
      sp->ExtensionBlocks = (ExtensionBlock *)malloc(
						     sizeof(ExtensionBlock) *
						     CopyFrom->ExtensionBlockCount);
      if (sp->ExtensionBlocks == NULL) {
	fprintf(stderr,"Error: %s %d malloc extension blocks failed\n", __FILE__, __LINE__);
	exit(7);
      }
      memcpy(sp->ExtensionBlocks, CopyFrom->ExtensionBlocks,
	     sizeof(ExtensionBlock) * CopyFrom->ExtensionBlockCount);
  }
}



int makeGif(const char * const baseFile, 
	    const char * const outFile)
{
    int	i, ErrorCode;
    GifFileType *GifFileIn, *GifFileOut = (GifFileType *)NULL;

    struct ArduinoState_S *s = ss->head;



    if ((GifFileIn = DGifOpenFileName(baseFile, &ErrorCode)) == NULL) {
	PrintGifError(ErrorCode);
	exit(EXIT_FAILURE);
    }
    if (DGifSlurp(GifFileIn) == GIF_ERROR) {
	PrintGifError(GifFileIn->Error);
	exit(EXIT_FAILURE);
    }

    if ((GifFileOut = EGifOpenFileName(outFile, false, &ErrorCode)) == NULL) {
	PrintGifError(ErrorCode);
	exit(EXIT_FAILURE);
    }


    

    /*
     * Your operations on in-core structures go here.  
     */

    if (DEBUG) DumpColorMap(GifFileIn->SColorMap,stderr);

    if (GifFileIn->ImageCount != 1) {
      fprintf(stderr,"Error: %s %d expecting exactly one image in input file\n",
	      __FILE__,__LINE__);
    }


    SavedImage *newImage = (SavedImage *) malloc( sizeof(SavedImage) );

    SavedImageCpy(newImage, &GifFileIn->SavedImages[0]);

    turnOnLED(2,newImage,GifFileIn->SColorMap);



    int imageCount = 0;
    for (s = ss->head; s!=NULL; s=s->next) {
      imageCount++;
    }

    // allocate an array for the images

    SavedImage *newImages = 
      (SavedImage *)
      malloc(sizeof(SavedImage) * imageCount);

    if (newImages == NULL) {
      fprintf(stderr,"Error: %s %d Could not allocate memory for images\n",
	      __FILE__,__LINE__);
      exit(15);
    }

    int imageIndex = 0;
    for (s = ss->head; s!=NULL; s=s->next) {
      
      // Make copy of SavedImage[0] as "newImages[imageIndex]"
      
      SavedImageCpy(&newImages[imageIndex], &GifFileIn->SavedImages[0]);
      
      // Now go through, and for each LED that should be on, 
      // turn it on.
      
      // TODO: replace with code that does this from the s record...

      int pin;
      for (pin = 2; pin <= 15; pin ++) {

	if (s->pinState[pin] == HIGH) {
	  if (s->pinMode[pin] == OUTPUT) {
	    turnOnLED(pin,&newImages[imageIndex],GifFileIn->SColorMap);
	  } else if (s->pinMode[pin] == INPUT) {
	    turnOnDimLED(pin,&newImages[imageIndex],GifFileIn->SColorMap);
	  }
	}
		  
      } // for pins

      imageIndex++;
    } // for state frames


    // Allocate a leading extension block for looping

    int LeadingExtensionBlockCount = 0;
    ExtensionBlock *LeadingExtensionBlocks = NULL;
    int loopParam=0;  // 0 means loop forever
    {
      unsigned char params[3] = {1, 0, 0};
      /* Create a Netscape 2.0 loop block */
      if (GifAddExtensionBlock(&LeadingExtensionBlockCount,
			       &LeadingExtensionBlocks,
			       APPLICATION_EXT_FUNC_CODE,
			       11,
			       (unsigned char *)"NETSCAPE2.0")==GIF_ERROR ) {
	fprintf(stderr,"Error: %s %d out of memory while adding loop block.\n",
		__FILE__, __LINE__);
	exit(9);
      }

      // Little endian?
      params[1] = (loopParam & 0xff);
      params[2] = (loopParam >> 8) & 0xff;

      // Add the extension for the delay
      if (GifAddExtensionBlock(&LeadingExtensionBlockCount,
			       &LeadingExtensionBlocks,
			       0, sizeof(params), params) == GIF_ERROR) {
	fprintf(stderr,"Error: %s %d out of memory while adding loop continuation.\n",
		__FILE__, __LINE__);
	exit(10);
      }

    }

    // Add to the first image


    SavedImage *firstImage = &(newImages[0]);
    if (firstImage->ExtensionBlockCount == 0) {
      firstImage->ExtensionBlockCount = LeadingExtensionBlockCount;
      firstImage->ExtensionBlocks = LeadingExtensionBlocks;
    } else {
      GifAppendExtensionBlocks(&firstImage->ExtensionBlockCount,
			       &firstImage->ExtensionBlocks,
			       LeadingExtensionBlockCount,
			       LeadingExtensionBlocks);
    }
    

     /* This code just copies the header and each image from the incoming file.
     */

    GifFileOut->SWidth = GifFileIn->SWidth;
    GifFileOut->SHeight = GifFileIn->SHeight;
    GifFileOut->SColorResolution = GifFileIn->SColorResolution;
    GifFileOut->SBackGroundColor = GifFileIn->SBackGroundColor;

    fflush(stderr);
    
    GifFileOut->SColorMap = GifMakeMapObject(
					     GifFileIn->SColorMap->ColorCount,
					     GifFileIn->SColorMap->Colors);
    
    //for (i = 0; i < GifFileIn->ImageCount; i++)
    //  (void) GifMakeSavedImage(GifFileOut, &GifFileIn->SavedImages[i]);

   
    for (i = 0; i < imageCount; i++) {
      (void) GifMakeSavedImage(GifFileOut, &newImages[i]);
     }

    // Now, add delays to GifFileOut

    // start with the second frame, adding delays.

    imageIndex = 1;
    struct ArduinoState_S *prev = ss->head;
    for (s = ss->head->next; s; s=s->next) {

      unsigned long delay = (s->millis - prev->millis);

      GraphicsControlBlock gcb = {0,false,delay/10,-1}; // unit is 1/100 sec
      EGifGCBToSavedExtension(&gcb, GifFileOut, imageIndex);
      imageIndex++;
      prev = s;
    }
    
    /*
     * Note: don't do DGifCloseFile early, as this will
     * deallocate all the memory containing the GIF data!
     *
     * Further note: EGifSpew() doesn't try to validity-check any of this
     * data; it's *your* responsibility to keep your changes consistent.
     * Caveat hacker!
     */
    if (EGifSpew(GifFileOut) == GIF_ERROR)
	PrintGifError(GifFileOut->Error);
    else if (DGifCloseFile(GifFileIn) == GIF_ERROR)
	PrintGifError(GifFileIn->Error);

    return 0;
    

}

/* end */

int main(int argc, char **argv) {

  if (argc!=3) {
    fprintf(stderr,"Usage: %s basefile.gif outfile.gif\n",argv[0]);
    exit(1);
  }

  initArduinoSequence();
  setup();
  loop();
  if (DEBUG) dumpArduinoSequence();

  return makeGif(argv[1],argv[2]);
  

}
