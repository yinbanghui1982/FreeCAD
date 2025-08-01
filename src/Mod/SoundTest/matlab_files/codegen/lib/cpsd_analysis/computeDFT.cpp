//
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "datawrap.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &xin
//                double nfft
//                double varargin_1
//                ::coder::array<creal_T, 1U> &Xx
//                ::coder::array<double, 1U> &f
// Return Type  : void
//
namespace cpsd
{
  void computeDFT(const ::coder::array<double, 1U> &xin, double nfft, double
                  varargin_1, ::coder::array<creal_T, 1U> &Xx, ::coder::array<
                  double, 1U> &f)
  {
    ::coder::array<creal_T, 1U> b_fv;
    ::coder::array<creal_T, 1U> fv;
    ::coder::array<creal_T, 1U> wwc;
    ::coder::array<double, 2U> costab;
    ::coder::array<double, 2U> sintab;
    ::coder::array<double, 2U> sintabinv;
    ::coder::array<double, 2U> wrappedData;
    ::coder::array<double, 1U> b_xin;
    ::coder::array<double, 1U> xw;
    int N2blue;
    int b_nfft;
    int i;
    int rt;
    int xidx;
    xw.set_size((static_cast<int>(nfft)));
    xidx = static_cast<int>(nfft);
    for (i = 0; i < xidx; i++) {
      xw[i] = 0.0;
    }

    if (xin.size(0) > nfft) {
      xidx = xin.size(0);
      b_xin.set_size(xin.size(0));
      for (i = 0; i < xidx; i++) {
        b_xin[i] = xin[i];
      }

      datawrap(b_xin, nfft, wrappedData);
      xidx = wrappedData.size(0) * wrappedData.size(1);
      for (i = 0; i < xidx; i++) {
        xw[i] = wrappedData[i];
      }
    } else {
      xw.set_size(xin.size(0));
      xidx = xin.size(0);
      for (i = 0; i < xidx; i++) {
        xw[i] = xin[i];
      }
    }

    b_nfft = static_cast<int>(nfft);
    if (xw.size(0) == 0) {
      Xx.set_size((static_cast<int>(nfft)));
      xidx = static_cast<int>(nfft);
      for (i = 0; i < xidx; i++) {
        Xx[i].re = 0.0;
        Xx[i].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0);
      coder::internal::FFTImplementationCallback::get_algo_sizes((static_cast<
        int>(nfft)), (useRadix2), (&N2blue), (&xidx));
      coder::internal::FFTImplementationCallback::generate_twiddle_tables((xidx),
        (useRadix2), (costab), (sintab), (sintabinv));
      if (useRadix2) {
        Xx.set_size((static_cast<int>(nfft)));
        if (static_cast<int>(nfft) > xw.size(0)) {
          xidx = static_cast<int>(nfft);
          Xx.set_size((static_cast<int>(nfft)));
          for (i = 0; i < xidx; i++) {
            Xx[i].re = 0.0;
            Xx[i].im = 0.0;
          }
        }

        coder::internal::FFTImplementationCallback::doHalfLengthRadix2((xw), (Xx),
          (static_cast<int>(nfft)), (costab), (sintab));
      } else {
        double nt_re;
        int i1;
        int idx;
        int k;
        int nInt2m1;
        i = static_cast<int>(nfft) & 1;
        if (i == 0) {
          int nInt2;
          xidx = static_cast<int>(nfft) / 2;
          nInt2m1 = (xidx + xidx) - 1;
          wwc.set_size(nInt2m1);
          idx = xidx;
          rt = 0;
          wwc[xidx - 1].re = 1.0;
          wwc[xidx - 1].im = 0.0;
          nInt2 = xidx << 1;
          for (k = 0; k <= xidx - 2; k++) {
            double nt_im;
            int y;
            y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= y) {
              rt += y - nInt2;
            } else {
              rt += y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(xidx);
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
          for (k = i1; k >= xidx; k--) {
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
            double nt_im;
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

        Xx.set_size((static_cast<int>(nfft)));
        if (static_cast<int>(nfft) > xw.size(0)) {
          xidx = static_cast<int>(nfft);
          Xx.set_size((static_cast<int>(nfft)));
          for (i1 = 0; i1 < xidx; i1++) {
            Xx[i1].re = 0.0;
            Xx[i1].im = 0.0;
          }
        }

        if ((N2blue != 1) && (i == 0)) {
          coder::internal::FFTImplementationCallback::doHalfLengthBluestein((xw),
            (Xx), (xw.size(0)), (static_cast<int>(nfft)), (N2blue), (wwc),
            (costab), (sintab), (costab), (sintabinv));
        } else {
          xidx = static_cast<int>(nfft);
          idx = xw.size(0);
          if (xidx < idx) {
            idx = xidx;
          }

          xidx = 0;
          for (k = 0; k < idx; k++) {
            nInt2m1 = (static_cast<int>(nfft) + k) - 1;
            Xx[k].re = wwc[nInt2m1].re * xw[xidx];
            Xx[k].im = wwc[nInt2m1].im * -xw[xidx];
            xidx++;
          }

          i = idx + 1;
          for (k = i; k <= b_nfft; k++) {
            Xx[k - 1].re = 0.0;
            Xx[k - 1].im = 0.0;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((Xx),
            (N2blue), (costab), (sintab), (fv));
          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
            (N2blue), (costab), (sintab), (b_fv));
          b_fv.set_size(fv.size(0));
          xidx = fv.size(0);
          for (i = 0; i < xidx; i++) {
            nt_re = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
            b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
            b_fv[i].im = nt_re;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv),
            (N2blue), (costab), (sintabinv), (fv));
          if (fv.size(0) > 1) {
            nt_re = 1.0 / static_cast<double>(fv.size(0));
            xidx = fv.size(0);
            for (i = 0; i < xidx; i++) {
              fv[i].re = nt_re * fv[i].re;
              fv[i].im = nt_re * fv[i].im;
            }
          }

          idx = 0;
          i = static_cast<int>(nfft);
          i1 = wwc.size(0);
          for (k = i; k <= i1; k++) {
            Xx[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1]
              .im;
            Xx[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1]
              .re;
            idx++;
          }
        }
      }
    }

    psdfreqvec(nfft, varargin_1, f);
  }
}

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
