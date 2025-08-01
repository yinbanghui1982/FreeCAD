//
// File: computeperiodogram.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//
#ifndef COMPUTEPERIODOGRAM_H
#define COMPUTEPERIODOGRAM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace cpsd
{
  struct cell_wrap_15;
}

// Function Declarations
namespace cpsd
{
  void computeperiodogram(const cell_wrap_15 x[2], const ::coder::array<double,
    1U> &win, double nfft, double Fs, ::coder::array<creal_T, 2U> &Pxx, ::coder::
    array<double, 1U> &F);
}

#endif

//
// File trailer for computeperiodogram.h
//
// [EOF]
//
