//
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "cpsd_analysis_rtwutil.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
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
namespace coder {
void computeDFT(const ::coder::array<double, 1U> &xin, double nfft,
                double varargin_1, ::coder::array<creal_T, 1U> &Xx,
                ::coder::array<double, 1U> &f)
{
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 2U> wrappedData;
  array<double, 1U> xw;
  int b_remainder;
  int i;
  int k;
  int loop_ub_tmp;
  int nFullPasses;
  int offset;
  loop_ub_tmp = static_cast<int>(nfft);
  xw.set_size(loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    xw[i] = 0.0;
  }
  if (xin.size(0) > nfft) {
    if (xin.size(0) == 1) {
      wrappedData.set_size(1, loop_ub_tmp);
      for (i = 0; i < loop_ub_tmp; i++) {
        wrappedData[i] = 0.0;
      }
    } else {
      wrappedData.set_size(loop_ub_tmp, 1);
      for (i = 0; i < loop_ub_tmp; i++) {
        wrappedData[i] = 0.0;
      }
    }
    nFullPasses = div_s32(xin.size(0), static_cast<int>(nfft));
    offset = nFullPasses * static_cast<int>(nfft);
    b_remainder = (xin.size(0) - offset) - 1;
    for (k = 0; k <= b_remainder; k++) {
      wrappedData[k] = xin[offset + k];
    }
    i = b_remainder + 2;
    for (k = i; k <= loop_ub_tmp; k++) {
      wrappedData[k - 1] = 0.0;
    }
    for (b_remainder = 0; b_remainder < nFullPasses; b_remainder++) {
      offset = b_remainder * static_cast<int>(nfft);
      for (k = 0; k < loop_ub_tmp; k++) {
        wrappedData[k] = wrappedData[k] + xin[offset + k];
      }
    }
    offset = wrappedData.size(0) * wrappedData.size(1);
    for (i = 0; i < offset; i++) {
      xw[i] = wrappedData[i];
    }
  } else {
    xw.set_size(xin.size(0));
    offset = xin.size(0);
    for (i = 0; i < offset; i++) {
      xw[i] = xin[i];
    }
  }
  if (xw.size(0) == 0) {
    Xx.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
      Xx[i].re = 0.0;
      Xx[i].im = 0.0;
    }
  } else {
    double e;
    int n;
    boolean_T useRadix2;
    useRadix2 = ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0);
    nFullPasses = 1;
    if (useRadix2) {
      offset = static_cast<int>(nfft);
    } else {
      boolean_T exitg1;
      n = (static_cast<int>(nfft) + static_cast<int>(nfft)) - 1;
      b_remainder = 31;
      offset = 0;
      exitg1 = false;
      while ((!exitg1) && (b_remainder - offset > 1)) {
        k = (offset + b_remainder) >> 1;
        nFullPasses = 1 << k;
        if (nFullPasses == n) {
          b_remainder = k;
          exitg1 = true;
        } else if (nFullPasses > n) {
          b_remainder = k;
        } else {
          offset = k;
        }
      }
      nFullPasses = 1 << b_remainder;
      offset = nFullPasses;
    }
    e = 6.2831853071795862 / static_cast<double>(offset);
    n = offset / 2 / 2;
    costab1q.set_size(1, n + 1);
    costab1q[0] = 1.0;
    b_remainder = n / 2 - 1;
    for (k = 0; k <= b_remainder; k++) {
      costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
    }
    i = b_remainder + 2;
    b_remainder = n - 1;
    for (k = i; k <= b_remainder; k++) {
      costab1q[k] = std::sin(e * static_cast<double>(n - k));
    }
    costab1q[n] = 0.0;
    if (!useRadix2) {
      n = costab1q.size(1) - 1;
      b_remainder = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, b_remainder + 1);
      sintab.set_size(1, b_remainder + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, b_remainder + 1);
      for (k = 0; k < n; k++) {
        sintabinv[k + 1] = costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= b_remainder; k++) {
        sintabinv[k] = costab1q[k - n];
      }
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= b_remainder; k++) {
        costab[k] = -costab1q[b_remainder - k];
        sintab[k] = -costab1q[k - n];
      }
    } else {
      n = costab1q.size(1) - 1;
      b_remainder = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, b_remainder + 1);
      sintab.set_size(1, b_remainder + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= b_remainder; k++) {
        costab[k] = -costab1q[b_remainder - k];
        sintab[k] = -costab1q[k - n];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      Xx.set_size(loop_ub_tmp);
      if (static_cast<int>(nfft) > xw.size(0)) {
        Xx.set_size(loop_ub_tmp);
        for (i = 0; i < loop_ub_tmp; i++) {
          Xx[i].re = 0.0;
          Xx[i].im = 0.0;
        }
      }
      internal::fft::FFTImplementationCallback::doHalfLengthRadix2(
          xw, Xx, static_cast<int>(nfft), costab, sintab);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xw, nFullPasses, static_cast<int>(nfft), costab, sintab, sintabinv,
          Xx);
    }
  }
  psdfreqvec(nfft, varargin_1, f);
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
