//
// pingpu_initialize.cpp
//
// Code generation for function 'pingpu_initialize'
//

// Include files
#include "pingpu_initialize.h"
#include "_coder_pingpu_mex.h"
#include "pingpu_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static void pingpu_once();

// Function Definitions
static void pingpu_once()
{
  mex_InitInfAndNan();
  // Allocate instance data
  covrtAllocateInstanceData(&emlrtCoverageInstance);
  // Initialize Coverage Information
  covrtScriptInit(
      &emlrtCoverageInstance,
      "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
      "test\\sound_test_window\\matlab_files\\pingpu.m",
      0U, 1U, 2U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);
  // Initialize Function Information
  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "pingpu", 0, -1, 326);
  // Initialize Basic Block Information
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 1U, 144, -1, 323);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 57, -1, 138);
  // Initialize If Information
  covrtIfInit(&emlrtCoverageInstance, 0U, 0U, 39, 46, -1, 142);
  // Initialize MCDC Information
  // Initialize For Information
  // Initialize While Information
  // Initialize Switch Information
  // Start callback for coverage engine
  covrtScriptStart(&emlrtCoverageInstance, 0U);
}

void pingpu_initialize()
{
  static const volatile char_T *emlrtBreakCheckR2012bFlagVar{nullptr};
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2022b(&st);
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtLicenseCheckR2022a(&st, "EMLRT:runTime:MexFunctionNeedsLicense",
                          "signal_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    pingpu_once();
  }
}

// End of code generation (pingpu_initialize.cpp)
