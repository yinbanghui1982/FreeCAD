//
// File: fft.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:06:11
//

// Include Files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                double varargin_1
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
namespace corr
{
  void fft(const ::coder::array<double, 1U> &x, double varargin_1, ::coder::
           array<creal_T, 1U> &y)
  {
    ::coder::array<creal_T, 1U> b_fv;
    ::coder::array<creal_T, 1U> fv;
    ::coder::array<creal_T, 1U> wwc;
    ::coder::array<double, 2U> costab;
    ::coder::array<double, 2U> costab1q;
    ::coder::array<double, 2U> sintab;
    ::coder::array<double, 2U> sintabinv;
    int N2blue;
    int nd2;
    int nfft;
    int rt;
    nfft = static_cast<int>(varargin_1);
    if ((x.size(0) == 0) || (0 == static_cast<int>(varargin_1))) {
      y.set_size((static_cast<int>(varargin_1)));
      nd2 = static_cast<int>(varargin_1);
      for (int i = 0; i < nd2; i++) {
        y[i].re = 0.0;
        y[i].im = 0.0;
      }
    } else {
      double nt_re;
      int i;
      int k;
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(varargin_1) > 0) && ((static_cast<int>
        (varargin_1) & (static_cast<int>(varargin_1) - 1)) == 0));
      coder::internal::FFTImplementationCallback::get_algo_sizes((static_cast<
        int>(varargin_1)), (useRadix2), (&N2blue), (&nd2));
      nt_re = 6.2831853071795862 / static_cast<double>(nd2);
      rt = nd2 / 2 / 2;
      costab1q.set_size(1, (rt + 1));
      costab1q[0] = 1.0;
      nd2 = rt / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = cos(nt_re * (static_cast<double>(k) + 1.0));
      }

      i = nd2 + 2;
      nd2 = rt - 1;
      for (k = i; k <= nd2; k++) {
        costab1q[k] = sin(nt_re * static_cast<double>(rt - k));
      }

      costab1q[rt] = 0.0;
      if (!useRadix2) {
        rt = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (nd2 + 1));
        for (k = 0; k < rt; k++) {
          sintabinv[k + 1] = costab1q[(rt - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - rt];
        }

        for (k = 0; k < rt; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(rt - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - rt];
        }
      } else {
        rt = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < rt; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(rt - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - rt];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((x), (
          static_cast<int>(varargin_1)), (costab), (sintab), (y));
      } else {
        int idx;
        int nInt2m1;
        if ((static_cast<int>(varargin_1) != 1) && ((static_cast<int>(varargin_1)
              & 1) == 0)) {
          int nInt2;
          nd2 = static_cast<int>(varargin_1) / 2;
          nInt2m1 = (nd2 + nd2) - 1;
          wwc.set_size(nInt2m1);
          idx = nd2;
          rt = 0;
          wwc[nd2 - 1].re = 1.0;
          wwc[nd2 - 1].im = 0.0;
          nInt2 = nd2 << 1;
          for (k = 0; k <= nd2 - 2; k++) {
            double nt_im;
            int b_y;
            b_y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= b_y) {
              rt += b_y - nInt2;
            } else {
              rt += b_y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(nd2);
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
          i = nInt2m1 - 1;
          for (k = i; k >= nd2; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        } else {
          int nInt2;
          nInt2m1 = (static_cast<int>(varargin_1) + static_cast<int>(varargin_1))
            - 1;
          wwc.set_size(nInt2m1);
          idx = static_cast<int>(varargin_1);
          rt = 0;
          wwc[static_cast<int>(varargin_1) - 1].re = 1.0;
          wwc[static_cast<int>(varargin_1) - 1].im = 0.0;
          nInt2 = static_cast<int>(varargin_1) << 1;
          i = static_cast<int>(varargin_1);
          for (k = 0; k <= i - 2; k++) {
            double nt_im;
            int b_y;
            b_y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= b_y) {
              rt += b_y - nInt2;
            } else {
              rt += b_y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(static_cast<int>(varargin_1));
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
          i = nInt2m1 - 1;
          for (k = i; k >= nfft; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        }

        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > x.size(0)) {
          nd2 = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (i = 0; i < nd2; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
          }
        }

        if ((N2blue != 1) && ((static_cast<int>(varargin_1) & 1) == 0)) {
          coder::internal::FFTImplementationCallback::doHalfLengthBluestein((x),
            (y), (x.size(0)), (static_cast<int>(varargin_1)), (N2blue), (wwc),
            (costab), (sintab), (costab), (sintabinv));
        } else {
          nd2 = static_cast<int>(varargin_1);
          nInt2m1 = x.size(0);
          if (nd2 < nInt2m1) {
            nInt2m1 = nd2;
          }

          nd2 = 0;
          for (k = 0; k < nInt2m1; k++) {
            rt = (static_cast<int>(varargin_1) + k) - 1;
            y[k].re = wwc[rt].re * x[nd2];
            y[k].im = wwc[rt].im * -x[nd2];
            nd2++;
          }

          i = nInt2m1 + 1;
          for (k = i; k <= nfft; k++) {
            y[k - 1].re = 0.0;
            y[k - 1].im = 0.0;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((y),
            (N2blue), (costab), (sintab), (fv));
          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
            (N2blue), (costab), (sintab), (b_fv));
          b_fv.set_size(fv.size(0));
          nd2 = fv.size(0);
          for (i = 0; i < nd2; i++) {
            nt_re = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
            b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
            b_fv[i].im = nt_re;
          }

          coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv),
            (N2blue), (costab), (sintabinv), (fv));
          if (fv.size(0) > 1) {
            nt_re = 1.0 / static_cast<double>(fv.size(0));
            nd2 = fv.size(0);
            for (i = 0; i < nd2; i++) {
              fv[i].re = nt_re * fv[i].re;
              fv[i].im = nt_re * fv[i].im;
            }
          }

          idx = 0;
          i = static_cast<int>(varargin_1);
          nd2 = wwc.size(0);
          for (k = i; k <= nd2; k++) {
            y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1]
              .im;
            y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1]
              .re;
            idx++;
          }
        }
      }
    }
  }
}

//
// File trailer for fft.cpp
//
// [EOF]
//
