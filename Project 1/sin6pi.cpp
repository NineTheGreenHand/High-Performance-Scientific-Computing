//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <iostream>
#include <vector>

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

const double pi = 3.141592653589793238462643383279;

// Plotting function
void make_plot(const std::vector<double>& x) {
  CImg<unsigned char> graph(500, 400, 1, 3, 0);
  const unsigned char red[] = {255, 0, 0}, green[] = {0, 255, 0}, blue[] = {0, 0, 255};
  CImg<double>        values(1, x.size(), 1, 1, 0);
  for (int i1 = 0; i1 < x.size(); ++i1) {
    values(0, i1) = x[i1];
  }
  graph.fill(255).draw_graph(values, blue, 1, 2).save_bmp("plot.bmp");
}


int main() {
  const size_t N = 1024;

  std::vector<double> y(N);

  // Compute sin(6*x) on interval [0, 1] -- inclusive of 1
  for (size_t i = 0; i < N; ++i) {
    y[i] = sin(((6 * pi) / 1023) * i);
  }

  // Call make_plot( /* Write Me */ );
  make_plot(y);

  if (y[0] == 0 && y[1022] != 0 && std::abs(y[1023]) < 2.e-15) {
    std::cout << "Pass " << y[1023] << std::endl;
    return 0;    // return success value
  } else {
    std::cout << "Fail " << y[1023] << std::endl;
    return 1;    // return other than success value
  }

  return 0;      // default return success value
}
