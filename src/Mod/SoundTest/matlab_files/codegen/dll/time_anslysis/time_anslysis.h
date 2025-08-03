//
// File: time_anslysis.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

#ifndef TIME_ANSLYSIS_H
#define TIME_ANSLYSIS_H

// Include Files
#include "rtwtypes.h"
#include "time_anslysis_spec.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
TIME_ANSLYSIS_DLL_EXPORT extern void
time_anslysis(const coder::array<double, 2U> &sig, double *rms2, double *mean2,
              double *max_abs, double *mean_abs, double *rms_abs, double *var2,
              double *std2, double *spl, double *ppv);

#endif
//
// File trailer for time_anslysis.h
//
// [EOF]
//
