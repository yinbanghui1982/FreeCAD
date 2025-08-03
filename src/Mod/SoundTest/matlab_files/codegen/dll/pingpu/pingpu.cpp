//
// File: pingpu.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:00:28
//

// Include Files
#include "pingpu.h"
#include "FFTImplementationCallback.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 1U> &in2);

static int div_s32(int numerator, int denominator);

static double rt_hypotd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 1U> &in2
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 1U> &in2)
{
  coder::array<double, 2U> b_in1;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in2.size(0) == 1) {
    i = in1.size(1);
  } else {
    i = in2.size(0);
  }
  b_in1.set_size(1, i);
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
  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int b_denominator;
    unsigned int b_numerator;
    if (numerator < 0) {
      b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      b_numerator = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      b_denominator = static_cast<unsigned int>(denominator);
    }
    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int>(b_numerator);
    } else {
      quotient = static_cast<int>(b_numerator);
    }
  }
  return quotient;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else if (!std::isnan(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

//
// Arguments    : const coder::array<double, 2U> &b_time
//                coder::array<double, 2U> &data
//                double w
//                coder::array<double, 2U> &f
//                coder::array<double, 2U> &Y
//                double *fs
// Return Type  : void
//
void pingpu(const coder::array<double, 2U> &b_time,
            coder::array<double, 2U> &data, double w,
            coder::array<double, 2U> &f, coder::array<double, 2U> &Y,
            double *fs)
{
  coder::array<creal_T, 2U> b_Y;
  coder::array<creal_T, 1U> yCol;
  coder::array<double, 2U> b_data;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 1U> b_window;
  coder::array<double, 1U> window;
  coder::array<int, 2U> y;
  double b_y;
  double m;
  int i;
  int k;
  int n;
  int nx;
  int pmin;
  int pow2p;
  if (w == 1.0) {
    signed char w_data;
    //  汉宁窗
    nx = 1;
    w_data = 0;
    pmin = 0;
    pow2p = data.size(1);
    if (data.size(1) == 0) {
      nx = 0;
      pmin = 1;
    } else if (data.size(1) == 1) {
      w_data = 1;
      pmin = 1;
    }
    window.set_size(nx);
    for (i = 0; i < nx; i++) {
      window[0] = w_data;
    }
    if (pmin == 0) {
      if (data.size(1) == 0) {
        i = 0;
      } else {
        i = static_cast<int>(std::fmod(static_cast<double>(data.size(1)), 2.0));
      }
      if (i == 0.0) {
        m = static_cast<double>(data.size(1)) / 2.0;
        if (m - 1.0 < 0.0) {
          y.set_size(1, 0);
        } else {
          y.set_size(1, static_cast<int>(m - 1.0) + 1);
          pmin = static_cast<int>(m - 1.0);
          for (i = 0; i <= pmin; i++) {
            y[i] = i;
          }
        }
        window.set_size(y.size(1));
        pmin = y.size(1);
        for (i = 0; i < pmin; i++) {
          window[i] = 6.2831853071795862 * (static_cast<double>(y[i]) /
                                            (static_cast<double>(pow2p) - 1.0));
        }
        nx = window.size(0);
        for (k = 0; k < nx; k++) {
          window[k] = std::cos(window[k]);
        }
        pmin = window.size(0);
        for (i = 0; i < pmin; i++) {
          window[i] = 0.5 - 0.5 * window[i];
        }
        if (window.size(0) < 1) {
          i = 0;
          pow2p = 1;
          n = -1;
        } else {
          i = window.size(0) - 1;
          pow2p = -1;
          n = 0;
        }
        pmin = div_s32(n - i, pow2p);
        b_window.set_size((window.size(0) + pmin) + 1);
        nx = window.size(0);
        for (n = 0; n < nx; n++) {
          b_window[n] = window[n];
        }
        for (n = 0; n <= pmin; n++) {
          b_window[n + window.size(0)] = window[i + pow2p * n];
        }
        window.set_size(b_window.size(0));
        pmin = b_window.size(0);
        for (i = 0; i < pmin; i++) {
          window[i] = b_window[i];
        }
      } else {
        m = (static_cast<double>(data.size(1)) + 1.0) / 2.0;
        if (m - 1.0 < 0.0) {
          y.set_size(1, 0);
        } else {
          y.set_size(1, static_cast<int>(m - 1.0) + 1);
          pmin = static_cast<int>(m - 1.0);
          for (i = 0; i <= pmin; i++) {
            y[i] = i;
          }
        }
        window.set_size(y.size(1));
        pmin = y.size(1);
        for (i = 0; i < pmin; i++) {
          window[i] = 6.2831853071795862 * (static_cast<double>(y[i]) /
                                            (static_cast<double>(pow2p) - 1.0));
        }
        nx = window.size(0);
        for (k = 0; k < nx; k++) {
          window[k] = std::cos(window[k]);
        }
        pmin = window.size(0);
        for (i = 0; i < pmin; i++) {
          window[i] = 0.5 - 0.5 * window[i];
        }
        if (window.size(0) - 1 < 1) {
          i = 0;
          pow2p = 1;
          n = -1;
        } else {
          i = window.size(0) - 2;
          pow2p = -1;
          n = 0;
        }
        pmin = div_s32(n - i, pow2p);
        b_window.set_size((window.size(0) + pmin) + 1);
        nx = window.size(0);
        for (n = 0; n < nx; n++) {
          b_window[n] = window[n];
        }
        for (n = 0; n <= pmin; n++) {
          b_window[n + window.size(0)] = window[i + pow2p * n];
        }
        window.set_size(b_window.size(0));
        pmin = b_window.size(0);
        for (i = 0; i < pmin; i++) {
          window[i] = b_window[i];
        }
      }
    }
    //  汉宁窗
    if (window.size(0) == data.size(1)) {
      data.set_size(1, data.size(1));
      pmin = data.size(1);
      for (i = 0; i < pmin; i++) {
        data[i] = data[i] * window[i];
      }
    } else {
      binary_expand_op(data, window);
    }
  }
  *fs = 1.0 / (b_time[1] - b_time[0]);
  // 样点个数
  m = *fs / (static_cast<double>(b_time.size(1)) - 1.0);
  // 分辨率
  if (b_time.size(1) - 1 < 0) {
    f.set_size(f.size(0), 0);
  } else {
    f.set_size(1, b_time.size(1));
    pmin = b_time.size(1) - 1;
    for (i = 0; i <= pmin; i++) {
      f[i] = i;
    }
  }
  f.set_size(1, f.size(1));
  pmin = f.size(1) - 1;
  for (i = 0; i <= pmin; i++) {
    f[i] = f[i] * m;
  }
  // 其中每点的频率，第一个点对应的频率为0
  if (b_time.size(1) < 1) {
    pmin = 0;
  } else {
    pmin = b_time.size(1);
  }
  b_data.set_size(1, pmin);
  for (i = 0; i < pmin; i++) {
    b_data[i] = data[i];
  }
  if (b_data.size(1) == 0) {
    b_Y.set_size(1, 0);
  } else {
    boolean_T useRadix2;
    useRadix2 = ((b_data.size(1) & (b_data.size(1) - 1)) == 0);
    pmin = 1;
    if (useRadix2) {
      nx = b_data.size(1);
    } else {
      n = (b_data.size(1) + b_data.size(1)) - 1;
      nx = 31;
      if (n <= 1) {
        nx = 0;
      } else {
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (nx - pmin > 1)) {
          k = (pmin + nx) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            nx = k;
            exitg1 = true;
          } else if (pow2p > n) {
            nx = k;
          } else {
            pmin = k;
          }
        }
      }
      pmin = 1 << nx;
      nx = pmin;
    }
    m = 6.2831853071795862 / static_cast<double>(nx);
    n = nx / 2 / 2;
    costab1q.set_size(1, n + 1);
    costab1q[0] = 1.0;
    nx = n / 2 - 1;
    for (k = 0; k <= nx; k++) {
      costab1q[k + 1] = std::cos(m * (static_cast<double>(k) + 1.0));
    }
    i = nx + 2;
    pow2p = n - 1;
    for (k = i; k <= pow2p; k++) {
      costab1q[k] = std::sin(m * static_cast<double>(n - k));
    }
    costab1q[n] = 0.0;
    if (!useRadix2) {
      n = costab1q.size(1) - 1;
      nx = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nx + 1);
      sintab.set_size(1, nx + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nx + 1);
      for (k = 0; k < n; k++) {
        sintabinv[k + 1] = costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nx; k++) {
        sintabinv[k] = costab1q[k - n];
      }
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nx; k++) {
        costab[k] = -costab1q[nx - k];
        sintab[k] = -costab1q[k - n];
      }
    } else {
      n = costab1q.size(1) - 1;
      nx = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nx + 1);
      sintab.set_size(1, nx + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nx; k++) {
        costab[k] = -costab1q[nx - k];
        sintab[k] = -costab1q[k - n];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      yCol.set_size(b_data.size(1));
      if (b_data.size(1) != 1) {
        nx = b_data.size(1);
        window = b_data.reshape(nx);
        coder::internal::fft::FFTImplementationCallback::doHalfLengthRadix2(
            window, yCol, b_data.size(1), costab, sintab);
      } else {
        yCol[0].re = b_data[0];
        yCol[0].im = 0.0;
      }
    } else {
      nx = b_data.size(1);
      window = b_data.reshape(nx);
      coder::internal::fft::FFTImplementationCallback::dobluesteinfft(
          window, pmin, b_data.size(1), costab, sintab, sintabinv, yCol);
    }
    b_Y.set_size(1, b_data.size(1));
    pmin = b_data.size(1);
    for (i = 0; i < pmin; i++) {
      b_Y[i] = yCol[i];
    }
  }
  b_y = static_cast<double>(b_time.size(1)) / 2.0;
  b_Y.set_size(1, b_Y.size(1));
  pmin = b_Y.size(1) - 1;
  for (i = 0; i <= pmin; i++) {
    double ai;
    double re;
    m = b_Y[i].re;
    ai = b_Y[i].im;
    if (ai == 0.0) {
      re = m / b_y;
      m = 0.0;
    } else if (m == 0.0) {
      re = 0.0;
      m = ai / b_y;
    } else {
      re = m / b_y;
      m = ai / b_y;
    }
    b_Y[i].re = re;
    b_Y[i].im = m;
  }
  // 真实的幅值
  nx = b_Y.size(1);
  Y.set_size(1, b_Y.size(1));
  for (k = 0; k < nx; k++) {
    Y[k] = rt_hypotd_snf(b_Y[k].re, b_Y[k].im);
  }
  Y.set_size(1, Y.size(1));
  pmin = Y.size(1) - 1;
  for (i = 0; i <= pmin; i++) {
    Y[i] = Y[i] / 2.0E-5;
  }
  nx = Y.size(1);
  for (k = 0; k < nx; k++) {
    Y[k] = std::log10(Y[k]);
  }
  Y.set_size(1, Y.size(1));
  pmin = Y.size(1) - 1;
  for (i = 0; i <= pmin; i++) {
    Y[i] = 20.0 * Y[i];
  }
  m = static_cast<double>(b_time.size(1)) / 2.0;
  if (m < 1.0) {
    nx = 0;
  } else {
    nx = static_cast<int>(m);
  }
  f.set_size(f.size(0), nx);
  m = static_cast<double>(b_time.size(1)) / 2.0;
  if (m < 1.0) {
    nx = 0;
  } else {
    nx = static_cast<int>(m);
  }
  Y.set_size(Y.size(0), nx);
}

//
// File trailer for pingpu.cpp
//
// [EOF]
//
