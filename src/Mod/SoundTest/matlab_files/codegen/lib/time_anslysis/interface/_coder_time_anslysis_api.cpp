//
// File: _coder_time_anslysis_api.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-May-2024 10:15:24
//

// Include Files
#include "_coder_time_anslysis_api.h"
#include "_coder_time_anslysis_mex.h"
#include "coder_array_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131626U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "time_anslysis",                                      // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<real_T, 2U> &ret);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *sig,
                             const char_T *identifier,
                             coder::array<real_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<real_T, 2U> &y);

static const mxArray *emlrt_marshallOut(const real_T u);

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 2U> &ret
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<real_T, 2U> &ret)
{
  static const int32_T dims[2]{1, -1};
  int32_T iv[2];
  const boolean_T bv[2]{false, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                            false, 2U, (void *)&dims[0], &bv[0], &iv[0]);
  ret.prealloc(iv[0] * iv[1]);
  ret.set_size(iv[0], iv[1]);
  ret.set(static_cast<real_T *>(emlrtMxGetData(src)), ret.size(0), ret.size(1));
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *sig
//                const char_T *identifier
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *sig,
                             const char_T *identifier,
                             coder::array<real_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(sig), &thisId, y);
  emlrtDestroyArray(&sig);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<real_T, 2U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const real_T u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const mxArray *prhs
//                int32_T nlhs
//                const mxArray *plhs[9]
// Return Type  : void
//
void time_anslysis_api(const mxArray *prhs, int32_T nlhs,
                       const mxArray *plhs[9])
{
  coder::array<real_T, 2U> sig;
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T max_abs;
  real_T mean2;
  real_T mean_abs;
  real_T ppv;
  real_T rms2;
  real_T rms_abs;
  real_T spl;
  real_T std2;
  real_T var2;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  // Marshall function inputs
  sig.no_free();
  emlrt_marshallIn(&st, emlrtAlias(prhs), "sig", sig);
  // Invoke the target function
  time_anslysis(sig, &rms2, &mean2, &max_abs, &mean_abs, &rms_abs, &var2, &std2,
                &spl, &ppv);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(rms2);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(mean2);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(max_abs);
  }
  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(mean_abs);
  }
  if (nlhs > 4) {
    plhs[4] = emlrt_marshallOut(rms_abs);
  }
  if (nlhs > 5) {
    plhs[5] = emlrt_marshallOut(var2);
  }
  if (nlhs > 6) {
    plhs[6] = emlrt_marshallOut(std2);
  }
  if (nlhs > 7) {
    plhs[7] = emlrt_marshallOut(spl);
  }
  if (nlhs > 8) {
    plhs[8] = emlrt_marshallOut(ppv);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : void
// Return Type  : void
//
void time_anslysis_atexit()
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
  time_anslysis_xil_terminate();
  time_anslysis_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void time_anslysis_initialize()
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
void time_anslysis_terminate()
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
// File trailer for _coder_time_anslysis_api.cpp
//
// [EOF]
//
