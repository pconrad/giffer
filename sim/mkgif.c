/*
  Space Elevator simulation
  Copyright (C) 2003-2004 Blaise Gassend <blaise at gassend dot com>
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gif_lib.h>


#define WIDTH 600
#define HEIGHT 600


GifFileType *GIFfile;

void closeGIF()
{
  printf("closeGIF\n");
  EGifCloseFile(GIFfile);
}

void initGIF()
{
  int i;
  ColorMapObject *GIFcmap;
  char loopheader[15] = "NETSCAPE2.0";
  const int GIFBPC = 6;
  const int GIFColors = GIFBPC * GIFBPC * GIFBPC;
  char ColorTable[6] = { 0, 51, 102, 153, 204, 255 };
  
  GIFcmap = MakeMapObject(256, NULL);
  GIFfile = EGifOpenFileName("oscilout.gif", 0);
  
  for (i = 0; i < 256; i++)
  {
    double r, g, b, f;
    f = (i - 1) / 254.0;
    
    if (i == 0)
    {
      r = g = b = 0;
    }
    else if (3 * f < 1)
    {
      r = 3 * f;
      g = 0;
      b = 1 - 3 * f;
    }
    else if (3 * f < 2)
    {
      r = 1;
      g = 3 * f - 1;
      b = 0;
    }
    else 
    {
      r = 1;
      g = 1;
      b = 3 * f - 2;
    }

    GIFcmap->Colors[i].Red = r * 255;
    GIFcmap->Colors[i].Green = g * 255;
    GIFcmap->Colors[i].Blue = b * 255;
//    GIFcmap->Colors[i].Red = ColorTable[i % GIFBPC];
//    GIFcmap->Colors[i].Green = ColorTable[(i / GIFBPC) % GIFBPC];
//    GIFcmap->Colors[i].Blue = ColorTable[(i / GIFBPC / GIFBPC) % GIFBPC]; 
  }
  
  EGifPutScreenDesc(GIFfile, WIDTH, HEIGHT, 128, 0, GIFcmap);

  loopheader[11] = 3;
  loopheader[12] = 1;
  loopheader[13] = 50;
  loopheader[14] = 0;
  EGifPutExtension(GIFfile, 255, 15, loopheader);
  

}

void saveGIF(unsigned char thisColor)
{
  int w, h, i;
  unsigned char img[WIDTH * HEIGHT];

  printf("saveGIF\n");

static unsigned char
    ExtStr[4] = { 0x04, 0x00, 0x00, 0xff };
 
    
    ExtStr[0] = 0x04;
    ExtStr[1] = 1000 % 256;
    ExtStr[2] = 1000 / 256;
 
    /* Dump graphics control block. */
    EGifPutExtension(GIFfile, GRAPHICS_EXT_FUNC_CODE, 4, ExtStr);
            
    

  int j;
  for (j=0; j<WIDTH*HEIGHT; j++) {
    img[j] = thisColor;
  }
  
  EGifPutImageDesc(GIFfile, 0, 0, WIDTH, HEIGHT, 0, NULL);
  i = 0;
  for (h = 0; h < HEIGHT; h++)
    for (w = 0; w < WIDTH; w++)
    {
      int col = img[i++];
//      col += ((int) img[i++]) * 6 / 256;
//      col += (((int) img[i++]) * 6 / 256) * 6;
//      col += (((int) img[i++]) * 6 / 256) * 6 * 6;
      EGifPutPixel(GIFfile, col);
    }      



  printf("saveGIF - done\n");
}



int main(int argc, char **argv)
{
  initGIF();
  saveGIF(30);
  saveGIF(150);
  saveGIF(75);
  closeGIF();
  return 0;
}
