//
// File: fft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

// Include Files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                double varargin_1
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
namespace coder {
void fft(const ::coder::array<double, 1U> &x, double varargin_1,
         ::coder::array<creal_T, 1U> &y)
{
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  int iDelta2;
  int nd2;
  if ((x.size(0) == 0) || (static_cast<int>(varargin_1) == 0)) {
    nd2 = static_cast<int>(varargin_1);
    y.set_size(nd2);
    for (int ju{0}; ju < nd2; ju++) {
      y[ju].re = 0.0;
      y[ju].im = 0.0;
    }
  } else {
    double temp_im;
    int j;
    int ju;
    int k;
    boolean_T useRadix2;
    useRadix2 = ((static_cast<int>(varargin_1) > 0) &&
                 ((static_cast<int>(varargin_1) &
                   (static_cast<int>(varargin_1) - 1)) == 0));
    internal::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(varargin_1), useRadix2, &iDelta2, &nd2);
    temp_im = 6.2831853071795862 / static_cast<double>(nd2);
    j = nd2 / 2 / 2;
    costab1q.set_size(1, j + 1);
    costab1q[0] = 1.0;
    nd2 = j / 2 - 1;
    for (k = 0; k <= nd2; k++) {
      costab1q[k + 1] = std::cos(temp_im * (static_cast<double>(k) + 1.0));
    }
    ju = nd2 + 2;
    nd2 = j - 1;
    for (k = ju; k <= nd2; k++) {
      costab1q[k] = std::sin(temp_im * static_cast<double>(j - k));
    }
    costab1q[j] = 0.0;
    if (!useRadix2) {
      j = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nd2 + 1);
      for (k = 0; k < j; k++) {
        sintabinv[k + 1] = costab1q[(j - k) - 1];
      }
      ju = costab1q.size(1);
      for (k = ju; k <= nd2; k++) {
        sintabinv[k] = costab1q[k - j];
      }
      for (k = 0; k < j; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(j - k) - 1];
      }
      ju = costab1q.size(1);
      for (k = ju; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - j];
      }
    } else {
      j = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < j; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(j - k) - 1];
      }
      ju = costab1q.size(1);
      for (k = ju; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - j];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      y.set_size(static_cast<int>(varargin_1));
      if (static_cast<int>(varargin_1) > x.size(0)) {
        y.set_size(static_cast<int>(varargin_1));
        nd2 = static_cast<int>(varargin_1);
        for (ju = 0; ju < nd2; ju++) {
          y[ju].re = 0.0;
          y[ju].im = 0.0;
        }
      }
      if (static_cast<int>(varargin_1) != 1) {
        internal::FFTImplementationCallback::doHalfLengthRadix2(
            x, y, static_cast<int>(varargin_1), costab, sintab);
      } else {
        double temp_re;
        double temp_re_tmp;
        double twid_re;
        int i;
        int istart;
        int nRowsD2;
        nd2 = x.size(0);
        istart = static_cast<int>(varargin_1);
        if (nd2 <= istart) {
          istart = nd2;
        }
        iDelta2 = static_cast<int>(varargin_1) - 2;
        nRowsD2 = static_cast<int>(varargin_1) / 2;
        k = nRowsD2 / 2;
        nd2 = 0;
        ju = 0;
        for (i = 0; i <= istart - 2; i++) {
          y[nd2].re = x[i];
          y[nd2].im = 0.0;
          j = static_cast<int>(varargin_1);
          useRadix2 = true;
          while (useRadix2) {
            j >>= 1;
            ju ^= j;
            useRadix2 = ((ju & j) == 0);
          }
          nd2 = ju;
        }
        y[nd2].re = x[istart - 1];
        y[nd2].im = 0.0;
        if (static_cast<int>(varargin_1) > 1) {
          for (i = 0; i <= iDelta2; i += 2) {
            temp_re_tmp = y[i + 1].re;
            temp_im = y[i + 1].im;
            temp_re = y[i].re;
            twid_re = y[i].im;
            y[i + 1].re = temp_re - temp_re_tmp;
            y[i + 1].im = twid_re - temp_im;
            y[i].re = temp_re + temp_re_tmp;
            y[i].im = twid_re + temp_im;
          }
        }
        nd2 = 2;
        iDelta2 = 4;
        ju = ((k - 1) << 2) + 1;
        while (k > 0) {
          int b_temp_re_tmp;
          for (i = 0; i < ju; i += iDelta2) {
            b_temp_re_tmp = i + nd2;
            temp_re = y[b_temp_re_tmp].re;
            temp_im = y[b_temp_re_tmp].im;
            y[b_temp_re_tmp].re = y[i].re - temp_re;
            y[b_temp_re_tmp].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }
          istart = 1;
          for (j = k; j < nRowsD2; j += k) {
            double twid_im;
            int ihi;
            twid_re = costab[j];
            twid_im = sintab[j];
            i = istart;
            ihi = istart + ju;
            while (i < ihi) {
              b_temp_re_tmp = i + nd2;
              temp_re_tmp = y[b_temp_re_tmp].im;
              temp_im = y[b_temp_re_tmp].re;
              temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
              temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
              y[b_temp_re_tmp].re = y[i].re - temp_re;
              y[b_temp_re_tmp].im = y[i].im - temp_im;
              y[i].re = y[i].re + temp_re;
              y[i].im = y[i].im + temp_im;
              i += iDelta2;
            }
            istart++;
          }
          k /= 2;
          nd2 = iDelta2;
          iDelta2 += iDelta2;
          ju -= nd2;
        }
      }
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          x, iDelta2, static_cast<int>(varargin_1), costab, sintab, sintabinv,
          y);
    }
  }
}

} // namespace coder

//
// File trailer for fft.cpp
//
// [EOF]
//
