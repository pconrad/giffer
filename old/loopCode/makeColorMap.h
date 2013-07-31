/****************************************************************************

makeColorMap.h

Given an array of colors, make a color map containing those colors.

*/

#ifndef _MAKE_COLOR_MAP_H
#define _MAKE_COLOR_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "getarg.h"
#include "gif_lib.h"

typedef unsigned int HexColor;

#define EXTRACT_R(color)  ( (color & 0xFF0000) >> 16 )
#define EXTRACT_G(color)  ( (color & 0x00FF00) >> 8 )
#define EXTRACT_B(color)  ( (color & 0x0000FF) )

ColorMapObject * makeColorMap(HexColor colors[], int numColors);

#endif

