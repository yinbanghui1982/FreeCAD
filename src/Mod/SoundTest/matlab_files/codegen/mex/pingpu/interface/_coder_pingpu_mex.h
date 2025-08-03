//
// _coder_pingpu_mex.h
//
// Code generation for function '_coder_pingpu_mex'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void pingpu_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                        const mxArray *prhs[3]);

// End of code generation (_coder_pingpu_mex.h)
