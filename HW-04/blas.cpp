/*
BLAS Level 1 function definitions
*/

//Suggested compilation: g++ -std=c++17 -Wall -Werror blas.cpp tests.cpp

#include "blas.h"
#include <cmath>


int amax(const double* x, const unsigned int len) {
  if (len > 0) {
    double max = std::abs(x[0]);
    int maxIndex = 0;
    for (unsigned int i = 0; i < len; i++) {
      if (std::abs(x[i]) > max) {
        max = std::abs(x[i]);
        maxIndex = i;
      }
    }
    return maxIndex;
  } else {
    return -1;
  }
}

double asum(const double* x, const unsigned int len) {
  double sum = 0;
  for (unsigned int i = 0; i < len; i++) {
    sum += std::abs(x[i]);
  }
  return sum;
}

void axpy(const double a, const double* x, double* y, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    y[i] = a*x[i] + y[i];
  }
}

void copy(const double* x, double* y, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    y[i] = x[i];
  }
}

double dot(const double* x, const double* y, const unsigned int len) {
  double dot = 0;
  if (len > 0) {
    for (unsigned int i = 0; i < len; i++) {
      dot += x[i] * y[i];
    }
    return dot;
  } else {
    return 0;
  }
}

double norm2(const double* x, const unsigned int len) {
  double sum = 0;
  for (unsigned int i = 0; i < len; i++) {
    sum += std::pow(x[i], 2);
  }
  return std::sqrt(sum);
}

void scale(const double a, double* x, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    x[i] = a * x[i];
  }
}

void swap(double* x, double* y, const unsigned int len) {
  double temp = 0;
  for (unsigned int i = 0; i < len; i++) {
    temp = x[i];
    x[i] = y[i];
    y[i] = temp;
  }
}
