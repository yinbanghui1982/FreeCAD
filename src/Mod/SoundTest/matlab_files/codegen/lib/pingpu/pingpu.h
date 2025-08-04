//
// File: pingpu.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 03-Dec-2023 12:42:37
//

#ifndef PINGPU_H
#define PINGPU_H

// Include Files
#include "rtwtypes.h"
// #include "coder_array.h"
#include "matlab_files/codegen/lib/time_anslysis/coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void pingpu(const coder::array<double, 1U> &b_time,
                   const coder::array<double, 1U> &data,
                   coder::array<double, 2U> &f, coder::array<double, 1U> &Y,
                   double *fs);

#endif
//
// File trailer for pingpu.h
//
// [EOF]
//
