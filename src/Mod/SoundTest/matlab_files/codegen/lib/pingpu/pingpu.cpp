//
// File: pingpu.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 03-Dec-2023 12:42:37
//

// Include Files
#include "pingpu.h"
#include "FFTImplementationCallback.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions
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
// Arguments    : const coder::array<double, 1U> &b_time
//                const coder::array<double, 1U> &data
//                coder::array<double, 2U> &f
//                coder::array<double, 1U> &Y
//                double *fs
// Return Type  : void
//
void pingpu(const coder::array<double, 1U> &b_time,
            const coder::array<double, 1U> &data, coder::array<double, 2U> &f,
            coder::array<double, 1U> &Y, double *fs)
{
  coder::array<creal_T, 1U> b_Y;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 1U> b_data;
  double b;
  double y;
  int k;
  int loop_ub;
  int pmax;
  int pow2p;
  *fs = 1.0 / (b_time[1] - b_time[0]);
  // 样点个数
  b = *fs / (static_cast<double>(b_time.size(0)) - 1.0);
  // 分辨率
  if (b_time.size(0) - 1 < 0) {
    f.set_size(f.size(0), 0);
  } else {
    f.set_size(1, b_time.size(0));
    loop_ub = b_time.size(0) - 1;
    for (pow2p = 0; pow2p <= loop_ub; pow2p++) {
      f[pow2p] = pow2p;
    }
  }
  f.set_size(1, f.size(1));
  loop_ub = f.size(1) - 1;
  for (pow2p = 0; pow2p <= loop_ub; pow2p++) {
    f[pow2p] = f[pow2p] * b;
  }
  // 其中每点的频率，第一个点对应的频率为0
  if (b_time.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = b_time.size(0);
  }
  if (loop_ub == 0) {
    b_Y.set_size(0);
  } else {
    int n;
    int pmin;
    boolean_T useRadix2;
    useRadix2 = ((loop_ub & (loop_ub - 1)) == 0);
    pmin = 1;
    if (useRadix2) {
      pmax = loop_ub;
    } else {
      n = (loop_ub + loop_ub) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      pmin = 1 << pmax;
      pmax = pmin;
    }
    b = 6.2831853071795862 / static_cast<double>(pmax);
    n = pmax / 2 / 2;
    costab1q.set_size(1, n + 1);
    costab1q[0] = 1.0;
    pmax = n / 2 - 1;
    for (k = 0; k <= pmax; k++) {
      costab1q[k + 1] = std::cos(b * (static_cast<double>(k) + 1.0));
    }
    pow2p = pmax + 2;
    pmax = n - 1;
    for (k = pow2p; k <= pmax; k++) {
      costab1q[k] = std::sin(b * static_cast<double>(n - k));
    }
    costab1q[n] = 0.0;
    if (!useRadix2) {
      n = costab1q.size(1) - 1;
      pmax = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, pmax + 1);
      sintab.set_size(1, pmax + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, pmax + 1);
      for (k = 0; k < n; k++) {
        sintabinv[k + 1] = costab1q[(n - k) - 1];
      }
      pow2p = costab1q.size(1);
      for (k = pow2p; k <= pmax; k++) {
        sintabinv[k] = costab1q[k - n];
      }
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      pow2p = costab1q.size(1);
      for (k = pow2p; k <= pmax; k++) {
        costab[k] = -costab1q[pmax - k];
        sintab[k] = -costab1q[k - n];
      }
    } else {
      n = costab1q.size(1) - 1;
      pmax = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, pmax + 1);
      sintab.set_size(1, pmax + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      pow2p = costab1q.size(1);
      for (k = pow2p; k <= pmax; k++) {
        costab[k] = -costab1q[pmax - k];
        sintab[k] = -costab1q[k - n];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      b_Y.set_size(loop_ub);
      if (loop_ub != 1) {
        b_data.set_size(loop_ub);
        for (pow2p = 0; pow2p < loop_ub; pow2p++) {
          b_data[pow2p] = data[pow2p];
        }
        coder::internal::fft::FFTImplementationCallback::doHalfLengthRadix2(
            b_data, b_Y, loop_ub, costab, sintab);
      } else {
        b_Y[0].re = data[0];
        b_Y[0].im = 0.0;
      }
    } else {
      b_data.set_size(loop_ub);
      for (pow2p = 0; pow2p < loop_ub; pow2p++) {
        b_data[pow2p] = data[pow2p];
      }
      coder::internal::fft::FFTImplementationCallback::dobluesteinfft(
          b_data, pmin, loop_ub, costab, sintab, sintabinv, b_Y);
    }
  }
  y = static_cast<double>(b_time.size(0)) / 2.0;
  loop_ub = b_Y.size(0);
  for (pow2p = 0; pow2p < loop_ub; pow2p++) {
    double ai;
    double re;
    b = b_Y[pow2p].re;
    ai = b_Y[pow2p].im;
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
    b_Y[pow2p].re = re;
    b_Y[pow2p].im = b;
  }
  // 真实的幅值
  pmax = b_Y.size(0);
  Y.set_size(b_Y.size(0));
  for (k = 0; k < pmax; k++) {
    Y[k] = rt_hypotd_snf(b_Y[k].re, b_Y[k].im);
  }
  loop_ub = Y.size(0);
  for (pow2p = 0; pow2p < loop_ub; pow2p++) {
    Y[pow2p] = Y[pow2p] / 2.0E-5;
  }
  pmax = Y.size(0);
  for (k = 0; k < pmax; k++) {
    Y[k] = std::log10(Y[k]);
  }
  loop_ub = Y.size(0);
  for (pow2p = 0; pow2p < loop_ub; pow2p++) {
    Y[pow2p] = 20.0 * Y[pow2p];
  }
  b = static_cast<double>(b_time.size(0)) / 2.0;
  if (b < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(b);
  }
  f.set_size(f.size(0), loop_ub);
  b = static_cast<double>(b_time.size(0)) / 2.0;
  if (b < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(b);
  }
  Y.set_size(loop_ub);
}

//
// File trailer for pingpu.cpp
//
// [EOF]
//
