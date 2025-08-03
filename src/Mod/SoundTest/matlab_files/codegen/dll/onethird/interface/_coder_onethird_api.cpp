//
// File: _coder_onethird_api.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

// Include Files
#include "_coder_onethird_api.h"
#include "_coder_onethird_mex.h"
#include "coder_array_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131626U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "onethird",                                           // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<real_T, 2U> &ret);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<real_T, 1U> &ret);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *t,
                             const char_T *identifier,
                             coder::array<real_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<real_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                             const char_T *identifier,
                             coder::array<real_T, 1U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<real_T, 1U> &y);

static const mxArray *emlrt_marshallOut(const coder::array<real_T, 1U> &u);

static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u);

static const mxArray *emlrt_marshallOut(const real_T u[30]);

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
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<real_T, 1U> &ret
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<real_T, 1U> &ret)
{
  static const int32_T dims{-1};
  int32_T i;
  const boolean_T b{true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                            false, 1U, (void *)&dims, &b, &i);
  ret.prealloc(i);
  ret.set_size(i);
  ret.set(static_cast<real_T *>(emlrtMxGetData(src)), ret.size(0));
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *t
//                const char_T *identifier
//                coder::array<real_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *t,
                             const char_T *identifier,
                             coder::array<real_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(t), &thisId, y);
  emlrtDestroyArray(&t);
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
// Arguments    : const emlrtStack *sp
//                const mxArray *x
//                const char_T *identifier
//                coder::array<real_T, 1U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                             const char_T *identifier,
                             coder::array<real_T, 1U> &y)
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
//                coder::array<real_T, 1U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<real_T, 1U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const coder::array<real_T, 1U> &u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const coder::array<real_T, 1U> &u)
{
  static const int32_T i{0};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &(((coder::array<real_T, 1U> *)&u)->data())[0]);
  emlrtSetDimensions((mxArray *)m, ((coder::array<real_T, 1U> *)&u)->size(), 1);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const coder::array<real_T, 2U> &u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const coder::array<real_T, 2U> &u)
{
  static const int32_T iv[2]{0, 0};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &(((coder::array<real_T, 2U> *)&u)->data())[0]);
  emlrtSetDimensions((mxArray *)m, ((coder::array<real_T, 2U> *)&u)->size(), 2);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const real_T u[30]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u[30])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 30};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
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
// Arguments    : const mxArray * const prhs[2]
//                int32_T nlhs
//                const mxArray *plhs[6]
// Return Type  : void
//
void onethird_api(const mxArray *const prhs[2], int32_T nlhs,
                  const mxArray *plhs[6])
{
  coder::array<real_T, 2U> f;
  coder::array<real_T, 2U> t;
  coder::array<real_T, 1U> Ya_1;
  coder::array<real_T, 1U> x;
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*Ya_2)[30];
  real_T(*fc)[30];
  real_T nc;
  real_T nfft;
  st.tls = emlrtRootTLSGlobal;
  Ya_2 = (real_T(*)[30])mxMalloc(sizeof(real_T[30]));
  fc = (real_T(*)[30])mxMalloc(sizeof(real_T[30]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  // Marshall function inputs
  t.no_free();
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "t", t);
  x.no_free();
  emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "x", x);
  // Invoke the target function
  onethird(t, x, Ya_1, *Ya_2, f, *fc, &nfft, &nc);
  // Marshall function outputs
  Ya_1.no_free();
  plhs[0] = emlrt_marshallOut(Ya_1);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*Ya_2);
  }
  if (nlhs > 2) {
    f.no_free();
    plhs[2] = emlrt_marshallOut(f);
  }
  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(*fc);
  }
  if (nlhs > 4) {
    plhs[4] = emlrt_marshallOut(nfft);
  }
  if (nlhs > 5) {
    plhs[5] = emlrt_marshallOut(nc);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : void
// Return Type  : void
//
void onethird_atexit()
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
  onethird_xil_terminate();
  onethird_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void onethird_initialize()
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
void onethird_terminate()
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
// File trailer for _coder_onethird_api.cpp
//
// [EOF]
//
