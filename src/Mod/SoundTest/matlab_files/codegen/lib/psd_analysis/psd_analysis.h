//
// File: psd_analysis.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

#ifndef PSD_ANALYSIS_H
#define PSD_ANALYSIS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void psd_analysis(const coder::array<double, 2U> &noise, int N,
                         double Fs, coder::array<double, 2U> &psdestx,
                         coder::array<double, 1U> &Fxx);

#endif
//
// File trailer for psd_analysis.h
//
// [EOF]
//
