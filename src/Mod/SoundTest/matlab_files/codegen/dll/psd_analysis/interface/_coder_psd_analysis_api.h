//
// File: _coder_psd_analysis_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:01:53
//

#ifndef _CODER_PSD_ANALYSIS_API_H
#define _CODER_PSD_ANALYSIS_API_H

// Include Files
#include "psd_analysis_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void psd_analysis(coder::array<real_T, 1U> *noise, real_T N, real_T Fs,
                  coder::array<real_T, 2U> *psdestx,
                  coder::array<real_T, 1U> *Fxx);

void psd_analysis_api(const mxArray *const prhs[3], int32_T nlhs,
                      const mxArray *plhs[2]);

void psd_analysis_atexit();

void psd_analysis_initialize();

void psd_analysis_terminate();

void psd_analysis_xil_shutdown();

void psd_analysis_xil_terminate();

#endif
//
// File trailer for _coder_psd_analysis_api.h
//
// [EOF]
//
