//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_FNORM_HPP
#define AMATH583_FNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

// Helper function
double worker_a(const Vector& x, unsigned long begin, unsigned long end) {
  double sum_of_squares = 0.0;
  for (unsigned long i = begin; i < end; ++i) {
    sum_of_squares += x(i) * x(i);
  }
  return sum_of_squares;
}

double partitioned_two_norm_a(const Vector& x, size_t partitions) {
  std::vector<std::future<double>> partial;
  unsigned long blocksize = x.num_rows() / partitions;
  double sum = 0.0;
  for (unsigned long k = 0; k < partitions; ++k) {
    partial.push_back(
      std::async(std::launch::async,
        worker_a, std::cref(x), k * blocksize, (k + 1) * blocksize));
  }
  for (unsigned long k = 0; k < partitions; ++k) {
    sum += partial[k].get();
  }
  return std::sqrt(sum);
}

double partitioned_two_norm_b(const Vector& x, size_t partitions) {
  std::vector<std::future<double>> partial;
  unsigned long blocksize = x.num_rows() / partitions;
  double sum = 0.0;
  for (unsigned long k = 0; k < partitions; ++k) {
    partial.push_back(
      std::async(std::launch::deferred,
        worker_a, std::cref(x), k * blocksize, (k + 1) * blocksize));
  }
  for (unsigned long k = 0; k < partitions; ++k) {
    sum += partial[k].get();
  }
  return std::sqrt(sum);
}

#endif    // AMATH_583_FNORM_HPP
