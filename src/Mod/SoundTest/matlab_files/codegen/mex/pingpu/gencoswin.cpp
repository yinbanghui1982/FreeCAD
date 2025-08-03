//
// gencoswin.cpp
//
// Code generation for function 'gencoswin'
//

// Include files
#include "gencoswin.h"
#include "eml_int_forloop_overflow_check.h"
#include "pingpu_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo m_emlrtRSI{
    77,            // lineNo
    "calc_window", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\signal\\signal\\private\\gencoswin.m" // pathName
};

static emlrtRSInfo
    n_emlrtRSI{
        11,    // lineNo
        "cos", // fcnName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\elfun\\cos.m" // pathName
    };

static emlrtRTEInfo
    s_emlrtRTEI{
        76,                  // lineNo
        9,                   // colNo
        "eml_mtimes_helper", // fName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_"
        "helper.m" // pName
    };

// Function Definitions
namespace coder {
void calc_window(const emlrtStack *sp, real_T m, real_T n,
                 ::coder::array<real_T, 1U> &w)
{
  array<real_T, 2U> y;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  int32_T nx;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  if (m - 1.0 < 0.0) {
    y.set_size(&h_emlrtRTEI, sp, 1, 0);
  } else {
    y.set_size(&h_emlrtRTEI, sp, 1, static_cast<int32_T>(m - 1.0) + 1);
    nx = static_cast<int32_T>(m - 1.0);
    for (int32_T k{0}; k <= nx; k++) {
      y[k] = k;
    }
  }
  w.set_size(&s_emlrtRTEI, sp, y.size(1));
  nx = y.size(1);
  for (int32_T k{0}; k < nx; k++) {
    w[k] = 6.2831853071795862 * (y[k] / (n - 1.0));
  }
  st.site = &m_emlrtRSI;
  b_st.site = &n_emlrtRSI;
  nx = w.size(0);
  c_st.site = &o_emlrtRSI;
  if (w.size(0) > 2147483646) {
    d_st.site = &p_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }
  for (int32_T k{0}; k < nx; k++) {
    w[k] = muDoubleScalarCos(w[k]);
  }
  nx = w.size(0);
  for (int32_T k{0}; k < nx; k++) {
    w[k] = 0.5 - 0.5 * w[k];
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

} // namespace coder

// End of code generation (gencoswin.cpp)
