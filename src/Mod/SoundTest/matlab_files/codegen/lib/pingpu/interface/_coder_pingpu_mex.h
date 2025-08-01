//
// File: _coder_pingpu_mex.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 03-Dec-2023 12:42:37
//

#ifndef _CODER_PINGPU_MEX_H
#define _CODER_PINGPU_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_pingpu_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                               const mxArray *prhs[2]);

#endif
//
// File trailer for _coder_pingpu_mex.h
//
// [EOF]
//
