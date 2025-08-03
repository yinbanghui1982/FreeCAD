//
// pingpu.h
//
// Code generation for function 'pingpu'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
void pingpu(const emlrtStack *sp, const coder::array<real_T, 2U> &b_time,
            coder::array<real_T, 2U> &data, real_T w,
            coder::array<real_T, 2U> &f, coder::array<real_T, 2U> &Y,
            real_T *fs);

// End of code generation (pingpu.h)
