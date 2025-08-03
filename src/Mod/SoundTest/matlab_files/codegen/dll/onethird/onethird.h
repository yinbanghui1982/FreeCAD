//
// File: onethird.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

#ifndef ONETHIRD_H
#define ONETHIRD_H

// Include Files
#include "onethird_spec.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
ONETHIRD_DLL_EXPORT extern void
onethird(const coder::array<double, 2U> &t, const coder::array<double, 1U> &x,
         coder::array<double, 1U> &Ya_1, double Ya_2[30],
         coder::array<double, 2U> &f, double fc[30], double *nfft, double *nc);

#endif
//
// File trailer for onethird.h
//
// [EOF]
//
