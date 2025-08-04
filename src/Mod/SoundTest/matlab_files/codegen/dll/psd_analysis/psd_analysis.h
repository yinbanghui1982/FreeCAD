//
// File: psd_analysis.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:01:53
//

#ifndef PSD_ANALYSIS_H
#define PSD_ANALYSIS_H

// Include Files
#include "psd_analysis_spec.h"
#include "rtwtypes.h"
// #include "coder_array.h"
#include "matlab_files/codegen/lib/time_anslysis/coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
PSD_ANALYSIS_DLL_EXPORT extern void
psd_analysis(const coder::array<double, 1U> &noise, double N, double Fs,
             coder::array<double, 2U> &psdestx, coder::array<double, 1U> &Fxx);

#endif
//
// File trailer for psd_analysis.h
//
// [EOF]
//
