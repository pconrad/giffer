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

int getNamedColor(ColorMapObject *Object, const char * const color) {

  int i;
  for (i=0; namedColors[i].name != 0; i++) {
    fprintf(stderr,"comparing %s to %s\n",color,namedColors[i].name);
    if (strcmp(color,namedColors[i].name)==0) {
      return getColor(Object,namedColors[i].color);
    }
  }
  return -2;
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

    DumpColorMap(GifFileIn->SColorMap,stderr);

    int red = getNamedColor(GifFileIn->SColorMap,"red");
    int orange = getNamedColor(GifFileIn->SColorMap,"orange");
    int yellow = getNamedColor(GifFileIn->SColorMap,"yellow");
    int green = getNamedColor(GifFileIn->SColorMap,"green");
    int blue = getNamedColor(GifFileIn->SColorMap,"blue");

    fprintf(stderr,"red=%d orange=%d yellow=%d green=%d blue=%d\n",
	    red,orange,yellow,green,blue);

    if (red < 0) {
      fprintf(stderr,"%s %d: Could not find red\n",__FILE__,__LINE__);
      exit(3);
    }

    if (orange < 0) {
      fprintf(stderr,"%s %d: Could not find orange\n",__FILE__,__LINE__);
      exit(3);
    }

    if (yellow < 0) {
      fprintf(stderr,"%s %d: Could not find yellow\n",__FILE__,__LINE__);
      exit(3);
    }

    if (green < 0) {
      fprintf(stderr,"%s %d: Could not find green\n",__FILE__,__LINE__);
      exit(3);
    }

    if (blue < 0) {
      fprintf(stderr,"%s %d: Could not find blue\n",__FILE__,__LINE__);
      exit(3);
    }


    if (GifFileIn->ImageCount > 0) {
      fprintf(stderr,"About to call GifDrawRectangle \n");
      SavedImage *image = &(GifFileIn->SavedImages[0]);
      int left = image->ImageDesc.Left;
      int top = image->ImageDesc.Top;
      int w = image->ImageDesc.Width;
      int h = image->ImageDesc.Height;

      fprintf(stderr,"image->ImageDesc.Left=%d\n",image->ImageDesc.Left);
      fprintf(stderr,"image->ImageDesc.Top=%d\n",image->ImageDesc.Top);
      fprintf(stderr,"image->ImageDesc.Width=%d\n",image->ImageDesc.Width);
      fprintf(stderr,"image->ImageDesc.Height=%d\n",image->ImageDesc.Height);
      GifDrawRectangle(image, left + 10, top+20, 10, 10, red);
      GifDrawRectangle(image, left + 10, top+40, 10, 10, orange);
      GifDrawRectangle(image, left + 80, top+60, 10, 10, yellow);
      GifDrawRectangle(image, left + 10, top+80, 10, 10, green);
      GifDrawRectangle(image, left + 80, top+100, 10, 10, blue);

    } else {
      fprintf(stderr,"No saved images\n");
    }

    fprintf(stderr,"Done with GifDrawRectangle in image\n");

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
