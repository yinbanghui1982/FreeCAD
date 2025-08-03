//
// File: _coder_cpsd_analysis_mex.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

#ifndef _CODER_CPSD_ANALYSIS_MEX_H
#define _CODER_CPSD_ANALYSIS_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_cpsd_analysis_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                      int32_T nrhs, const mxArray *prhs[3]);

#endif
//
// File trailer for _coder_cpsd_analysis_mex.h
//
// [EOF]
//
