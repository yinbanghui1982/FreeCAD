//
// File: pingpu.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:00:28
//

#ifndef PINGPU_H
#define PINGPU_H

// Include Files
#include "pingpu_spec.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
PINGPU_DLL_EXPORT extern void pingpu(const coder::array<double, 2U> &b_time,
                                     coder::array<double, 2U> &data, double w,
                                     coder::array<double, 2U> &f,
                                     coder::array<double, 2U> &Y, double *fs);

#endif
//
// File trailer for pingpu.h
//
// [EOF]
//
