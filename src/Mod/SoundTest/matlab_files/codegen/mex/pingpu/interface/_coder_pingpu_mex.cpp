//
// _coder_pingpu_mex.cpp
//
// Code generation for function '_coder_pingpu_mex'
//

// Include files
#include "_coder_pingpu_mex.h"
#include "_coder_pingpu_api.h"
#include "pingpu_data.h"
#include "pingpu_initialize.h"
#include "pingpu_terminate.h"
#include "rt_nonfinite.h"
#include <stdexcept>

void emlrtExceptionBridge();
void emlrtExceptionBridge()
{
  throw std::runtime_error("");
}
// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&pingpu_atexit);
  // Module initialization.
  pingpu_initialize();
  try {
    // Dispatch the entry-point.
    pingpu_mexFunction(nlhs, plhs, nrhs, prhs);
    // Module termination.
    pingpu_terminate();
  } catch (...) {
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           (void *)&emlrtExceptionBridge, "GBK", true);
  return emlrtRootTLSGlobal;
}

void pingpu_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
                        const mxArray *prhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs[3];
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        6, "pingpu");
  }
  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 6,
                        "pingpu");
  }
  // Call the function.
  pingpu_api(prhs, nlhs, outputs);
  // Copy over outputs to the caller.
  if (nlhs < 1) {
    i = 1;
  } else {
    i = nlhs;
  }
  emlrtReturnArrays(i, &plhs[0], &outputs[0]);
}

// End of code generation (_coder_pingpu_mex.cpp)
