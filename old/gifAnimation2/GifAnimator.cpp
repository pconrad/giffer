#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <vector>

using namespace std;


#include "GifAnimator.h"

// global vairables


GifAnimator::GifAnimator(const char * const filename){


  // The following functions are used to set up input from a GIF:

  int error;

  this->gf = DGifOpenFileName(filename, &error);
  
  if (this->gf==NULL) {
    std::cerr << "Error: " << error << endl;
    exit(1);
  }
  
  if (DGifSlurp(this->gf) != GIF_OK) {
    std::cerr << "Error: DGifSlurp returned error status "  << endl;
    exit(2);
  }

}

GifAnimator::~GifAnimator(){
  
}

bool GifAnimator::Save(){


  int result = EGifSpew(this->gf);

  if (result != GIF_OK) {
    cerr << "Problem writing file " << endl;
  }

}

  
