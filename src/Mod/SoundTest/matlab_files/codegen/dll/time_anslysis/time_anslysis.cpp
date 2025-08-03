//
// File: time_anslysis.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

// Include Files
#include "time_anslysis.h"
#include "combineVectorElements.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// 有效值
//
// Arguments    : const coder::array<double, 2U> &sig
//                double *rms2
//                double *mean2
//                double *max_abs
//                double *mean_abs
//                double *rms_abs
//                double *var2
//                double *std2
//                double *spl
//                double *ppv
// Return Type  : void
//
void time_anslysis(const coder::array<double, 2U> &sig, double *rms2,
                   double *mean2, double *max_abs, double *mean_abs,
                   double *rms_abs, double *var2, double *std2, double *spl,
                   double *ppv)
{
  coder::array<double, 2U> b_sig;
  coder::array<double, 1U> absdiff;
  coder::array<double, 1U> c_sig;
  double t;
  double xbar;
  int i;
  int k;
  int last;
  int nx;
  b_sig.set_size(1, sig.size(1));
  nx = sig.size(1);
  for (i = 0; i < nx; i++) {
    t = sig[i];
    b_sig[i] = t * t;
  }
  *rms2 = std::sqrt(coder::mean(b_sig));
  // 平均值
  *mean2 = coder::mean(sig);
  // 最大幅值
  nx = sig.size(1);
  b_sig.set_size(1, sig.size(1));
  for (k = 0; k < nx; k++) {
    b_sig[k] = std::abs(sig[k]);
  }
  *max_abs = coder::internal::maximum(b_sig);
  // 平均幅值
  nx = sig.size(1);
  b_sig.set_size(1, sig.size(1));
  for (k = 0; k < nx; k++) {
    b_sig[k] = std::abs(sig[k]);
  }
  *mean_abs = coder::mean(b_sig);
  // 方根幅值
  nx = sig.size(1);
  b_sig.set_size(1, sig.size(1));
  for (k = 0; k < nx; k++) {
    b_sig[k] = std::abs(sig[k]);
  }
  *rms_abs = std::sqrt(coder::mean(b_sig));
  // 方差
  last = sig.size(1);
  if (sig.size(1) == 0) {
    *var2 = rtNaN;
  } else if (sig.size(1) == 1) {
    if ((!std::isinf(sig[0])) && (!std::isnan(sig[0]))) {
      *var2 = 0.0;
    } else {
      *var2 = rtNaN;
    }
  } else {
    nx = sig.size(1);
    c_sig = sig.reshape(nx);
    xbar = coder::combineVectorElements(c_sig, sig.size(1)) /
           static_cast<double>(sig.size(1));
    *var2 = 0.0;
    for (k = 0; k < last; k++) {
      t = sig[k] - xbar;
      *var2 += t * t;
    }
    *var2 /= static_cast<double>(sig.size(1)) - 1.0;
  }
  // 均方差
  last = sig.size(1);
  if (sig.size(1) == 0) {
    *std2 = rtNaN;
  } else if (sig.size(1) == 1) {
    if ((!std::isinf(sig[0])) && (!std::isnan(sig[0]))) {
      *std2 = 0.0;
    } else {
      *std2 = rtNaN;
    }
  } else {
    nx = sig.size(1);
    c_sig = sig.reshape(nx);
    xbar = coder::combineVectorElements(c_sig, sig.size(1)) /
           static_cast<double>(sig.size(1));
    absdiff.set_size(sig.size(1));
    for (k = 0; k < last; k++) {
      absdiff[k] = std::abs(sig[k] - xbar);
    }
    *std2 = 0.0;
    xbar = 3.3121686421112381E-170;
    nx = sig.size(1);
    for (k = 0; k < nx; k++) {
      if (absdiff[k] > xbar) {
        t = xbar / absdiff[k];
        *std2 = *std2 * t * t + 1.0;
        xbar = absdiff[k];
      } else {
        t = absdiff[k] / xbar;
        *std2 += t * t;
      }
    }
    *std2 = xbar * std::sqrt(*std2);
    *std2 /= std::sqrt(static_cast<double>(sig.size(1)) - 1.0);
  }
  // 计算有效声压
  //  根据定义计算有效声压，pa = sqrt((x(1)^2+x(2)^2+...+x(M)^2)/M)
  //  单位为Pa
  xbar = 0.0;
  i = sig.size(1);
  for (nx = 0; nx < i; nx++) {
    t = sig[nx];
    xbar += t * t;
    // 下面公式2-5
  }
  // 计算声压级
  //  声压级值spl=20*log10(pa/p0),单位为dB
  //  基准声压p0，单位为Pa
  *spl = 20.0 * std::log10(std::sqrt(xbar / static_cast<double>(sig.size(1))) /
                           1.9999999999999998E-5);
  // 下面公式2-6
  last = sig.size(1);
  if (sig.size(1) <= 2) {
    if (sig.size(1) == 1) {
      xbar = sig[0];
    } else if ((sig[0] > sig[sig.size(1) - 1]) ||
               (std::isnan(sig[0]) && (!std::isnan(sig[sig.size(1) - 1])))) {
      xbar = sig[sig.size(1) - 1];
    } else {
      xbar = sig[0];
    }
  } else {
    if (!std::isnan(sig[0])) {
      nx = 1;
    } else {
      boolean_T exitg1;
      nx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(sig[k - 1])) {
          nx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (nx == 0) {
      xbar = sig[0];
    } else {
      xbar = sig[nx - 1];
      i = nx + 1;
      for (k = i; k <= last; k++) {
        t = sig[k - 1];
        if (xbar > t) {
          xbar = t;
        }
      }
    }
  }
  *ppv = coder::internal::maximum(sig) - xbar;
}

//
// File trailer for time_anslysis.cpp
//
// [EOF]
//
