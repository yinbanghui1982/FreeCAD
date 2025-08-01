//
// File: _coder_fft_test_fun_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Nov-2023 22:00:14
//

#ifndef _CODER_FFT_TEST_FUN_API_H
#define _CODER_FFT_TEST_FUN_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void fft_test_fun(real32_T x[1000], real32_T y[1000]);

void fft_test_fun_api(const mxArray *prhs, const mxArray **plhs);

void fft_test_fun_atexit();

void fft_test_fun_initialize();

void fft_test_fun_terminate();

void fft_test_fun_xil_shutdown();

void fft_test_fun_xil_terminate();

#endif
//
// File trailer for _coder_fft_test_fun_api.h
//
// [EOF]
//
