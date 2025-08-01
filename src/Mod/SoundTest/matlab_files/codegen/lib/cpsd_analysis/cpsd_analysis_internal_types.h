//
// File: cpsd_analysis_internal_types.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//
#ifndef CPSD_ANALYSIS_INTERNAL_TYPES_H
#define CPSD_ANALYSIS_INTERNAL_TYPES_H

// Include Files
#include "cpsd_analysis_types.h"
#include "rtwtypes.h"
#include "coder_array.h"

// Type Definitions
namespace cpsd
{
  struct struct_T
  {
    double nfft;
    double Fs;
    double conflevel;
    boolean_T average;
    boolean_T maxhold;
    boolean_T minhold;
    boolean_T MIMO;
    boolean_T isNFFTSingle;
    boolean_T centerdc;
    char range[8];
  };

  struct cell_wrap_1
  {
    ::coder::array<double, 2U> f1;
  };

  struct cell_wrap_15
  {
    ::coder::array<double, 1U> f1;
  };
}

#endif

//
// File trailer for cpsd_analysis_internal_types.h
//
// [EOF]
//
