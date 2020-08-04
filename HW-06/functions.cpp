#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];

  bool fail = false;

  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];

    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }

  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }

  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* seam = new int[length];
  for (int i = 0; i < length; i++) {
    seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
  delete [] seam;
  seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {

  ifstream ifs (filename);

  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w;
  if (ifs.fail() && !ifs.eof()) {
    cout << "Error: read non-integer value";
    return false;
  } else if (ifs.fail() && ifs.eof()) {
    cout << "Error: not enough color values";
    return false;
  }

  ifs >> h;
  if (ifs.fail() && !ifs.eof()) {
    cout << "Error: read non-integer value";
    return false;
  } else if (ifs.fail() && ifs.eof()) {
    cout << "Error: not enough color values";
    return false;
  }


  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width <<") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height <<") does not match value in file (" << h << ")" << endl;
    return false;
  }

  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail() && !ifs.eof()) {
    cout << "Error: read non-integer value";
    return false;
  } else if (colorMax != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  } else if (ifs.fail() && ifs.eof()) {
    cout << "Error: not enough color values";
    return false;
  }

  // get RGB pixel values
  int red = 0;
  int green = 0;
  int blue = 0;

  for (int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {

      ifs >> red;
      if (ifs.fail() && !ifs.eof()) {
        cout << "Error: read non-integer value";
        return false;
      } else if (ifs.fail() && ifs.eof()) {
        cout << "Error: not enough color values";
        return false;
      } else if (red > 255 || red < 0) {
        cout << "Error: invalid color value " << red;
        return false;
      } else {
        image[j][i].r = red;
      }

      ifs >> green;
      if (ifs.fail() && !ifs.eof()) {
        cout << "Error: read non-integer value";
        return false;
      } else if (ifs.fail() && ifs.eof()) {
        cout << "Error: not enough color values";
        return false;
      } else if (green > 255 || green < 0) {
        cout << "Error: invalid color value " << green;
        return false;
      } else {
        image[j][i].g = green;
      }

      ifs >> blue;
      if (ifs.fail() && !ifs.eof()) {
        cout << "Error: read non-integer value";
        return false;
      } else if (ifs.fail() && ifs.eof()) {
        cout << "Error: not enough color values";
        return false;
      } else if (blue > 255 || blue < 0) {
        cout << "Error: invalid color value " << blue;
        return false;
      } else {
        image[j][i].b = blue;
      }

    }
  }

  int temp;
  ifs >> temp;
  if (!ifs.fail()) {
    cout << "Error: too many color values";
    return false;
  }

  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {

  ofstream ofs (filename);
  //check if output stream opened successfully
  if(ofs.is_open()){
    // output preamble
    ofs << "P3" << endl;
    ofs << width << ' ' << height << endl << 255 << endl;
    // output pixels
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        ofs << image[j][i].r << ' ' << image[j][i].g << ' ' << image[j][i].b << endl;
      }
    }
  } else {
    // check if output stream opened successfully
    cout << "Error: failed to open output file " << filename << endl;
    return false;
  }

  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) {
  int xGrad = 0;
  int yGrad = 0;
  int rx = 0; int gx = 0; int bx = 0;
  int ry = 0; int gy = 0; int by = 0;

  if (x == 0) {
    rx = abs(image[x+1][y].r - image[width-1][y].r);
    gx = abs(image[x+1][y].g - image[width-1][y].g);
    bx = abs(image[x+1][y].b - image[width-1][y].b);
  } else if (x == (width - 1)) {
    rx = abs(image[0][y].r - image[x-1][y].r);
    gx = abs(image[0][y].g - image[x-1][y].g);
    bx = abs(image[0][y].b - image[x-1][y].b);
  } else {
    rx = abs(image[x+1][y].r - image[x-1][y].r);
    gx = abs(image[x+1][y].g - image[x-1][y].g);
    bx = abs(image[x+1][y].b - image[x-1][y].b);
  }
  xGrad = rx * rx + bx * bx + gx * gx;

  if (y == 0) {
    ry = abs(image[x][y+1].r - image[x][height-1].r);
    gy = abs(image[x][y+1].g - image[x][height-1].g);
    by = abs(image[x][y+1].b - image[x][height-1].b);
  } else if (y == (height - 1)) {
    ry = abs(image[x][0].r - image[x][y-1].r);
    gy = abs(image[x][0].g - image[x][y-1].g);
    by = abs(image[x][0].b - image[x][y-1].b);
  } else {
    ry = abs(image[x][y+1].r - image[x][y-1].r);
    gy = abs(image[x][y+1].g - image[x][y-1].g);
    by = abs(image[x][y+1].b - image[x][y-1].b);
  }
  yGrad = ry * ry + by * by + gy * gy;

  int totalGrad = xGrad + yGrad;

  return totalGrad;
}

// implement for part 2

// int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
//   return 0;
// }
//
// int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
//   return 0;
// }
//
// int* findMinVerticalSeam(Pixel** image, int width, int height) {
//   return nullptr;
// }
//
// int* findMinHorizontalSeam(Pixel** image, int width, int height) {
//   return nullptr;
// }
//
// void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
// }
//
// void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
// }
