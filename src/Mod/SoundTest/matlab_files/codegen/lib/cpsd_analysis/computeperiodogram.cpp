//
// File: computeperiodogram.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "computeperiodogram.h"
#include "FFTImplementationCallback.h"
#include "bsxfun.h"
#include "computeDFT.h"
#include "cpsd_analysis_data.h"
#include "cpsd_analysis_internal_types.h"
#include "datawrap.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const cell_wrap_15 x[2]
//                const ::coder::array<double, 1U> &win
//                double nfft
//                double Fs
//                ::coder::array<creal_T, 2U> &Pxx
//                ::coder::array<double, 1U> &F
// Return Type  : void
//
namespace cpsd
{
  void computeperiodogram(const cell_wrap_15 x[2], const ::coder::array<double,
    1U> &win, double nfft, double Fs, ::coder::array<creal_T, 2U> &Pxx, ::coder::
    array<double, 1U> &F)
  {
    ::coder::array<creal_T, 2U> b_Xx;
    ::coder::array<creal_T, 1U> Xx;
    ::coder::array<creal_T, 1U> b_fv;
    ::coder::array<creal_T, 1U> fv;
    ::coder::array<creal_T, 1U> r;
    ::coder::array<creal_T, 1U> wwc;
    ::coder::array<double, 2U> costab;
    ::coder::array<double, 2U> sintab;
    ::coder::array<double, 2U> sintabinv;
    ::coder::array<double, 2U> wrappedData;
    ::coder::array<double, 2U> xw;
    ::coder::array<double, 1U> b_yw;
    ::coder::array<double, 1U> yw;
    double b_win;
    double nt_im;
    double nt_re;
    int N2blue;
    int b_nfft;
    int i;
    int k;
    int nInt2m1;
    int nRows;
    int rt;
    if (rtIsNaN(Fs)) {
      Fs = 6.2831853071795862;
    }

    bsxfun(x[0].f1, win, yw);
    computeDFT(yw, nfft, Fs, Xx, F);
    bsxfun(x[1].f1, win, yw);
    b_win = 0.0;
    nInt2m1 = win.size(0);
    for (i = 0; i < nInt2m1; i++) {
      b_win += win[i] * win[i];
    }

    xw.set_size((static_cast<int>(nfft)), 1);
    nInt2m1 = static_cast<int>(nfft);
    for (i = 0; i < nInt2m1; i++) {
      xw[i] = 0.0;
    }

    if (yw.size(0) > nfft) {
      nInt2m1 = yw.size(0);
      b_yw.set_size(yw.size(0));
      for (i = 0; i < nInt2m1; i++) {
        b_yw[i] = yw[i];
      }

      datawrap(b_yw, nfft, wrappedData);
      nInt2m1 = wrappedData.size(0) * wrappedData.size(1);
      for (i = 0; i < nInt2m1; i++) {
        xw[i] = wrappedData[i];
      }
    } else {
      xw.set_size(yw.size(0), 1);
      nInt2m1 = yw.size(0);
      for (i = 0; i < nInt2m1; i++) {
        xw[i] = yw[i];
      }
    }

    b_nfft = static_cast<int>(nfft);
    if (xw.size(0) == 0) {
      b_Xx.set_size((static_cast<int>(nfft)), 1);
      nInt2m1 = static_cast<int>(nfft);
      for (i = 0; i < nInt2m1; i++) {
        b_Xx[i].re = 0.0;
        b_Xx[i].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0);
      coder::internal::FFTImplementationCallback::get_algo_sizes((static_cast<
        int>(nfft)), (useRadix2), (&N2blue), (&nRows));
      coder::internal::FFTImplementationCallback::generate_twiddle_tables((nRows),
        (useRadix2), (costab), (sintab), (sintabinv));
      if (useRadix2) {
        b_Xx.set_size((static_cast<int>(nfft)), 1);
        if (static_cast<int>(nfft) > xw.size(0)) {
          b_Xx.set_size((static_cast<int>(nfft)), 1);
          nInt2m1 = static_cast<int>(nfft);
          for (i = 0; i < nInt2m1; i++) {
            b_Xx[i].re = 0.0;
            b_Xx[i].im = 0.0;
          }
        }

        r.set_size((static_cast<int>(nfft)));
        if (static_cast<int>(nfft) > xw.size(0)) {
          nInt2m1 = static_cast<int>(nfft);
          r.set_size((static_cast<int>(nfft)));
          for (i = 0; i < nInt2m1; i++) {
            r[i].re = 0.0;
            r[i].im = 0.0;
          }
        }

        coder::internal::FFTImplementationCallback::doHalfLengthRadix2((xw), (r),
          (static_cast<int>(nfft)), (costab), (sintab));
        nInt2m1 = r.size(0);
        for (i = 0; i < nInt2m1; i++) {
          b_Xx[i] = r[i];
        }
      } else {
        int i1;
        int idx;
        i = static_cast<int>(nfft) & 1;
        if (i == 0) {
          int nInt2;
          nRows = static_cast<int>(nfft) / 2;
          nInt2m1 = (nRows + nRows) - 1;
          wwc.set_size(nInt2m1);
          idx = nRows;
          rt = 0;
          wwc[nRows - 1].re = 1.0;
          wwc[nRows - 1].im = 0.0;
          nInt2 = nRows << 1;
          for (k = 0; k <= nRows - 2; k++) {
            int y;
            y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= y) {
              rt += y - nInt2;
            } else {
              rt += y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(nRows);
            if (nt_im == 0.0) {
              nt_re = 1.0;
              nt_im = 0.0;
            } else {
              nt_re = cos(nt_im);
              nt_im = sin(nt_im);
            }

            wwc[idx - 2].re = nt_re;
            wwc[idx - 2].im = -nt_im;
            idx--;
          }

          idx = 0;
          i1 = nInt2m1 - 1;
          for (k = i1; k >= nRows; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        } else {
          int nInt2;
          nInt2m1 = (static_cast<int>(nfft) + static_cast<int>(nfft)) - 1;
          wwc.set_size(nInt2m1);
          idx = static_cast<int>(nfft);
          rt = 0;
          wwc[static_cast<int>(nfft) - 1].re = 1.0;
          wwc[static_cast<int>(nfft) - 1].im = 0.0;
          nInt2 = static_cast<int>(nfft) << 1;
          i1 = static_cast<int>(nfft);
          for (k = 0; k <= i1 - 2; k++) {
            int y;
            y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= y) {
              rt += y - nInt2;
            } else {
              rt += y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(static_cast<int>(nfft));
            if (nt_im == 0.0) {
              nt_re = 1.0;
              nt_im = 0.0;
            } else {
              nt_re = cos(nt_im);
              nt_im = sin(nt_im);
            }

            wwc[idx - 2].re = nt_re;
            wwc[idx - 2].im = -nt_im;
            idx--;
          }

          idx = 0;
          i1 = nInt2m1 - 1;
          for (k = i1; k >= b_nfft; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        }

        b_Xx.set_size((static_cast<int>(nfft)), 1);
        if (static_cast<int>(nfft) > xw.size(0)) {
          b_Xx.set_size((static_cast<int>(nfft)), 1);
          nInt2m1 = static_cast<int>(nfft);
          for (i1 = 0; i1 < nInt2m1; i1++) {
            b_Xx[i1].re = 0.0;
            b_Xx[i1].im = 0.0;
          }
        }

        if ((N2blue != 1) && (i == 0)) {
          useRadix2 = true;
        } else {
          useRadix2 = false;
        }

        r.set_size((static_cast<int>(nfft)));
        if (static_cast<int>(nfft) > xw.size(0)) {
          nInt2m1 = static_cast<int>(nfft);
          r.set_size((static_cast<int>(nfft)));
          for (i = 0; i < nInt2m1; i++) {
            r[i].re = 0.0;
            r[i].im = 0.0;
          }
        }

        if (useRadix2) {
          coder::internal::FFTImplementationCallback::doHalfLengthBluestein((xw),
            (r), (xw.size(0)), (static_cast<int>(nfft)), (N2blue), (wwc),
            (costab), (sintab), (costab), (sintabinv));
        } else {
          nRows = static_cast<int>(nfft);
          idx = xw.size(0);
          if (nRows < idx) {
            idx = nRows;
          }

          nInt2m1 = 0;
          for (k = 0; k < idx; k++) {
            nRows = (static_cast<int>(nfft) + k) - 1;
            r[k].re = wwc[nRows].re * xw[nInt2m1];
            r[k].im = wwc[nRows].im * -xw[nInt2m1];
            nInt2m1++;
          }

          i = idx + 1;
          for (k = i; k <= b_nfft; k++) {
            r[k - 1].re = 0.0;
            r[k - 1].im = 0.0;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((r),
            (N2blue), (costab), (sintab), (fv));
          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
            (N2blue), (costab), (sintab), (b_fv));
          b_fv.set_size(fv.size(0));
          nInt2m1 = fv.size(0);
          for (i = 0; i < nInt2m1; i++) {
            nt_re = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
            b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
            b_fv[i].im = nt_re;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv),
            (N2blue), (costab), (sintabinv), (fv));
          if (fv.size(0) > 1) {
            nt_re = 1.0 / static_cast<double>(fv.size(0));
            nInt2m1 = fv.size(0);
            for (i = 0; i < nInt2m1; i++) {
              fv[i].re = nt_re * fv[i].re;
              fv[i].im = nt_re * fv[i].im;
            }
          }

          idx = 0;
          i = static_cast<int>(nfft);
          i1 = wwc.size(0);
          for (k = i; k <= i1; k++) {
            r[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1]
              .im;
            r[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1]
              .re;
            idx++;
          }
        }

        nInt2m1 = r.size(0);
        for (i = 0; i < nInt2m1; i++) {
          b_Xx[i] = r[i];
        }
      }
    }

    psdfreqvec(nfft, Fs, F);
    i = b_Xx.size(0) * b_Xx.size(1);
    b_Xx.set_size(b_Xx.size(0), 1);
    nInt2m1 = i - 1;
    for (i = 0; i <= nInt2m1; i++) {
      b_Xx[i].im = -b_Xx[i].im;
    }

    nRows = b_Xx.size(0);
    nInt2m1 = Xx.size(0);
    if (nRows < nInt2m1) {
      nInt2m1 = nRows;
    }

    if (Xx.size(0) == b_Xx.size(0)) {
      nInt2m1 = Xx.size(0);
    }

    Pxx.set_size(nInt2m1, 1);
    i = Pxx.size(0) - 1;
    for (k = 0; k <= i; k++) {
      Pxx[k].re = Xx[k].re * b_Xx[k].re - Xx[k].im * b_Xx[k].im;
      Pxx[k].im = Xx[k].re * b_Xx[k].im + Xx[k].im * b_Xx[k].re;
    }

    i = Pxx.size(0) * Pxx.size(1);
    Pxx.set_size(Pxx.size(0), 1);
    nInt2m1 = i - 1;
    for (i = 0; i <= nInt2m1; i++) {
      double ai;
      nt_re = Pxx[i].re;
      ai = Pxx[i].im;
      if (ai == 0.0) {
        nt_im = nt_re / b_win;
        nt_re = 0.0;
      } else if (nt_re == 0.0) {
        nt_im = 0.0;
        nt_re = ai / b_win;
      } else {
        nt_im = nt_re / b_win;
        nt_re = ai / b_win;
      }

      Pxx[i].re = nt_im;
      Pxx[i].im = nt_re;
    }
  }
}

//
// File trailer for computeperiodogram.cpp
//
// [EOF]
//
