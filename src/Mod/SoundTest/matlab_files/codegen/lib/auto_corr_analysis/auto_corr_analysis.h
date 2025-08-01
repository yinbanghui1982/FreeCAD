//
// File: auto_corr_analysis.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:06:11
//
#ifndef AUTO_CORR_ANALYSIS_H
#define AUTO_CORR_ANALYSIS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace corr
{
  extern void auto_corr_analysis(const ::coder::array<double, 2U> &x, double dt,
    ::coder::array<double, 2U> &c, ::coder::array<double, 2U> &lags2);
}

#endif

//
// File trailer for auto_corr_analysis.h
//
// [EOF]
//
