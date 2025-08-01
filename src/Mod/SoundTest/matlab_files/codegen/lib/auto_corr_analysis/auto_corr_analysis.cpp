//
// File: auto_corr_analysis.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:06:11
//

// Include Files
#include "auto_corr_analysis.h"
#include "auto_corr_analysis_data.h"
#include "auto_corr_analysis_initialize.h"
#include "fft.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Declarations
namespace corr
{
  static double rt_hypotd_snf(double u0, double u1);
  static double rt_powd_snf(double u0, double u1);
}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace corr
{
  static double rt_hypotd_snf(double u0, double u1)
  {
    double a;
    double y;
    a = fabs(u0);
    y = fabs(u1);
    if (a < y) {
      a /= y;
      y *= sqrt(a * a + 1.0);
    } else if (a > y) {
      y /= a;
      y = a * sqrt(y * y + 1.0);
    } else {
      if (!rtIsNaN(y)) {
        y = a * 1.4142135623730951;
      }
    }

    return y;
  }

  //
  // Arguments    : double u0
  //                double u1
  // Return Type  : double
  //
  static double rt_powd_snf(double u0, double u1)
  {
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
      y = rtNaN;
    } else {
      double d;
      double d1;
      d = fabs(u0);
      d1 = fabs(u1);
      if (rtIsInf(u1)) {
        if (d == 1.0) {
          y = 1.0;
        } else if (d > 1.0) {
          if (u1 > 0.0) {
            y = rtInf;
          } else {
            y = 0.0;
          }
        } else if (u1 > 0.0) {
          y = 0.0;
        } else {
          y = rtInf;
        }
      } else if (d1 == 0.0) {
        y = 1.0;
      } else if (d1 == 1.0) {
        if (u1 > 0.0) {
          y = u0;
        } else {
          y = 1.0 / u0;
        }
      } else if (u1 == 2.0) {
        y = u0 * u0;
      } else if ((u1 == 0.5) && (u0 >= 0.0)) {
        y = sqrt(u0);
      } else if ((u0 < 0.0) && (u1 > floor(u1))) {
        y = rtNaN;
      } else {
        y = pow(u0, u1);
      }
    }

    return y;
  }

  //
  // Arguments    : const ::coder::array<double, 2U> &x
  //                double dt
  //                ::coder::array<double, 2U> &c
  //                ::coder::array<double, 2U> &lags2
  // Return Type  : void
  //
  void auto_corr_analysis(const ::coder::array<double, 2U> &x, double dt, ::
    coder::array<double, 2U> &c, ::coder::array<double, 2U> &lags2)
  {
    ::coder::array<creal_T, 1U> X;
    ::coder::array<double, 2U> b_y;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> Cr;
    ::coder::array<double, 1U> b_c1;
    ::coder::array<double, 1U> c1;
    double c0;
    double m2;
    int ceilLog2;
    int i;
    int k;
    int nm1d2;
    if (!isInitialized_auto_corr_analysis) {
      auto_corr_analysis_initialize();
    }

    m2 = frexp(fabs(2.0 * static_cast<double>(x.size(1)) - 1.0), &ceilLog2);
    if (m2 == 0.5) {
      ceilLog2--;
    }

    m2 = rt_powd_snf(2.0, static_cast<double>(ceilLog2));
    c0 = 2.0 * static_cast<double>(x.size(1)) - 1.0;
    if (c0 + static_cast<double>(x.size(1) - 1) * ((c0 - static_cast<double>
          (x.size(1) - 1)) - 1.0) < m2 * (15.0 * static_cast<double>(ceilLog2) +
         6.0)) {
      nm1d2 = x.size(1) - 1;
      ceilLog2 = x.size(1) - 1;
      if (nm1d2 < ceilLog2) {
        ceilLog2 = nm1d2;
      }

      m2 = 2.0 * static_cast<double>(ceilLog2) + 1.0;
      b_c1.set_size((static_cast<int>(m2)));
      nm1d2 = static_cast<int>(m2);
      for (i = 0; i < nm1d2; i++) {
        b_c1[i] = 0.0;
      }

      for (k = 0; k <= ceilLog2; k++) {
        m2 = 0.0;
        i = x.size(1) - k;
        for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
          m2 += x[nm1d2] * x[k + nm1d2];
        }

        b_c1[ceilLog2 - k] = m2;
        b_c1[ceilLog2 + k] = m2;
      }
    } else {
      ceilLog2 = x.size(1);
      c1 = x.reshape(ceilLog2);
      fft(c1, m2, X);
      ceilLog2 = X.size(0);
      c1.set_size(X.size(0));
      for (k = 0; k < ceilLog2; k++) {
        c1[k] = rt_hypotd_snf(X[k].re, X[k].im);
      }

      Cr.set_size(c1.size(0));
      ceilLog2 = c1.size(0);
      for (k = 0; k < ceilLog2; k++) {
        Cr[k] = rt_powd_snf(c1[k], 2.0);
      }

      ifft(Cr, X);
      c1.set_size(X.size(0));
      nm1d2 = X.size(0);
      for (i = 0; i < nm1d2; i++) {
        c1[i] = X[i].re;
      }

      if (1 > x.size(1)) {
        nm1d2 = -1;
      } else {
        nm1d2 = x.size(1) - 1;
      }

      if (x.size(1) - 1 < 1) {
        y.set_size(1, 0);
      } else {
        y.set_size(1, (x.size(1) - 1));
        ceilLog2 = x.size(1) - 2;
        for (i = 0; i <= ceilLog2; i++) {
          y[i] = static_cast<double>(i) + 1.0;
        }
      }

      m2 -= static_cast<double>(x.size(1) - 1);
      b_c1.set_size(((y.size(1) + nm1d2) + 1));
      ceilLog2 = y.size(1);
      for (i = 0; i < ceilLog2; i++) {
        b_c1[i] = c1[static_cast<int>(m2 + y[i]) - 1];
      }

      for (i = 0; i <= nm1d2; i++) {
        b_c1[i + y.size(1)] = c1[i];
      }
    }

    m2 = (static_cast<double>(b_c1.size(0)) - 1.0) / 2.0;
    if (m2 < -m2) {
      y.set_size(1, 0);
    } else if (floor(-m2) == -m2) {
      nm1d2 = static_cast<int>(floor(m2 - (-m2)));
      y.set_size(1, (nm1d2 + 1));
      for (i = 0; i <= nm1d2; i++) {
        y[i] = -m2 + static_cast<double>(i);
      }
    } else {
      double apnd;
      double cdiff;
      double u0;
      double u1;
      c0 = floor((m2 - (-m2)) + 0.5);
      apnd = -m2 + c0;
      cdiff = apnd - m2;
      u0 = fabs(-m2);
      u1 = fabs(m2);
      if (u0 > u1) {
        u1 = u0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        c0++;
        apnd = m2;
      } else if (cdiff > 0.0) {
        apnd = -m2 + (c0 - 1.0);
      } else {
        c0++;
      }

      if (c0 >= 0.0) {
        ceilLog2 = static_cast<int>(c0);
      } else {
        ceilLog2 = 0;
      }

      y.set_size(1, ceilLog2);
      if (ceilLog2 > 0) {
        y[0] = -m2;
        if (ceilLog2 > 1) {
          y[ceilLog2 - 1] = apnd;
          nm1d2 = (ceilLog2 - 1) / 2;
          for (k = 0; k <= nm1d2 - 2; k++) {
            y[k + 1] = -m2 + (static_cast<double>(k) + 1.0);
            y[(ceilLog2 - k) - 2] = apnd - (static_cast<double>(k) + 1.0);
          }

          if (nm1d2 << 1 == ceilLog2 - 1) {
            y[nm1d2] = (-m2 + apnd) / 2.0;
          } else {
            y[nm1d2] = -m2 + static_cast<double>(nm1d2);
            y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
          }
        }
      }
    }

    ceilLog2 = y.size(1);
    b_y.set_size(1, y.size(1));
    for (k = 0; k < ceilLog2; k++) {
      b_y[k] = fabs(y[k]);
    }

    Cr.set_size(b_y.size(1));
    nm1d2 = b_y.size(1);
    for (i = 0; i < nm1d2; i++) {
      Cr[i] = static_cast<double>(x.size(1)) - b_y[i];
    }

    ceilLog2 = Cr.size(0);
    for (nm1d2 = 0; nm1d2 < ceilLog2; nm1d2++) {
      if (Cr[nm1d2] <= 0.0) {
        Cr[nm1d2] = 1.0;
      }
    }

    c1.set_size(b_c1.size(0));
    nm1d2 = b_c1.size(0);
    for (i = 0; i < nm1d2; i++) {
      c1[i] = b_c1[i];
    }

    nm1d2 = Cr.size(0);
    ceilLog2 = b_c1.size(0);
    if (nm1d2 < ceilLog2) {
      ceilLog2 = nm1d2;
    }

    if (Cr.size(0) == 1) {
      ceilLog2 = b_c1.size(0);
    } else if (b_c1.size(0) == 1) {
      ceilLog2 = Cr.size(0);
    } else {
      if (b_c1.size(0) == Cr.size(0)) {
        ceilLog2 = b_c1.size(0);
      }
    }

    b_c1.set_size(ceilLog2);
    if (ceilLog2 != 0) {
      int bcoef;
      nm1d2 = (c1.size(0) != 1);
      bcoef = (Cr.size(0) != 1);
      i = ceilLog2 - 1;
      for (k = 0; k <= i; k++) {
        b_c1[k] = c1[nm1d2 * k] / Cr[bcoef * k];
      }
    }

    c1.set_size((static_cast<int>(2.0 * (static_cast<double>(x.size(1)) - 1.0) +
      1.0)));
    nm1d2 = static_cast<int>(2.0 * (static_cast<double>(x.size(1)) - 1.0) + 1.0);
    for (i = 0; i < nm1d2; i++) {
      c1[i] = 0.0;
    }

    nm1d2 = b_c1.size(0);
    for (i = 0; i < nm1d2; i++) {
      c1[i] = b_c1[i];
    }

    if (x.size(1) - 1 < 1 - x.size(1)) {
      lags2.set_size(1, 0);
    } else {
      lags2.set_size(1, ((x.size(1) + x.size(1)) - 1));
      nm1d2 = (x.size(1) + x.size(1)) - 1;
      for (i = 0; i < nm1d2; i++) {
        lags2[i] = (i - x.size(1)) + 1;
      }
    }

    c.set_size(1, c1.size(0));
    nm1d2 = c1.size(0);
    for (i = 0; i < nm1d2; i++) {
      c[i] = c1[i];
    }

    i = lags2.size(0) * lags2.size(1);
    lags2.set_size(1, lags2.size(1));
    nm1d2 = i - 1;
    for (i = 0; i <= nm1d2; i++) {
      lags2[i] = lags2[i] * dt;
    }
  }
}

//
// File trailer for auto_corr_analysis.cpp
//
// [EOF]
//
