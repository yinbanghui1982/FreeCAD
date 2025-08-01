//
// File: time_anslysis.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:59:39
//

// Include Files
#include "time_anslysis.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "time_anslysis_data.h"
#include "time_anslysis_initialize.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// 有效值
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
void time_anslysis(const coder::array<double, 2U> &sig, double *rms2, double
                   *mean2, double *max_abs, double *mean_abs, double *rms_abs,
                   double *var2, double *std2, double *spl, double *ppv)
{
  coder::array<double, 2U> x;
  coder::array<double, 1U> absdiff;
  double t;
  double xbar;
  int i;
  int k;
  int n;
  int vlen;
  if (!isInitialized_time_anslysis) {
    time_anslysis_initialize();
  }

  x.set_size(1, sig.size(1));
  vlen = sig.size(0) * sig.size(1);
  for (i = 0; i < vlen; i++) {
    t = sig[i];
    x[i] = t * t;
  }

  vlen = x.size(1);
  if (x.size(1) == 0) {
    xbar = 0.0;
  } else {
    xbar = x[0];
    for (k = 2; k <= vlen; k++) {
      xbar += x[k - 1];
    }
  }

  *rms2 = sqrt(xbar / static_cast<double>(x.size(1)));

  // 平均值
  vlen = sig.size(1);
  if (sig.size(1) == 0) {
    xbar = 0.0;
  } else {
    xbar = sig[0];
    for (k = 2; k <= vlen; k++) {
      xbar += sig[k - 1];
    }
  }

  *mean2 = xbar / static_cast<double>(sig.size(1));

  // 最大幅值
  vlen = sig.size(1);
  x.set_size(1, sig.size(1));
  for (k = 0; k < vlen; k++) {
    x[k] = fabs(sig[k]);
  }

  *max_abs = coder::internal::maximum(x);

  // 平均幅值
  vlen = sig.size(1);
  x.set_size(1, sig.size(1));
  for (k = 0; k < vlen; k++) {
    x[k] = fabs(sig[k]);
  }

  vlen = x.size(1);
  if (x.size(1) == 0) {
    xbar = 0.0;
  } else {
    xbar = x[0];
    for (k = 2; k <= vlen; k++) {
      xbar += x[k - 1];
    }
  }

  *mean_abs = xbar / static_cast<double>(x.size(1));

  // 方根幅值
  vlen = sig.size(1);
  x.set_size(1, sig.size(1));
  for (k = 0; k < vlen; k++) {
    x[k] = fabs(sig[k]);
  }

  vlen = x.size(1);
  if (x.size(1) == 0) {
    xbar = 0.0;
  } else {
    xbar = x[0];
    for (k = 2; k <= vlen; k++) {
      xbar += x[k - 1];
    }
  }

  *rms_abs = sqrt(xbar / static_cast<double>(x.size(1)));

  // 方差
  n = sig.size(1);
  if (sig.size(1) == 0) {
    *var2 = rtNaN;
  } else if (sig.size(1) == 1) {
    if ((!rtIsInf(sig[0])) && (!rtIsNaN(sig[0]))) {
      *var2 = 0.0;
    } else {
      *var2 = rtNaN;
    }
  } else {
    xbar = sig[0];
    for (k = 2; k <= n; k++) {
      xbar += sig[k - 1];
    }

    xbar /= static_cast<double>(sig.size(1));
    *var2 = 0.0;
    for (k = 0; k < n; k++) {
      t = sig[k] - xbar;
      *var2 += t * t;
    }

    *var2 /= static_cast<double>(sig.size(1)) - 1.0;
  }

  // 均方差
  n = sig.size(1);
  if (sig.size(1) == 0) {
    *std2 = rtNaN;
  } else if (sig.size(1) == 1) {
    if ((!rtIsInf(sig[0])) && (!rtIsNaN(sig[0]))) {
      *std2 = 0.0;
    } else {
      *std2 = rtNaN;
    }
  } else {
    xbar = sig[0];
    for (k = 2; k <= n; k++) {
      xbar += sig[k - 1];
    }

    xbar /= static_cast<double>(sig.size(1));
    absdiff.set_size(sig.size(1));
    for (k = 0; k < n; k++) {
      absdiff[k] = fabs(sig[k] - xbar);
    }

    *std2 = 0.0;
    xbar = 3.3121686421112381E-170;
    vlen = sig.size(1);
    for (k = 0; k < vlen; k++) {
      if (absdiff[k] > xbar) {
        t = xbar / absdiff[k];
        *std2 = *std2 * t * t + 1.0;
        xbar = absdiff[k];
      } else {
        t = absdiff[k] / xbar;
        *std2 += t * t;
      }
    }

    *std2 = xbar * sqrt(*std2);
    *std2 /= sqrt(static_cast<double>(sig.size(1)) - 1.0);
  }

  // 计算有效声压
  //  根据定义计算有效声压，pa = sqrt((x(1)^2+x(2)^2+...+x(M)^2)/M)
  //  单位为Pa
  xbar = 0.0;
  i = sig.size(1);
  for (vlen = 0; vlen < i; vlen++) {
    t = sig[vlen];
    xbar += t * t;

    // 下面公式2-5
  }

  // 计算声压级
  //  声压级值spl=20*log10(pa/p0),单位为dB
  //  基准声压p0，单位为Pa
  *spl = 20.0 * log10(sqrt(xbar / static_cast<double>(sig.size(1))) /
                      1.9999999999999998E-5);

  // 下面公式2-6
  n = sig.size(1);
  if (sig.size(1) <= 2) {
    if (sig.size(1) == 1) {
      xbar = sig[0];
    } else if ((sig[0] > sig[1]) || (rtIsNaN(sig[0]) && (!rtIsNaN(sig[1])))) {
      xbar = sig[1];
    } else {
      xbar = sig[0];
    }
  } else {
    if (!rtIsNaN(sig[0])) {
      vlen = 1;
    } else {
      boolean_T exitg1;
      vlen = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= sig.size(1))) {
        if (!rtIsNaN(sig[k - 1])) {
          vlen = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (vlen == 0) {
      xbar = sig[0];
    } else {
      xbar = sig[vlen - 1];
      i = vlen + 1;
      for (k = i; k <= n; k++) {
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
