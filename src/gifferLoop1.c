/****************************************************************************

gifsponge.c - skeleton file for generic GIF `sponge' program

Slurp a GIF into core, operate on it, spew it out again.  Most of the
junk above `int main' isn't needed for the skeleton, but is likely to
be for what you'll do with it.

If you compile this, it will turn into an expensive GIF copying routine;
stdin to stdout with no changes and minimal validation.  Well, it's a
decent test of DGifSlurp() and EGifSpew(), anyway.

Note: due to the vicissitudes of Lempel-Ziv compression, the output of this
copier may not be bitwise identical to its input.  This can happen if you
copy an image from a much more (or much *less*) memory-limited system; your
compression may use more (or fewer) bits.  The uncompressed rasters should,
however, be identical (you can check this with gifbuild -d).

****************************************************************************/

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>

#include "getarg.h"
#include "gif_lib.h"

#define PROGRAM_NAME	"gifsponge"

struct namedHexColor {
  const char * name;
  int color;
} namedColors[] = { {"red",0xFF0000},
		    {"orange",0xFF9933}, 
		    {"yellow",0xFFFF00}, 
		    {"green",0x00FF66}, 
		    {"blue",0x0066CC}, 
		    {0,0} };

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



void    addAllLEDs(SavedImage *image, ColorMapObject *colorMap) {
  
  int left = image->ImageDesc.Left;
  int top = image->ImageDesc.Top;
  int w = image->ImageDesc.Width;
  int h = image->ImageDesc.Height;
  
  if (DEBUG) {
    fprintf(stderr,"image->ImageDesc.Left=%d\n",image->ImageDesc.Left);
    fprintf(stderr,"image->ImageDesc.Top=%d\n",image->ImageDesc.Top);
    fprintf(stderr,"image->ImageDesc.Width=%d\n",image->ImageDesc.Width);
    fprintf(stderr,"image->ImageDesc.Height=%d\n",image->ImageDesc.Height);
  }
  
  int ledNumToX[16] = {0,0,
		       80,80,80,80,80,80,80,
		       5,  5, 5, 5, 5, 5, 5};
  int ledNumToY[16] = {0,0,
		       165,140,115,90,65,35,10,
		       165,140,115,90,65,35, 7};
  const char * const ledNumToColor[16] = 
    {0,0,
     "red","green","red","green","red","green","red",
     "orange","orange","orange","blue","blue","yellow","yellow"};
  
  int ledNum;
  for (ledNum = 2; ledNum <=15; ledNum++) {
    GifDrawRectangle(image, 
		     left + ledNumToX[ledNum],
		     top + ledNumToY[ledNum],
		     15, 15,
		     getNamedColor(colorMap,
				   ledNumToColor[ledNum],
				   1));
  }
  
  fprintf(stderr,"Done with addAllLEDs\n");
}




int main(int argc, char **argv)
{
    int	i, ErrorCode;
    GifFileType *GifFileIn, *GifFileOut = (GifFileType *)NULL;

    if ((GifFileIn = DGifOpenFileHandle(0, &ErrorCode)) == NULL) {
	PrintGifError(ErrorCode);
	exit(EXIT_FAILURE);
    }
    if (DGifSlurp(GifFileIn) == GIF_ERROR) {
	PrintGifError(GifFileIn->Error);
	exit(EXIT_FAILURE);
    }
    if ((GifFileOut = EGifOpenFileHandle(1, &ErrorCode)) == NULL) {
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

    fprintf(stderr,"About to call addAllLEDs \n");

    addAllLEDs(&(GifFileIn->SavedImages[0]),GifFileIn->SColorMap);



     /* This code just copies the header and each image from the incoming file.
     */

    GifFileOut->SWidth = GifFileIn->SWidth;
    GifFileOut->SHeight = GifFileIn->SHeight;
    GifFileOut->SColorResolution = GifFileIn->SColorResolution;
    fprintf(stderr,"GifFileIn->SColorResolution=%d\n",GifFileIn->SColorResolution);
    GifFileOut->SBackGroundColor = GifFileIn->SBackGroundColor;

    fprintf(stderr,"About to call GifMakeMapObject\n");
    fflush(stderr);
    
    GifFileOut->SColorMap = GifMakeMapObject(
					     GifFileIn->SColorMap->ColorCount,
					     GifFileIn->SColorMap->Colors);
    
    for (i = 0; i < GifFileIn->ImageCount; i++)
      (void) GifMakeSavedImage(GifFileOut, &GifFileIn->SavedImages[i]);
    
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
