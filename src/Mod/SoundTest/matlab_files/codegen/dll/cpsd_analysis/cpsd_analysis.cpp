//
// File: cpsd_analysis.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

// Include Files
#include "cpsd_analysis.h"
#include "bsxfun.h"
#include "computeDFT.h"
#include "computepsd.h"
#include "cpsd_analysis_data.h"
#include "cpsd_analysis_initialize.h"
#include "cpsd_analysis_rtwutil.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "welch.h"
#include "coder_array.h"
#include "rt_defines.h"
#include <cmath>
#include <math.h>
#include <string.h>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

static double rt_hypotd_snf(double u0, double u1);

static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = std::atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
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
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
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
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

//
// Arguments    : const coder::array<double, 2U> &x
//                const coder::array<double, 2U> &y
//                double Fs
//                coder::array<double, 2U> &Pxy2
//                coder::array<double, 2U> &arg2
//                coder::array<double, 1U> &f
// Return Type  : void
//
void cpsd_analysis(const coder::array<double, 2U> &x,
                   const coder::array<double, 2U> &y, double Fs,
                   coder::array<double, 2U> &Pxy2,
                   coder::array<double, 2U> &arg2, coder::array<double, 1U> &f)
{
  static const char cv[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  coder::array<creal_T, 2U> Sxx1;
  coder::array<creal_T, 2U> b_Sxx1;
  coder::array<creal_T, 1U> Xx;
  coder::array<creal_T, 1U> Yy;
  coder::array<creal_T, 1U> c_x;
  coder::array<double, 2U> b_f1;
  coder::array<double, 2U> f1;
  coder::array<double, 2U> xEnd;
  coder::array<double, 2U> xStart;
  coder::array<double, 1U> b_x;
  coder::array<double, 1U> b_y;
  coder::array<double, 1U> c_f1;
  coder::array<double, 1U> c_y;
  coder::array<double, 1U> d_f1;
  coder::array<double, 1U> r;
  double Xx_im_tmp;
  double Xx_re;
  double b_f;
  double k1;
  double options_nfft;
  int units_size[2];
  int L;
  int b_loop_ub;
  int eint;
  int i;
  int i1;
  int i2;
  int loop_ub;
  int noverlap;
  int nx;
  char units_data[10];
  if (!isInitialized_cpsd_analysis) {
    cpsd_analysis_initialize();
  }
  f1.set_size(1, x.size(1));
  loop_ub = x.size(1);
  for (i = 0; i < loop_ub; i++) {
    f1[i] = x[i];
  }
  b_f1.set_size(1, y.size(1));
  loop_ub = y.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_f1[i] = y[i];
  }
  L = static_cast<int>(std::trunc(static_cast<double>(f1.size(1)) / 4.5));
  noverlap = static_cast<int>(std::trunc(0.5 * static_cast<double>(L)));
  if (std::fmod(static_cast<double>(L), 2.0) == 0.0) {
    b_f = static_cast<double>(L) / 2.0 - 1.0;
    b_y.set_size(static_cast<int>(b_f) + 1);
    loop_ub = static_cast<int>(b_f);
    for (i = 0; i <= loop_ub; i++) {
      b_y[i] = 6.2831853071795862 *
               (static_cast<double>(i) / (static_cast<double>(L) - 1.0));
    }
    nx = b_y.size(0);
    for (loop_ub = 0; loop_ub < nx; loop_ub++) {
      b_y[loop_ub] = std::cos(b_y[loop_ub]);
    }
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_y[i] = 0.54 - 0.46 * b_y[i];
    }
    nx = b_y.size(0) - 1;
    c_y.set_size(b_y.size(0) + b_y.size(0));
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      c_y[i] = b_y[i];
    }
    for (i = 0; i <= nx; i++) {
      c_y[i + b_y.size(0)] = b_y[nx - i];
    }
    b_y.set_size(c_y.size(0));
    loop_ub = c_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_y[i] = c_y[i];
    }
  } else {
    b_f = (static_cast<double>(L) + 1.0) / 2.0 - 1.0;
    b_y.set_size(static_cast<int>(b_f) + 1);
    loop_ub = static_cast<int>(b_f);
    for (i = 0; i <= loop_ub; i++) {
      b_y[i] = 6.2831853071795862 *
               (static_cast<double>(i) / (static_cast<double>(L) - 1.0));
    }
    nx = b_y.size(0);
    for (loop_ub = 0; loop_ub < nx; loop_ub++) {
      b_y[loop_ub] = std::cos(b_y[loop_ub]);
    }
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_y[i] = 0.54 - 0.46 * b_y[i];
    }
    if (b_y.size(0) - 1 < 1) {
      i = 0;
      i1 = 1;
      i2 = -1;
    } else {
      i = b_y.size(0) - 2;
      i1 = -1;
      i2 = 0;
    }
    loop_ub = div_s32(i2 - i, i1);
    c_y.set_size((b_y.size(0) + loop_ub) + 1);
    nx = b_y.size(0);
    for (i2 = 0; i2 < nx; i2++) {
      c_y[i2] = b_y[i2];
    }
    for (i2 = 0; i2 <= loop_ub; i2++) {
      c_y[i2 + b_y.size(0)] = b_y[i + i1 * i2];
    }
    b_y.set_size(c_y.size(0));
    loop_ub = c_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_y[i] = c_y[i];
    }
  }
  b_f = frexp(static_cast<double>(L), &eint);
  if (b_f == 0.5) {
    eint--;
  }
  options_nfft = std::fmax(256.0, rt_powd_snf(2.0, static_cast<double>(eint)));
  eint = L - noverlap;
  k1 = std::trunc(static_cast<double>(f1.size(1) - noverlap) /
                  static_cast<double>(eint));
  b_f = k1 * static_cast<double>(eint);
  if (std::isnan(b_f)) {
    xStart.set_size(1, 1);
    xStart[0] = rtNaN;
  } else if ((eint == 0) || ((b_f > 1.0) && (eint < 0)) ||
             ((b_f < 1.0) && (eint > 0))) {
    xStart.set_size(1, 0);
  } else {
    loop_ub = static_cast<int>((b_f - 1.0) / static_cast<double>(eint));
    xStart.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      xStart[i] = static_cast<double>(eint) * static_cast<double>(i) + 1.0;
    }
  }
  xEnd.set_size(1, xStart.size(1));
  loop_ub = xStart.size(1);
  for (i = 0; i < loop_ub; i++) {
    xEnd[i] = (xStart[i] + static_cast<double>(L)) - 1.0;
  }
  loop_ub = f1.size(1);
  b_x.set_size(f1.size(1));
  for (i = 0; i < loop_ub; i++) {
    b_x[i] = f1[i];
  }
  if (b_f1.size(1) != 0) {
    Sxx1.set_size(0, 0);
    i = static_cast<int>(k1);
    if (static_cast<int>(k1) - 1 >= 0) {
      b_loop_ub = b_y.size(0);
    }
    for (L = 0; L < i; L++) {
      double d_y;
      b_f = xStart[L];
      Xx_im_tmp = xEnd[L];
      if (b_f > Xx_im_tmp) {
        i1 = 0;
        i2 = 0;
        nx = 0;
        eint = 0;
      } else {
        i1 = static_cast<int>(b_f) - 1;
        i2 = static_cast<int>(Xx_im_tmp);
        nx = static_cast<int>(b_f) - 1;
        eint = static_cast<int>(Xx_im_tmp);
      }
      loop_ub = i2 - i1;
      c_f1.set_size(loop_ub);
      for (i2 = 0; i2 < loop_ub; i2++) {
        c_f1[i2] = b_x[i1 + i2];
      }
      loop_ub = eint - nx;
      d_f1.set_size(loop_ub);
      for (i1 = 0; i1 < loop_ub; i1++) {
        d_f1[i1] = b_f1[nx + i1];
      }
      b_f = Fs;
      if (std::isnan(Fs)) {
        b_f = 6.2831853071795862;
      }
      coder::bsxfun(c_f1, b_y, r);
      coder::computeDFT(r, options_nfft, b_f, Xx, c_y);
      d_y = 0.0;
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        d_y += b_y[i1] * b_y[i1];
      }
      coder::bsxfun(d_f1, b_y, r);
      coder::computeDFT(r, options_nfft, b_f, Yy, c_y);
      loop_ub = Yy.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        Yy[i1].im = -Yy[i1].im;
      }
      nx = Yy.size(0);
      eint = Xx.size(0);
      if (nx <= eint) {
        eint = nx;
      }
      if (Xx.size(0) == Yy.size(0)) {
        eint = Xx.size(0);
      }
      c_x.set_size(eint);
      nx = Yy.size(0);
      eint = Xx.size(0);
      if (nx <= eint) {
        eint = nx;
      }
      if (Xx.size(0) == Yy.size(0)) {
        eint = Xx.size(0);
      }
      i1 = eint - 1;
      for (loop_ub = 0; loop_ub <= i1; loop_ub++) {
        double d;
        b_f = Xx[loop_ub].re;
        Xx_im_tmp = Yy[loop_ub].im;
        Xx_re = Xx[loop_ub].im;
        d = Yy[loop_ub].re;
        c_x[loop_ub].re = b_f * d - Xx_re * Xx_im_tmp;
        c_x[loop_ub].im = b_f * Xx_im_tmp + Xx_re * d;
      }
      loop_ub = c_x.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_f = c_x[i1].re;
        Xx_re = c_x[i1].im;
        if (Xx_re == 0.0) {
          Xx_im_tmp = b_f / d_y;
          b_f = 0.0;
        } else if (b_f == 0.0) {
          Xx_im_tmp = 0.0;
          b_f = Xx_re / d_y;
        } else {
          Xx_im_tmp = b_f / d_y;
          b_f = Xx_re / d_y;
        }
        c_x[i1].re = Xx_im_tmp;
        c_x[i1].im = b_f;
      }
      if (L + 1U == 1U) {
        Sxx1.set_size(c_x.size(0), 1);
        loop_ub = c_x.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          Sxx1[i1] = c_x[i1];
        }
      } else if (Sxx1.size(0) == c_x.size(0)) {
        loop_ub = Sxx1.size(1);
        b_Sxx1.set_size(Sxx1.size(0), Sxx1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
          nx = Sxx1.size(0);
          for (i2 = 0; i2 < nx; i2++) {
            b_Sxx1[i2].re = Sxx1[i2].re + c_x[i2].re;
            b_Sxx1[i2].im = Sxx1[i2].im + c_x[i2].im;
          }
        }
        Sxx1.set_size(b_Sxx1.size(0), b_Sxx1.size(1));
        loop_ub = b_Sxx1.size(0) * b_Sxx1.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          Sxx1[i1] = b_Sxx1[i1];
        }
      } else {
        binary_expand_op(Sxx1, c_x);
      }
    }
  } else {
    Sxx1.set_size(0, 0);
    i = static_cast<int>(k1);
    for (L = 0; L < i; L++) {
      double d_y;
      b_f = xStart[L];
      Xx_im_tmp = xEnd[L];
      if (b_f > Xx_im_tmp) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = static_cast<int>(b_f) - 1;
        i2 = static_cast<int>(Xx_im_tmp);
      }
      b_f = Fs;
      if (std::isnan(Fs)) {
        b_f = 6.2831853071795862;
      }
      loop_ub = i2 - i1;
      c_y.set_size(loop_ub);
      for (i2 = 0; i2 < loop_ub; i2++) {
        c_y[i2] = b_x[i1 + i2];
      }
      coder::bsxfun(c_y, b_y, r);
      coder::computeDFT(r, options_nfft, b_f, Xx, c_y);
      d_y = 0.0;
      loop_ub = b_y.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        d_y += b_y[i1] * b_y[i1];
      }
      loop_ub = Xx.size(0);
      c_y.set_size(Xx.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_f = Xx[i1].re;
        Xx_im_tmp = Xx[i1].im;
        Xx_re = b_f * b_f - Xx_im_tmp * -Xx_im_tmp;
        if (b_f * -Xx_im_tmp + Xx_im_tmp * b_f == 0.0) {
          Xx_re /= d_y;
        } else if (Xx_re == 0.0) {
          Xx_re = 0.0;
        } else {
          Xx_re /= d_y;
        }
        c_y[i1] = Xx_re;
      }
      if (L + 1U == 1U) {
        Sxx1.set_size(c_y.size(0), 1);
        loop_ub = c_y.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          Sxx1[i1].re = c_y[i1];
          Sxx1[i1].im = 0.0;
        }
      } else if (Sxx1.size(0) == c_y.size(0)) {
        loop_ub = Sxx1.size(1);
        b_Sxx1.set_size(Sxx1.size(0), Sxx1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
          nx = Sxx1.size(0);
          for (i2 = 0; i2 < nx; i2++) {
            b_Sxx1[i2].re = Sxx1[i2].re + c_y[i2];
            b_Sxx1[i2].im = Sxx1[i2].im;
          }
        }
        Sxx1.set_size(b_Sxx1.size(0), b_Sxx1.size(1));
        loop_ub = b_Sxx1.size(0) * b_Sxx1.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          Sxx1[i1] = b_Sxx1[i1];
        }
      } else {
        binary_expand_op(Sxx1, c_y);
      }
    }
  }
  loop_ub = Sxx1.size(0) * Sxx1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_f = Sxx1[i].re;
    Xx_re = Sxx1[i].im;
    if (Xx_re == 0.0) {
      Xx_im_tmp = b_f / k1;
      b_f = 0.0;
    } else if (b_f == 0.0) {
      Xx_im_tmp = 0.0;
      b_f = Xx_re / k1;
    } else {
      Xx_im_tmp = b_f / k1;
      b_f = Xx_re / k1;
    }
    Sxx1[i].re = Xx_im_tmp;
    Sxx1[i].im = b_f;
  }
  coder::psdfreqvec(options_nfft, Fs, c_y);
  nx = c_y.size(0);
  f1 = c_y.reshape(nx, 1);
  coder::computepsd(Sxx1, f1, cv, options_nfft, Fs, b_Sxx1, f, units_data,
                    units_size);
  nx = b_Sxx1.size(0) * b_Sxx1.size(1);
  Pxy2.set_size(b_Sxx1.size(0), b_Sxx1.size(1));
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    Pxy2[loop_ub] = rt_hypotd_snf(b_Sxx1[loop_ub].re, b_Sxx1[loop_ub].im);
  }
  nx = Pxy2.size(0) * Pxy2.size(1);
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    Pxy2[loop_ub] = std::log10(Pxy2[loop_ub]);
  }
  loop_ub = Pxy2.size(0) * Pxy2.size(1);
  for (i = 0; i < loop_ub; i++) {
    Pxy2[i] = (10.0 * Pxy2[i] + 300.0) - 300.0;
  }
  nx = b_Sxx1.size(0) * b_Sxx1.size(1);
  arg2.set_size(b_Sxx1.size(0), b_Sxx1.size(1));
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    arg2[loop_ub] = rt_atan2d_snf(b_Sxx1[loop_ub].im, b_Sxx1[loop_ub].re);
  }
}

//
// File trailer for cpsd_analysis.cpp
//
// [EOF]
//
