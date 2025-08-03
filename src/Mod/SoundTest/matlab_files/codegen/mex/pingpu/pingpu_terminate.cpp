//
// pingpu_terminate.cpp
//
// Code generation for function 'pingpu_terminate'
//

// Include files
#include "pingpu_terminate.h"
#include "_coder_pingpu_mex.h"
#include "pingpu_data.h"
#include "rt_nonfinite.h"

// Function Definitions
void pingpu_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  // Free instance data
  covrtFreeInstanceData(&emlrtCoverageInstance);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void pingpu_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (pingpu_terminate.cpp)
