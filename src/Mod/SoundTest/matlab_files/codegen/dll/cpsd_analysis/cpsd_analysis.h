//
// File: cpsd_analysis.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

#ifndef CPSD_ANALYSIS_H
#define CPSD_ANALYSIS_H

// Include Files
#include "cpsd_analysis_spec.h"
#include "rtwtypes.h"
// #include "coder_array.h"
#include "matlab_files/codegen/lib/time_anslysis/coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
CPSD_ANALYSIS_DLL_EXPORT extern void
cpsd_analysis(const coder::array<double, 2U> &x,
              const coder::array<double, 2U> &y, double Fs,
              coder::array<double, 2U> &Pxy2, coder::array<double, 2U> &arg2,
              coder::array<double, 1U> &f);

#endif
//
// File trailer for cpsd_analysis.h
//
// [EOF]
//
