//
// File: _coder_cpsd_analysis_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

#ifndef _CODER_CPSD_ANALYSIS_API_H
#define _CODER_CPSD_ANALYSIS_API_H

// Include Files
#include "cpsd_analysis_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void cpsd_analysis(coder::array<real_T, 2U> *x, coder::array<real_T, 2U> *y,
                   real_T Fs, coder::array<real_T, 2U> *Pxy2,
                   coder::array<real_T, 2U> *arg2, coder::array<real_T, 1U> *f);

void cpsd_analysis_api(const mxArray *const prhs[3], int32_T nlhs,
                       const mxArray *plhs[3]);

void cpsd_analysis_atexit();

void cpsd_analysis_initialize();

void cpsd_analysis_terminate();

void cpsd_analysis_xil_shutdown();

void cpsd_analysis_xil_terminate();

#endif
//
// File trailer for _coder_cpsd_analysis_api.h
//
// [EOF]
//
