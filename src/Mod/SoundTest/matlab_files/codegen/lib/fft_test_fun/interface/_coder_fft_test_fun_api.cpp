//
// File: _coder_fft_test_fun_api.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Nov-2023 22:00:14
//

// Include Files
#include "_coder_fft_test_fun_api.h"
#include "_coder_fft_test_fun_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131626U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "fft_test_fun",                                       // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[1000]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                             const char_T *identifier, real32_T y[1000]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             real32_T y[1000]);

static const mxArray *emlrt_marshallOut(const real32_T u[1000]);

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real32_T ret[1000]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[1000])
{
  static const int32_T dims[2]{1, 1000};
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src,
                          (const char_T *)"single|double", false, 2U,
                          (void *)&dims[0]);
  emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret[0], 4, false);
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *x
//                const char_T *identifier
//                real32_T y[1000]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                             const char_T *identifier, real32_T y[1000])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(x), &thisId, y);
  emlrtDestroyArray(&x);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real32_T y[1000]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             real32_T y[1000])
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const real32_T u[1000]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real32_T u[1000])
{
  static const int32_T iv[2]{1, 1000};
  const mxArray *m;
  const mxArray *y;
  real32_T *pData;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  pData = static_cast<real32_T *>(emlrtMxGetData(m));
  for (int32_T i{0}; i < 1000; i++) {
    pData[i] = u[i];
  }
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const mxArray *prhs
//                const mxArray **plhs
// Return Type  : void
//
void fft_test_fun_api(const mxArray *prhs, const mxArray **plhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real32_T x[1000];
  real32_T y[1000];
  st.tls = emlrtRootTLSGlobal;
  // Marshall function inputs
  emlrt_marshallIn(&st, emlrtAliasP(prhs), "x", x);
  // Invoke the target function
  fft_test_fun(x, y);
  // Marshall function outputs
  *plhs = emlrt_marshallOut(y);
}

//
// Arguments    : void
// Return Type  : void
//
void fft_test_fun_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  fft_test_fun_xil_terminate();
  fft_test_fun_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void fft_test_fun_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void fft_test_fun_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_fft_test_fun_api.cpp
//
// [EOF]
//
