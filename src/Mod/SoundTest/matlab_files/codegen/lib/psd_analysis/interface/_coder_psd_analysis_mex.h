//
// File: _coder_psd_analysis_mex.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

#ifndef _CODER_PSD_ANALYSIS_MEX_H
#define _CODER_PSD_ANALYSIS_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_psd_analysis_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                     int32_T nrhs, const mxArray *prhs[3]);

#endif
//
// File trailer for _coder_psd_analysis_mex.h
//
// [EOF]
//
