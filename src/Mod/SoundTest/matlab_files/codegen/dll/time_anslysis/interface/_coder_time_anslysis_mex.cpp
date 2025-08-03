//
// File: _coder_time_anslysis_mex.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

// Include Files
#include "_coder_time_anslysis_mex.h"
#include "_coder_time_anslysis_api.h"

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
  mexAtExit(&time_anslysis_atexit);
  // Module initialization.
  time_anslysis_initialize();
  // Dispatch the entry-point.
  unsafe_time_anslysis_mexFunction(nlhs, plhs, nrhs, prhs);
  // Module termination.
  time_anslysis_terminate();
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
//                mxArray *plhs[9]
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_time_anslysis_mexFunction(int32_T nlhs, mxArray *plhs[9],
                                      int32_T nrhs, const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs[9];
  int32_T b_nlhs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        13, "time_anslysis");
  }
  if (nlhs > 9) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "time_anslysis");
  }
  // Call the function.
  time_anslysis_api(prhs[0], nlhs, outputs);
  // Copy over outputs to the caller.
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }
  emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

//
// File trailer for _coder_time_anslysis_mex.cpp
//
// [EOF]
//
