//
// File: _coder_daopu_analysis_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:57:41
//

#ifndef _CODER_DAOPU_ANALYSIS_API_H
#define _CODER_DAOPU_ANALYSIS_API_H

// Include Files
#include "daopu_analysis_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void daopu_analysis(coder::array<real_T, 2U> *y, coder::array<creal_T, 2U> *z);

void daopu_analysis_api(const mxArray *prhs, const mxArray **plhs);

void daopu_analysis_atexit();

void daopu_analysis_initialize();

void daopu_analysis_terminate();

void daopu_analysis_xil_shutdown();

void daopu_analysis_xil_terminate();

#endif
//
// File trailer for _coder_daopu_analysis_api.h
//
// [EOF]
//
