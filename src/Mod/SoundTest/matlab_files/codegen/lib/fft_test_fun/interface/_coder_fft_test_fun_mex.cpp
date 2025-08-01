//
// File: _coder_fft_test_fun_mex.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Nov-2023 22:00:14
//

// Include Files
#include "_coder_fft_test_fun_mex.h"
#include "_coder_fft_test_fun_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&fft_test_fun_atexit);
  // Module initialization.
  fft_test_fun_initialize();
  // Dispatch the entry-point.
  unsafe_fft_test_fun_mexFunction(nlhs, plhs, nrhs, prhs);
  // Module termination.
  fft_test_fun_terminate();
}

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, (const char_T *)"GBK", true);
  return emlrtRootTLSGlobal;
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[1]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_fft_test_fun_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                     int32_T nrhs, const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        12, "fft_test_fun");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 12,
                        "fft_test_fun");
  }
  // Call the function.
  fft_test_fun_api(prhs[0], &outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

//
// File trailer for _coder_fft_test_fun_mex.cpp
//
// [EOF]
//
