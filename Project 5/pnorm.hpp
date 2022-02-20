//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_PNORM_HPP
#define AMATH583_PNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

std::mutex p_mutex;
// Fixed
void worker_a(const Vector& x, unsigned long begin, unsigned long end, double& partial) {
  double temp = 0.0;
  for (unsigned long i = begin; i < end; ++i)
    temp += x(i) * x(i);
  { std::lock_guard<std::mutex> p_guard(p_mutex); 
    partial += temp;
  }
}

// Fixed
double partitioned_two_norm_a(const Vector& x, size_t partitions) {
  std::vector<std::thread> threads;
  unsigned long blocksize = x.num_rows() / partitions;

  double sum = 0;
  for (unsigned long i = 0; i < partitions; ++i) {
    threads.push_back(std::thread(worker_a, std::cref(x), i * blocksize, (i + 1) * blocksize, std::ref(sum)));
  }
  for (unsigned long i = 0; i < partitions; ++i)
    threads[i].join();

  return std::sqrt(sum);
}

#endif    //  AMATH583_PNORM_HPP
