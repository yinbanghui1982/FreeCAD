//
// File: _coder_pingpu_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:00:28
//

#ifndef _CODER_PINGPU_API_H
#define _CODER_PINGPU_API_H

// Include Files
#include "pingpu_spec.h"
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void pingpu(coder::array<real_T, 2U> *b_time, coder::array<real_T, 2U> *data,
            real_T w, coder::array<real_T, 2U> *f, coder::array<real_T, 2U> *Y,
            real_T *fs);

void pingpu_api(const mxArray *const prhs[3], int32_T nlhs,
                const mxArray *plhs[3]);

void pingpu_atexit();

void pingpu_initialize();

void pingpu_terminate();

void pingpu_xil_shutdown();

void pingpu_xil_terminate();

#endif
//
// File trailer for _coder_pingpu_api.h
//
// [EOF]
//
