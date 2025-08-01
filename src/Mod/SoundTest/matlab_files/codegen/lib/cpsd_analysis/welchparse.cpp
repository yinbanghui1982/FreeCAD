//
// File: welchparse.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "welchparse.h"
#include "cpsd_analysis_internal_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Declarations
namespace cpsd
{
  static int div_s32_floor(int numerator, int denominator);
  static double rt_powd_snf(double u0, double u1);
}

// Function Definitions
//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
namespace cpsd
{
  static int div_s32_floor(int numerator, int denominator)
  {
    unsigned int absNumerator;
    int quotient;
    if (denominator == 0) {
      if (numerator >= 0) {
        quotient = MAX_int32_T;
      } else {
        quotient = MIN_int32_T;
      }
    } else {
      unsigned int absDenominator;
      unsigned int tempAbsQuotient;
      boolean_T quotientNeedsNegation;
      if (numerator < 0) {
        absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
      } else {
        absNumerator = static_cast<unsigned int>(numerator);
      }

      if (denominator < 0) {
        absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
      } else {
        absDenominator = static_cast<unsigned int>(denominator);
      }

      quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
      tempAbsQuotient = absNumerator / absDenominator;
      if (quotientNeedsNegation) {
        absNumerator %= absDenominator;
        if (absNumerator > 0U) {
          tempAbsQuotient++;
        }

        quotient = -static_cast<int>(tempAbsQuotient);
      } else {
        quotient = static_cast<int>(tempAbsQuotient);
      }
    }

    return quotient;
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
  // Arguments    : const cell_wrap_1 x1[2]
  //                double varargin_4
  //                ::coder::array<double, 1U> &x
  //                double *M
  //                boolean_T *isreal_x
  //                ::coder::array<double, 1U> &y
  //                double *Ly
  //                ::coder::array<double, 1U> &win
  //                double *noverlap
  //                double *k
  //                double *L
  //                struct_T *options
  // Return Type  : void
  //
  namespace signal
  {
    namespace internal
    {
      namespace spectral
      {
        void welchparse(const cell_wrap_1 x1[2], double varargin_4, ::coder::
                        array<double, 1U> &x, double *M, boolean_T *isreal_x, ::
                        coder::array<double, 1U> &y, double *Ly, ::coder::array<
                        double, 1U> &win, double *noverlap, double *k, double *L,
                        struct_T *options)
        {
          static const char cv[8] = { 'o', 'n', 'e', 's', 'i', 'd', 'e', 'd' };

          ::coder::array<double, 2U> b_y;
          ::coder::array<double, 1U> b_win;
          double f;
          int b_L;
          int b_Ly;
          int b_M;
          int b_noverlap;
          int eint;
          int i;
          int nx;
          x.set_size(x1[0].f1.size(1));
          nx = x1[0].f1.size(1);
          for (i = 0; i < nx; i++) {
            x[i] = x1[0].f1[i];
          }

          y.set_size(x1[1].f1.size(1));
          nx = x1[1].f1.size(1);
          for (i = 0; i < nx; i++) {
            y[i] = x1[1].f1[i];
          }

          b_Ly = x1[1].f1.size(1);
          b_M = x1[0].f1.size(1);
          b_L = static_cast<int>(floor(static_cast<double>(x1[0].f1.size(1)) /
            4.5));
          b_noverlap = static_cast<int>(floor(0.5 * static_cast<double>(b_L)));
          if (fmod(static_cast<double>(b_L), 2.0) == 0.0) {
            nx = static_cast<int>(floor(static_cast<double>(b_L) / 2.0 - 1.0));
            b_y.set_size(1, (nx + 1));
            for (i = 0; i <= nx; i++) {
              b_y[i] = i;
            }

            win.set_size(b_y.size(1));
            nx = b_y.size(1);
            for (i = 0; i < nx; i++) {
              win[i] = 6.2831853071795862 * (b_y[i] / (static_cast<double>(b_L)
                - 1.0));
            }

            nx = win.size(0);
            for (int b_k = 0; b_k < nx; b_k++) {
              win[b_k] = cos(win[b_k]);
            }

            nx = win.size(0);
            for (i = 0; i < nx; i++) {
              win[i] = 0.54 - 0.46 * win[i];
            }

            b_win.set_size(((win.size(0) + div_s32_floor(1 - win.size(0), -1)) +
                            1));
            nx = win.size(0);
            for (i = 0; i < nx; i++) {
              b_win[i] = win[i];
            }

            nx = div_s32_floor(1 - win.size(0), -1);
            for (i = 0; i <= nx; i++) {
              b_win[i + win.size(0)] = win[(win.size(0) - i) - 1];
            }

            win.set_size(b_win.size(0));
            nx = b_win.size(0);
            for (i = 0; i < nx; i++) {
              win[i] = b_win[i];
            }
          } else {
            int b_k;
            int i1;
            int loop_ub;
            nx = static_cast<int>(floor((static_cast<double>(b_L) + 1.0) / 2.0 -
              1.0));
            b_y.set_size(1, (nx + 1));
            for (i = 0; i <= nx; i++) {
              b_y[i] = i;
            }

            win.set_size(b_y.size(1));
            nx = b_y.size(1);
            for (i = 0; i < nx; i++) {
              win[i] = 6.2831853071795862 * (b_y[i] / (static_cast<double>(b_L)
                - 1.0));
            }

            nx = win.size(0);
            for (b_k = 0; b_k < nx; b_k++) {
              win[b_k] = cos(win[b_k]);
            }

            nx = win.size(0);
            for (i = 0; i < nx; i++) {
              win[i] = 0.54 - 0.46 * win[i];
            }

            if (1 > win.size(0) - 1) {
              i = 0;
              b_k = 1;
              i1 = -1;
            } else {
              i = win.size(0) - 2;
              b_k = -1;
              i1 = 0;
            }

            nx = div_s32_floor(i1 - i, b_k);
            b_win.set_size(((win.size(0) + nx) + 1));
            loop_ub = win.size(0);
            for (i1 = 0; i1 < loop_ub; i1++) {
              b_win[i1] = win[i1];
            }

            for (i1 = 0; i1 <= nx; i1++) {
              b_win[i1 + win.size(0)] = win[i + b_k * i1];
            }

            win.set_size(b_win.size(0));
            nx = b_win.size(0);
            for (i = 0; i < nx; i++) {
              win[i] = b_win[i];
            }
          }

          f = frexp(static_cast<double>(b_L), &eint);
          if (f == 0.5) {
            eint--;
          }

          f = rt_powd_snf(2.0, static_cast<double>(eint));
          if (256.0 > f) {
            f = 256.0;
          }

          options->nfft = f;
          options->average = true;
          options->maxhold = false;
          options->minhold = false;
          options->MIMO = false;
          options->conflevel = rtNaN;
          options->isNFFTSingle = false;
          for (i = 0; i < 8; i++) {
            options->range[i] = cv[i];
          }

          options->centerdc = false;
          options->Fs = varargin_4;
          *k = (static_cast<double>(x1[0].f1.size(1)) - static_cast<double>
                (b_noverlap)) / static_cast<double>(b_L - b_noverlap);
          if (*k < 0.0) {
            *k = ceil(*k);
          } else {
            *k = floor(*k);
          }

          *M = b_M;
          *isreal_x = true;
          *Ly = b_Ly;
          *noverlap = b_noverlap;
          *L = b_L;
        }
      }
    }
  }
}

//
// File trailer for welchparse.cpp
//
// [EOF]
//
