//
// File: cpsd_analysis.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//
#ifndef CPSD_ANALYSIS_H
#define CPSD_ANALYSIS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace cpsd
{
  extern void cpsd_analysis(const ::coder::array<double, 2U> &x, const ::coder::
    array<double, 2U> &y, double Fs, ::coder::array<double, 2U> &Pxy2, ::coder::
    array<double, 2U> &arg2, ::coder::array<double, 1U> &f);
}

#endif

//
// File trailer for cpsd_analysis.h
//
// [EOF]
//
