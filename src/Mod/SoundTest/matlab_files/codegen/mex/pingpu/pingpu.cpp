//
// pingpu.cpp
//
// Code generation for function 'pingpu'
//

// Include files
#include "pingpu.h"
#include "eml_int_forloop_overflow_check.h"
#include "gencoswin.h"
#include "indexShapeCheck.h"
#include "pingpu_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo emlrtRSI{
    4,        // lineNo
    "pingpu", // fcnName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pathName
};

static emlrtRSInfo b_emlrtRSI{
    13,       // lineNo
    "pingpu", // fcnName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pathName
};

static emlrtRSInfo c_emlrtRSI{
    15,       // lineNo
    "pingpu", // fcnName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pathName
};

static emlrtRSInfo d_emlrtRSI{
    38,     // lineNo
    "hann", // fcnName
    "D:\\Program Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\hann.m" // pathName
};

static emlrtRSInfo e_emlrtRSI{
    21,          // lineNo
    "gencoswin", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo f_emlrtRSI{
    43,          // lineNo
    "gencoswin", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo g_emlrtRSI{
    53,           // lineNo
    "sym_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo h_emlrtRSI{
    56,           // lineNo
    "sym_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo i_emlrtRSI{
    57,           // lineNo
    "sym_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo j_emlrtRSI{
    61,           // lineNo
    "sym_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo k_emlrtRSI{
    62,           // lineNo
    "sym_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo l_emlrtRSI{
    9,        // lineNo
    "iseven", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\iseven.m" // pathName
};

static emlrtRSInfo r_emlrtRSI{
    63,    // lineNo
    "fft", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m" // pathName
};

static emlrtRSInfo
    s_emlrtRSI{
        31,    // lineNo
        "fft", // fcnName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
        "fft\\fft.m" // pathName
    };

static emlrtRSInfo
    t_emlrtRSI{
        58,                // lineNo
        "executeCallback", // fcnName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
        "fft\\fft.m" // pathName
    };

static emlrtRSInfo u_emlrtRSI{
    44,                        // lineNo
    "Custom1DFFTCallback/fft", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

static emlrtRSInfo v_emlrtRSI{
    54,                            // lineNo
    "Custom1DFFTCallback/fftLoop", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

static emlrtRSInfo
    y_emlrtRSI{
        18,    // lineNo
        "abs", // fcnName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\elfun\\abs.m" // pathName
    };

static emlrtRSInfo ab_emlrtRSI{
    74,                    // lineNo
    "applyScalarFunction", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunction.m" // pathName
};

static emlrtRSInfo bb_emlrtRSI{
    17,      // lineNo
    "log10", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\elfun\\log10.m" // pathName
};

static emlrtECInfo emlrtECI{
    2,        // nDims
    6,        // lineNo
    12,       // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtBCInfo emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    9,        // lineNo
    12,       // colNo
    "time",   // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo b_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    9,        // lineNo
    20,       // colNo
    "time",   // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo c_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    13,       // lineNo
    14,       // colNo
    "data",   // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo d_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    13,       // lineNo
    16,       // colNo
    "data",   // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo e_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    17,       // lineNo
    5,        // colNo
    "f",      // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtDCInfo emlrtDCI{
    17,       // lineNo
    7,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    1                                                  // checkKind
};

static emlrtBCInfo f_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    17,       // lineNo
    7,        // colNo
    "f",      // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo g_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    18,       // lineNo
    5,        // colNo
    "Y",      // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtDCInfo b_emlrtDCI{
    18,       // lineNo
    7,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    1                                                  // checkKind
};

static emlrtBCInfo h_emlrtBCI{
    -1,       // iFirst
    -1,       // iLast
    18,       // lineNo
    7,        // colNo
    "Y",      // aName
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m", // pName
    0                                                  // checkKind
};

static emlrtBCInfo i_emlrtBCI{
    -1,           // iFirst
    -1,           // iLast
    62,           // lineNo
    15,           // colNo
    "",           // aName
    "sym_window", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m", // pName
    0 // checkKind
};

static emlrtBCInfo j_emlrtBCI{
    -1,           // iFirst
    -1,           // iLast
    62,           // lineNo
    24,           // colNo
    "",           // aName
    "sym_window", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m", // pName
    0 // checkKind
};

static emlrtRTEInfo d_emlrtRTEI{
    4,        // lineNo
    5,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo e_emlrtRTEI{
    62,          // lineNo
    9,           // colNo
    "gencoswin", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pName
};

static emlrtRTEInfo f_emlrtRTEI{
    57,          // lineNo
    9,           // colNo
    "gencoswin", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pName
};

static emlrtRTEInfo g_emlrtRTEI{
    6,        // lineNo
    5,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo i_emlrtRTEI{
    12,       // lineNo
    1,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo j_emlrtRTEI{
    13,       // lineNo
    9,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo k_emlrtRTEI{
    26,                   // lineNo
    32,                   // colNo
    "MATLABFFTWCallback", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "fft\\MATLABFFTWCallback.m" // pName
};

static emlrtRTEInfo l_emlrtRTEI{
    13,       // lineNo
    5,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo m_emlrtRTEI{
    13,       // lineNo
    1,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo n_emlrtRTEI{
    30,                    // lineNo
    21,                    // colNo
    "applyScalarFunction", // fName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunction.m" // pName
};

static emlrtRTEInfo o_emlrtRTEI{
    15,       // lineNo
    12,       // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo p_emlrtRTEI{
    15,       // lineNo
    1,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo q_emlrtRTEI{
    17,       // lineNo
    1,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo r_emlrtRTEI{
    18,       // lineNo
    1,        // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRTEInfo t_emlrtRTEI{
    6,        // lineNo
    12,       // colNo
    "pingpu", // fName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pName
};

static emlrtRSInfo cb_emlrtRSI{
    6,        // lineNo
    "pingpu", // fcnName
    "D:\\work_share\\yinjian\\sound_test\\sound_test_software\\sound_"
    "test\\sound_test_window\\matlab_files\\pingpu.m" // pathName
};

// Function Declarations
static void binary_expand_op(const emlrtStack *sp,
                             coder::array<real_T, 2U> &in1,
                             const coder::array<real_T, 1U> &in2);

static int32_T div_s32(const emlrtStack *sp, int32_T numerator,
                       int32_T denominator);

// Function Definitions
static void binary_expand_op(const emlrtStack *sp,
                             coder::array<real_T, 2U> &in1,
                             const coder::array<real_T, 1U> &in2)
{
  coder::array<real_T, 2U> b_in1;
  int32_T i;
  int32_T loop_ub;
  int32_T stride_0_1;
  int32_T stride_1_1;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  if (in2.size(0) == 1) {
    i = in1.size(1);
  } else {
    i = in2.size(0);
  }
  b_in1.set_size(&t_emlrtRTEI, sp, 1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in2.size(0) != 1);
  if (in2.size(0) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_1] * in2[i * stride_1_1];
  }
  in1.set_size(&g_emlrtRTEI, sp, 1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

static int32_T div_s32(const emlrtStack *sp, int32_T numerator,
                       int32_T denominator)
{
  int32_T quotient;
  if (denominator == 0) {
    emlrtDivisionByZeroErrorR2012b(nullptr, (emlrtConstCTX)sp);
  } else {
    uint32_T tempAbsQuotient;
    uint32_T u;
    if (numerator < 0) {
      tempAbsQuotient = ~static_cast<uint32_T>(numerator) + 1U;
    } else {
      tempAbsQuotient = static_cast<uint32_T>(numerator);
    }
    if (denominator < 0) {
      u = ~static_cast<uint32_T>(denominator) + 1U;
    } else {
      u = static_cast<uint32_T>(denominator);
    }
    tempAbsQuotient /= u;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int32_T>(tempAbsQuotient);
    } else {
      quotient = static_cast<int32_T>(tempAbsQuotient);
    }
  }
  return quotient;
}

void pingpu(const emlrtStack *sp, const coder::array<real_T, 2U> &b_time,
            coder::array<real_T, 2U> &data, real_T w,
            coder::array<real_T, 2U> &f, coder::array<real_T, 2U> &Y,
            real_T *fs)
{
  coder::array<creal_T, 2U> b_Y;
  coder::array<real_T, 2U> x;
  coder::array<real_T, 1U> b_window;
  coder::array<real_T, 1U> window;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  real_T b;
  real_T y;
  int32_T i;
  int32_T nx;
  int32_T trivialwin;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  covrtLogFcn(&emlrtCoverageInstance, 0, 0);
  if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 0, w == 1.0)) {
    int8_T w_data;
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 0);
    //  汉宁窗
    st.site = &emlrtRSI;
    b_st.site = &d_emlrtRSI;
    c_st.site = &e_emlrtRSI;
    nx = 1;
    w_data = 0;
    trivialwin = 0;
    if (data.size(1) == 0) {
      nx = 0;
      trivialwin = 1;
    } else if (data.size(1) == 1) {
      w_data = 1;
      trivialwin = 1;
    }
    window.set_size(&d_emlrtRTEI, &b_st, nx);
    for (i = 0; i < nx; i++) {
      window[0] = w_data;
    }
    if (trivialwin == 0) {
      c_st.site = &f_emlrtRSI;
      d_st.site = &g_emlrtRSI;
      e_st.site = &l_emlrtRSI;
      if (data.size(1) == 0) {
        i = 0;
      } else {
        i = static_cast<int32_T>(
            muDoubleScalarRem(static_cast<real_T>(data.size(1)), 2.0));
      }
      if (i == 0.0) {
        int32_T iv[2];
        int32_T i1;
        int32_T loop_ub;
        d_st.site = &h_emlrtRSI;
        coder::calc_window(&d_st, static_cast<real_T>(data.size(1)) / 2.0,
                           static_cast<real_T>(data.size(1)), window);
        if (window.size(0) < 1) {
          i = 0;
          nx = 1;
          i1 = -1;
        } else {
          i = window.size(0) - 1;
          nx = -1;
          i1 = 0;
        }
        iv[0] = 1;
        d_st.site = &i_emlrtRSI;
        trivialwin = div_s32(&d_st, i1 - i, nx);
        iv[1] = trivialwin + 1;
        d_st.site = &i_emlrtRSI;
        coder::internal::indexShapeCheck(&d_st, window.size(0), iv);
        b_window.set_size(&f_emlrtRTEI, &c_st,
                          (window.size(0) + trivialwin) + 1);
        loop_ub = window.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_window[i1] = window[i1];
        }
        for (i1 = 0; i1 <= trivialwin; i1++) {
          b_window[i1 + window.size(0)] = window[i + nx * i1];
        }
        window.set_size(&d_emlrtRTEI, &c_st, b_window.size(0));
        trivialwin = b_window.size(0);
        for (i = 0; i < trivialwin; i++) {
          window[i] = b_window[i];
        }
      } else {
        int32_T iv[2];
        int32_T i1;
        int32_T loop_ub;
        d_st.site = &j_emlrtRSI;
        coder::calc_window(&d_st,
                           (static_cast<real_T>(data.size(1)) + 1.0) / 2.0,
                           static_cast<real_T>(data.size(1)), window);
        if (window.size(0) - 1 < 1) {
          i = 0;
          nx = 1;
          i1 = -1;
        } else {
          if ((window.size(0) - 1 < 1) ||
              (window.size(0) - 1 > window.size(0))) {
            emlrtDynamicBoundsCheckR2012b(window.size(0) - 1, 1, window.size(0),
                                          &i_emlrtBCI, &c_st);
          }
          i = window.size(0) - 2;
          nx = -1;
          if (window.size(0) < 1) {
            emlrtDynamicBoundsCheckR2012b(1, 1, window.size(0), &j_emlrtBCI,
                                          &c_st);
          }
          i1 = 0;
        }
        iv[0] = 1;
        d_st.site = &k_emlrtRSI;
        trivialwin = div_s32(&d_st, i1 - i, nx);
        iv[1] = trivialwin + 1;
        d_st.site = &k_emlrtRSI;
        coder::internal::indexShapeCheck(&d_st, window.size(0), iv);
        b_window.set_size(&e_emlrtRTEI, &c_st,
                          (window.size(0) + trivialwin) + 1);
        loop_ub = window.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_window[i1] = window[i1];
        }
        for (i1 = 0; i1 <= trivialwin; i1++) {
          b_window[i1 + window.size(0)] = window[i + nx * i1];
        }
        window.set_size(&d_emlrtRTEI, &c_st, b_window.size(0));
        trivialwin = b_window.size(0);
        for (i = 0; i < trivialwin; i++) {
          window[i] = b_window[i];
        }
      }
    }
    //  汉宁窗
    if ((window.size(0) != data.size(1)) &&
        ((data.size(1) != 1) && (window.size(0) != 1))) {
      emlrtDimSizeImpxCheckR2021b(data.size(1), window.size(0), &emlrtECI,
                                  (emlrtConstCTX)sp);
    }
    if (window.size(0) == data.size(1)) {
      data.set_size(&g_emlrtRTEI, sp, 1, data.size(1));
      trivialwin = data.size(1);
      for (i = 0; i < trivialwin; i++) {
        data[i] = data[i] * window[i];
      }
    } else {
      st.site = &cb_emlrtRSI;
      binary_expand_op(&st, data, window);
    }
  }
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 1);
  if (b_time.size(1) < 2) {
    emlrtDynamicBoundsCheckR2012b(2, 1, b_time.size(1), &emlrtBCI,
                                  (emlrtConstCTX)sp);
  }
  if (b_time.size(1) < 1) {
    emlrtDynamicBoundsCheckR2012b(1, 1, b_time.size(1), &b_emlrtBCI,
                                  (emlrtConstCTX)sp);
  }
  *fs = 1.0 / (b_time[1] - b_time[0]);
  // 样点个数
  b = *fs / (static_cast<real_T>(b_time.size(1)) - 1.0);
  // 分辨率
  if (b_time.size(1) - 1 < 0) {
    f.set_size(&h_emlrtRTEI, sp, f.size(0), 0);
  } else {
    f.set_size(&h_emlrtRTEI, sp, 1, b_time.size(1));
    trivialwin = b_time.size(1) - 1;
    for (i = 0; i <= trivialwin; i++) {
      f[i] = i;
    }
  }
  f.set_size(&i_emlrtRTEI, sp, 1, f.size(1));
  trivialwin = f.size(1) - 1;
  for (i = 0; i <= trivialwin; i++) {
    f[i] = f[i] * b;
  }
  // 其中每点的频率，第一个点对应的频率为0
  if (b_time.size(1) < 1) {
    trivialwin = 0;
  } else {
    if (data.size(1) < 1) {
      emlrtDynamicBoundsCheckR2012b(1, 1, data.size(1), &c_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (b_time.size(1) > data.size(1)) {
      emlrtDynamicBoundsCheckR2012b(b_time.size(1), 1, data.size(1),
                                    &d_emlrtBCI, (emlrtConstCTX)sp);
    }
    trivialwin = b_time.size(1);
  }
  st.site = &b_emlrtRSI;
  x.set_size(&j_emlrtRTEI, &st, 1, trivialwin);
  for (i = 0; i < trivialwin; i++) {
    x[i] = data[i];
  }
  b_st.site = &r_emlrtRSI;
  if (trivialwin == 0) {
    b_Y.set_size(&l_emlrtRTEI, &b_st, b_Y.size(0), 0);
  } else {
    c_st.site = &s_emlrtRSI;
    d_st.site = &t_emlrtRSI;
    e_st.site = &u_emlrtRSI;
    f_st.site = &v_emlrtRSI;
    emlrtFFTWSetNumThreads(8);
    b_Y.set_size(&k_emlrtRTEI, &f_st, 1, trivialwin);
    emlrtFFTW_1D_R2C(&x[0], (real_T *)&b_Y[0], 1, trivialwin, trivialwin, 1,
                     -1);
  }
  y = static_cast<real_T>(b_time.size(1)) / 2.0;
  b_Y.set_size(&m_emlrtRTEI, sp, 1, b_Y.size(1));
  trivialwin = b_Y.size(1) - 1;
  for (i = 0; i <= trivialwin; i++) {
    real_T ai;
    real_T re;
    b = b_Y[i].re;
    ai = b_Y[i].im;
    if (ai == 0.0) {
      re = b / y;
      b = 0.0;
    } else if (b == 0.0) {
      re = 0.0;
      b = ai / y;
    } else {
      re = b / y;
      b = ai / y;
    }
    b_Y[i].re = re;
    b_Y[i].im = b;
  }
  // 真实的幅值
  st.site = &c_emlrtRSI;
  b_st.site = &y_emlrtRSI;
  nx = b_Y.size(1);
  Y.set_size(&n_emlrtRTEI, &b_st, 1, b_Y.size(1));
  c_st.site = &ab_emlrtRSI;
  if (b_Y.size(1) > 2147483646) {
    d_st.site = &p_emlrtRSI;
    coder::check_forloop_overflow_error(&d_st);
  }
  for (trivialwin = 0; trivialwin < nx; trivialwin++) {
    Y[trivialwin] = muDoubleScalarHypot(b_Y[trivialwin].re, b_Y[trivialwin].im);
  }
  st.site = &c_emlrtRSI;
  Y.set_size(&o_emlrtRTEI, &st, 1, Y.size(1));
  trivialwin = Y.size(1) - 1;
  for (i = 0; i <= trivialwin; i++) {
    Y[i] = Y[i] / 2.0E-5;
  }
  b_st.site = &bb_emlrtRSI;
  nx = Y.size(1);
  c_st.site = &o_emlrtRSI;
  if (Y.size(1) > 2147483646) {
    d_st.site = &p_emlrtRSI;
    coder::check_forloop_overflow_error(&d_st);
  }
  for (trivialwin = 0; trivialwin < nx; trivialwin++) {
    Y[trivialwin] = muDoubleScalarLog10(Y[trivialwin]);
  }
  Y.set_size(&p_emlrtRTEI, sp, 1, Y.size(1));
  trivialwin = Y.size(1) - 1;
  for (i = 0; i <= trivialwin; i++) {
    Y[i] = 20.0 * Y[i];
  }
  b = static_cast<real_T>(b_time.size(1)) / 2.0;
  if (b < 1.0) {
    i = 0;
  } else {
    if (f.size(1) < 1) {
      emlrtDynamicBoundsCheckR2012b(1, 1, f.size(1), &e_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (b != muDoubleScalarFloor(b)) {
      emlrtIntegerCheckR2012b(b, &emlrtDCI, (emlrtConstCTX)sp);
    }
    if (static_cast<int32_T>(b) > f.size(1)) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, f.size(1),
                                    &f_emlrtBCI, (emlrtConstCTX)sp);
    }
    i = static_cast<int32_T>(b);
  }
  f.set_size(&q_emlrtRTEI, sp, f.size(0), i);
  b = static_cast<real_T>(b_time.size(1)) / 2.0;
  if (b < 1.0) {
    i = 0;
  } else {
    if (Y.size(1) < 1) {
      emlrtDynamicBoundsCheckR2012b(1, 1, Y.size(1), &g_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (b != muDoubleScalarFloor(b)) {
      emlrtIntegerCheckR2012b(b, &b_emlrtDCI, (emlrtConstCTX)sp);
    }
    if (static_cast<int32_T>(b) > Y.size(1)) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, Y.size(1),
                                    &h_emlrtBCI, (emlrtConstCTX)sp);
    }
    i = static_cast<int32_T>(b);
  }
  Y.set_size(&r_emlrtRTEI, sp, Y.size(0), i);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

// End of code generation (pingpu.cpp)
