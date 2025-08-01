//
// File: cpsd_analysis.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "cpsd_analysis.h"
#include "computeDFT.h"
#include "computeperiodogram.h"
#include "computepsd.h"
#include "cpsd_analysis_data.h"
#include "cpsd_analysis_initialize.h"
#include "cpsd_analysis_internal_types.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "welchparse.h"
#include "coder_array.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Declarations
namespace cpsd
{
  static double rt_atan2d_snf(double u0, double u1);
  static double rt_hypotd_snf(double u0, double u1);
}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace cpsd
{
  static double rt_atan2d_snf(double u0, double u1)
  {
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
      y = rtNaN;
    } else if (rtIsInf(u0) && rtIsInf(u1)) {
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

      y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
    } else if (u1 == 0.0) {
      if (u0 > 0.0) {
        y = RT_PI / 2.0;
      } else if (u0 < 0.0) {
        y = -(RT_PI / 2.0);
      } else {
        y = 0.0;
      }
    } else {
      y = atan2(u0, u1);
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
  // Arguments    : const ::coder::array<double, 2U> &x
  //                const ::coder::array<double, 2U> &y
  //                double Fs
  //                ::coder::array<double, 2U> &Pxy2
  //                ::coder::array<double, 2U> &arg2
  //                ::coder::array<double, 1U> &f
  // Return Type  : void
  //
  void cpsd_analysis(const ::coder::array<double, 2U> &x, const ::coder::array<
                     double, 2U> &y, double Fs, ::coder::array<double, 2U> &Pxy2,
                     ::coder::array<double, 2U> &arg2, ::coder::array<double, 1U>
                     &f)
  {
    ::coder::array<creal_T, 2U> Sxx1;
    ::coder::array<creal_T, 2U> Sxxk;
    ::coder::array<creal_T, 2U> varargout_f1;
    ::coder::array<creal_T, 1U> Xx;
    ::coder::array<double, 2U> xEnd;
    ::coder::array<double, 2U> xStart;
    ::coder::array<double, 1U> b_f1;
    ::coder::array<double, 1U> b_x;
    ::coder::array<double, 1U> b_y1;
    ::coder::array<double, 1U> f1;
    ::coder::array<double, 1U> win1;
    ::coder::array<double, 1U> x1;
    cell_wrap_1 rv[2];
    cell_wrap_15 rv1[2];
    struct_T options;
    double L;
    double LminusOverlap;
    double cdiff;
    double k1;
    double noverlap;
    double options_Fs;
    double options_nfft;
    double u1;
    double unusedU2;
    int units_size[2];
    int acoef;
    int csz_idx_0;
    int i;
    int nm1d2;
    char units_data[10];
    boolean_T unusedU1;
    if (!isInitialized_cpsd_analysis) {
      cpsd_analysis_initialize();
    }

    xStart.set_size(1, x.size(1));
    acoef = x.size(0) * x.size(1);
    for (i = 0; i < acoef; i++) {
      xStart[i] = x[i];
    }

    xEnd.set_size(1, y.size(1));
    acoef = y.size(0) * y.size(1);
    for (i = 0; i < acoef; i++) {
      xEnd[i] = y[i];
    }

    rv[0].f1 = xStart;
    rv[1].f1 = xEnd;
    signal::internal::spectral::welchparse(rv, Fs, x1, &cdiff, &unusedU1, b_y1,
      &unusedU2, win1, &noverlap, &k1, &L, &options);
    options_nfft = options.nfft;
    options_Fs = options.Fs;
    LminusOverlap = L - noverlap;
    unusedU2 = k1 * LminusOverlap;
    if (rtIsNaN(LminusOverlap) || rtIsNaN(unusedU2)) {
      xStart.set_size(1, 1);
      xStart[0] = rtNaN;
    } else if ((LminusOverlap == 0.0) || ((1.0 < unusedU2) && (LminusOverlap <
                 0.0)) || ((unusedU2 < 1.0) && (LminusOverlap > 0.0))) {
      xStart.set_size(1, 0);
    } else if (rtIsInf(unusedU2) && (rtIsInf(LminusOverlap) || (1.0 == unusedU2)))
    {
      xStart.set_size(1, 1);
      xStart[0] = rtNaN;
    } else if (rtIsInf(LminusOverlap)) {
      xStart.set_size(1, 1);
      xStart[0] = 1.0;
    } else if (floor(LminusOverlap) == LminusOverlap) {
      acoef = static_cast<int>(floor((unusedU2 - 1.0) / LminusOverlap));
      xStart.set_size(1, (acoef + 1));
      for (i = 0; i <= acoef; i++) {
        xStart[i] = LminusOverlap * static_cast<double>(i) + 1.0;
      }
    } else {
      double apnd;
      noverlap = floor((unusedU2 - 1.0) / LminusOverlap + 0.5);
      apnd = noverlap * LminusOverlap + 1.0;
      if (LminusOverlap > 0.0) {
        cdiff = apnd - unusedU2;
      } else {
        cdiff = unusedU2 - apnd;
      }

      u1 = fabs(unusedU2);
      if ((1.0 > u1) || rtIsNaN(u1)) {
        u1 = 1.0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        noverlap++;
        apnd = unusedU2;
      } else if (cdiff > 0.0) {
        apnd = (noverlap - 1.0) * LminusOverlap + 1.0;
      } else {
        noverlap++;
      }

      if (noverlap >= 0.0) {
        acoef = static_cast<int>(noverlap);
      } else {
        acoef = 0;
      }

      xStart.set_size(1, acoef);
      if (acoef > 0) {
        xStart[0] = 1.0;
        if (acoef > 1) {
          xStart[acoef - 1] = apnd;
          nm1d2 = (acoef - 1) / 2;
          for (csz_idx_0 = 0; csz_idx_0 <= nm1d2 - 2; csz_idx_0++) {
            cdiff = (static_cast<double>(csz_idx_0) + 1.0) * LminusOverlap;
            xStart[csz_idx_0 + 1] = cdiff + 1.0;
            xStart[(acoef - csz_idx_0) - 2] = apnd - cdiff;
          }

          if (nm1d2 << 1 == acoef - 1) {
            xStart[nm1d2] = (apnd + 1.0) / 2.0;
          } else {
            cdiff = static_cast<double>(nm1d2) * LminusOverlap;
            xStart[nm1d2] = cdiff + 1.0;
            xStart[nm1d2 + 1] = apnd - cdiff;
          }
        }
      }
    }

    xEnd.set_size(1, xStart.size(1));
    acoef = xStart.size(0) * xStart.size(1);
    for (i = 0; i < acoef; i++) {
      xEnd[i] = (xStart[i] + L) - 1.0;
    }

    acoef = x1.size(0);
    b_x.set_size(x1.size(0));
    for (i = 0; i < acoef; i++) {
      b_x[i] = x1[i];
    }

    if (b_y1.size(0) != 0) {
      Sxx1.set_size(0, 0);
      i = static_cast<int>(k1);
      for (int ii = 0; ii < i; ii++) {
        int i1;
        int i2;
        noverlap = xStart[ii];
        cdiff = xEnd[ii];
        if (noverlap > cdiff) {
          i1 = 0;
          i2 = 0;
          nm1d2 = 0;
          csz_idx_0 = 0;
        } else {
          i1 = static_cast<int>(noverlap) - 1;
          i2 = static_cast<int>(cdiff);
          nm1d2 = static_cast<int>(noverlap) - 1;
          csz_idx_0 = static_cast<int>(cdiff);
        }

        acoef = i2 - i1;
        f1.set_size(acoef);
        for (i2 = 0; i2 < acoef; i2++) {
          f1[i2] = b_x[i1 + i2];
        }

        acoef = csz_idx_0 - nm1d2;
        b_f1.set_size(acoef);
        for (i1 = 0; i1 < acoef; i1++) {
          b_f1[i1] = b_y1[nm1d2 + i1];
        }

        rv1[0].f1 = f1;
        rv1[1].f1 = b_f1;
        computeperiodogram(rv1, win1, options_nfft, options_Fs, Sxxk, x1);
        if (ii + 1U == 1U) {
          Sxx1.set_size(Sxxk.size(0), 1);
          acoef = Sxxk.size(0) * Sxxk.size(1);
          for (i1 = 0; i1 < acoef; i1++) {
            Sxx1[i1] = Sxxk[i1];
          }
        } else {
          acoef = Sxx1.size(0) * Sxx1.size(1);
          for (i1 = 0; i1 < acoef; i1++) {
            Sxx1[i1].re = Sxx1[i1].re + Sxxk[i1].re;
            Sxx1[i1].im = Sxx1[i1].im + Sxxk[i1].im;
          }
        }
      }
    } else {
      Sxx1.set_size(0, 0);
      i = static_cast<int>(k1);
      for (int ii = 0; ii < i; ii++) {
        int i1;
        int i2;
        noverlap = xStart[ii];
        cdiff = xEnd[ii];
        if (noverlap > cdiff) {
          i1 = 0;
          i2 = 0;
        } else {
          i1 = static_cast<int>(noverlap) - 1;
          i2 = static_cast<int>(cdiff);
        }

        cdiff = options_Fs;
        if (rtIsNaN(options_Fs)) {
          cdiff = 6.2831853071795862;
        }

        acoef = i2 - i1;
        x1.set_size(acoef);
        for (i2 = 0; i2 < acoef; i2++) {
          x1[i2] = b_x[i1 + i2];
        }

        acoef = win1.size(0);
        nm1d2 = x1.size(0);
        if (acoef < nm1d2) {
          nm1d2 = acoef;
        }

        if (win1.size(0) == 1) {
          csz_idx_0 = x1.size(0);
        } else if (x1.size(0) == 1) {
          csz_idx_0 = win1.size(0);
        } else if (x1.size(0) == win1.size(0)) {
          csz_idx_0 = x1.size(0);
        } else {
          csz_idx_0 = nm1d2;
        }

        acoef = win1.size(0);
        nm1d2 = x1.size(0);
        if (acoef < nm1d2) {
          nm1d2 = acoef;
        }

        if (win1.size(0) == 1) {
          nm1d2 = x1.size(0);
        } else if (x1.size(0) == 1) {
          nm1d2 = win1.size(0);
        } else {
          if (x1.size(0) == win1.size(0)) {
            nm1d2 = x1.size(0);
          }
        }

        b_y1.set_size(nm1d2);
        if (csz_idx_0 != 0) {
          acoef = (x1.size(0) != 1);
          nm1d2 = (win1.size(0) != 1);
          i1 = csz_idx_0 - 1;
          for (csz_idx_0 = 0; csz_idx_0 <= i1; csz_idx_0++) {
            b_y1[csz_idx_0] = x1[acoef * csz_idx_0] * win1[nm1d2 * csz_idx_0];
          }
        }

        computeDFT(b_y1, options_nfft, cdiff, Xx, x1);
        unusedU2 = 0.0;
        acoef = win1.size(0);
        for (i1 = 0; i1 < acoef; i1++) {
          unusedU2 += win1[i1] * win1[i1];
        }

        acoef = Xx.size(0);
        b_y1.set_size(Xx.size(0));
        for (i1 = 0; i1 < acoef; i1++) {
          noverlap = Xx[i1].re;
          cdiff = -Xx[i1].im;
          u1 = Xx[i1].re * noverlap - Xx[i1].im * cdiff;
          cdiff = Xx[i1].re * cdiff + Xx[i1].im * noverlap;
          if (cdiff == 0.0) {
            noverlap = u1 / unusedU2;
          } else if (u1 == 0.0) {
            noverlap = 0.0;
          } else {
            noverlap = u1 / unusedU2;
          }

          b_y1[i1] = noverlap;
        }

        if (ii + 1U == 1U) {
          Sxx1.set_size(b_y1.size(0), 1);
          acoef = b_y1.size(0);
          for (i1 = 0; i1 < acoef; i1++) {
            Sxx1[i1].re = b_y1[i1];
            Sxx1[i1].im = 0.0;
          }
        } else {
          nm1d2 = Sxx1.size(0);
          Xx.set_size(Sxx1.size(0));
          acoef = Sxx1.size(0);
          for (i1 = 0; i1 < acoef; i1++) {
            Xx[i1].re = Sxx1[i1].re + b_y1[i1];
            Xx[i1].im = Sxx1[i1].im;
          }

          acoef = Sxx1.size(0);
          Sxx1.set_size(acoef, 1);
          for (i1 = 0; i1 < nm1d2; i1++) {
            Sxx1[i1] = Xx[i1];
          }
        }
      }
    }

    acoef = Sxx1.size(0) * Sxx1.size(1);
    for (i = 0; i < acoef; i++) {
      cdiff = Sxx1[i].re;
      noverlap = Sxx1[i].im;
      if (noverlap == 0.0) {
        unusedU2 = cdiff / k1;
        cdiff = 0.0;
      } else if (cdiff == 0.0) {
        unusedU2 = 0.0;
        cdiff = noverlap / k1;
      } else {
        unusedU2 = cdiff / k1;
        cdiff = noverlap / k1;
      }

      Sxx1[i].re = unusedU2;
      Sxx1[i].im = cdiff;
    }

    psdfreqvec(options.nfft, options.Fs, x1);
    acoef = x1.size(0);
    xStart = x1.reshape(acoef, 1);
    computepsd(Sxx1, xStart, options.range, options.nfft, options.Fs,
               varargout_f1, f, units_data, units_size);
    acoef = varargout_f1.size(0) * varargout_f1.size(1);
    Pxy2.set_size(varargout_f1.size(0), varargout_f1.size(1));
    for (csz_idx_0 = 0; csz_idx_0 < acoef; csz_idx_0++) {
      Pxy2[csz_idx_0] = rt_hypotd_snf(varargout_f1[csz_idx_0].re,
        varargout_f1[csz_idx_0].im);
    }

    acoef = Pxy2.size(0) * Pxy2.size(1);
    for (csz_idx_0 = 0; csz_idx_0 < acoef; csz_idx_0++) {
      Pxy2[csz_idx_0] = log10(Pxy2[csz_idx_0]);
    }

    acoef = Pxy2.size(0) * Pxy2.size(1);
    for (i = 0; i < acoef; i++) {
      Pxy2[i] = (10.0 * Pxy2[i] + 300.0) - 300.0;
    }

    acoef = varargout_f1.size(0) * varargout_f1.size(1);
    arg2.set_size(varargout_f1.size(0), varargout_f1.size(1));
    for (csz_idx_0 = 0; csz_idx_0 < acoef; csz_idx_0++) {
      arg2[csz_idx_0] = rt_atan2d_snf(varargout_f1[csz_idx_0].im,
        varargout_f1[csz_idx_0].re);
    }
  }
}

//
// File trailer for cpsd_analysis.cpp
//
// [EOF]
//
