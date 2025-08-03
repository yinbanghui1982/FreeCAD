//
// gencoswin.h
//
// Code generation for function 'gencoswin'
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
namespace coder {
void calc_window(const emlrtStack *sp, real_T m, real_T n,
                 ::coder::array<real_T, 1U> &w);

}

// End of code generation (gencoswin.h)
