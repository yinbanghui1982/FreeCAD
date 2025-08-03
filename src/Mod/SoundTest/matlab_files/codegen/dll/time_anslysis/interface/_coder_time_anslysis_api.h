//
// File: _coder_time_anslysis_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

#ifndef _CODER_TIME_ANSLYSIS_API_H
#define _CODER_TIME_ANSLYSIS_API_H

// Include Files
#include "time_anslysis_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void time_anslysis(coder::array<real_T, 2U> *sig, real_T *rms2, real_T *mean2,
                   real_T *max_abs, real_T *mean_abs, real_T *rms_abs,
                   real_T *var2, real_T *std2, real_T *spl, real_T *ppv);

void time_anslysis_api(const mxArray *prhs, int32_T nlhs,
                       const mxArray *plhs[9]);

void time_anslysis_atexit();

void time_anslysis_initialize();

void time_anslysis_terminate();

void time_anslysis_xil_shutdown();

void time_anslysis_xil_terminate();

#endif
//
// File trailer for _coder_time_anslysis_api.h
//
// [EOF]
//
