//
// File: _coder_onethird_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

#ifndef _CODER_ONETHIRD_API_H
#define _CODER_ONETHIRD_API_H

// Include Files
#include "onethird_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void onethird(coder::array<real_T, 2U> *t, coder::array<real_T, 1U> *x,
              coder::array<real_T, 1U> *Ya_1, real_T Ya_2[30],
              coder::array<real_T, 2U> *f, real_T fc[30], real_T *nfft,
              real_T *nc);

void onethird_api(const mxArray *const prhs[2], int32_T nlhs,
                  const mxArray *plhs[6]);

void onethird_atexit();

void onethird_initialize();

void onethird_terminate();

void onethird_xil_shutdown();

void onethird_xil_terminate();

#endif
//
// File trailer for _coder_onethird_api.h
//
// [EOF]
//
