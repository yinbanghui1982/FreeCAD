//
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:01:53
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cfloat>
#include <cmath>
#include <string.h>

// Function Declarations
static int div_s32(int numerator, int denominator);

static double rt_remd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int b_denominator;
    unsigned int b_numerator;
    if (numerator < 0) {
      b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      b_numerator = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      b_denominator = static_cast<unsigned int>(denominator);
    }
    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int>(b_numerator);
    } else {
      quotient = static_cast<int>(b_numerator);
    }
  }
  return quotient;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

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
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_remainder;
  int istart;
  int k;
  int loop_ub_tmp;
  int nFullPasses;
  int offset;
  loop_ub_tmp = static_cast<int>(nfft);
  xw.set_size(loop_ub_tmp);
  for (istart = 0; istart < loop_ub_tmp; istart++) {
    xw[istart] = 0.0;
  }
  if (xin.size(0) > nfft) {
    if (xin.size(0) == 1) {
      wrappedData.set_size(1, loop_ub_tmp);
      for (istart = 0; istart < loop_ub_tmp; istart++) {
        wrappedData[istart] = 0.0;
      }
    } else {
      wrappedData.set_size(loop_ub_tmp, 1);
      for (istart = 0; istart < loop_ub_tmp; istart++) {
        wrappedData[istart] = 0.0;
      }
    }
    nFullPasses = div_s32(xin.size(0), static_cast<int>(nfft));
    offset = nFullPasses * static_cast<int>(nfft);
    b_remainder = (xin.size(0) - offset) - 1;
    for (k = 0; k <= b_remainder; k++) {
      wrappedData[k] = xin[offset + k];
    }
    istart = b_remainder + 2;
    for (k = istart; k <= loop_ub_tmp; k++) {
      wrappedData[k - 1] = 0.0;
    }
    for (int j{0}; j < nFullPasses; j++) {
      offset = j * static_cast<int>(nfft);
      for (k = 0; k < loop_ub_tmp; k++) {
        wrappedData[k] = wrappedData[k] + xin[offset + k];
      }
    }
    offset = wrappedData.size(0) * wrappedData.size(1);
    for (istart = 0; istart < offset; istart++) {
      xw[istart] = wrappedData[istart];
    }
  } else {
    xw.set_size(xin.size(0));
    offset = xin.size(0);
    for (istart = 0; istart < offset; istart++) {
      xw[istart] = xin[istart];
    }
  }
  if ((xw.size(0) == 0) || (static_cast<int>(nfft) == 0)) {
    Xx.set_size(loop_ub_tmp);
    for (istart = 0; istart < loop_ub_tmp; istart++) {
      Xx[istart].re = 0.0;
      Xx[istart].im = 0.0;
    }
  } else {
    int ihi;
    boolean_T useRadix2;
    useRadix2 =
        ((static_cast<int>(nfft) > 0) &&
         ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0));
    nFullPasses = 1;
    if (useRadix2) {
      offset = static_cast<int>(nfft);
    } else {
      if (static_cast<int>(nfft) > 0) {
        ihi = (static_cast<int>(nfft) + static_cast<int>(nfft)) - 1;
        b_remainder = 31;
        if (ihi <= 1) {
          b_remainder = 0;
        } else {
          boolean_T exitg1;
          offset = 0;
          exitg1 = false;
          while ((!exitg1) && (b_remainder - offset > 1)) {
            k = (offset + b_remainder) >> 1;
            nFullPasses = 1 << k;
            if (nFullPasses == ihi) {
              b_remainder = k;
              exitg1 = true;
            } else if (nFullPasses > ihi) {
              b_remainder = k;
            } else {
              offset = k;
            }
          }
        }
        nFullPasses = 1 << b_remainder;
      }
      offset = nFullPasses;
    }
    temp_im = 6.2831853071795862 / static_cast<double>(offset);
    ihi = offset / 2 / 2;
    costab1q.set_size(1, ihi + 1);
    costab1q[0] = 1.0;
    b_remainder = ihi / 2 - 1;
    for (k = 0; k <= b_remainder; k++) {
      costab1q[k + 1] = std::cos(temp_im * (static_cast<double>(k) + 1.0));
    }
    istart = b_remainder + 2;
    b_remainder = ihi - 1;
    for (k = istart; k <= b_remainder; k++) {
      costab1q[k] = std::sin(temp_im * static_cast<double>(ihi - k));
    }
    costab1q[ihi] = 0.0;
    if (!useRadix2) {
      ihi = costab1q.size(1) - 1;
      b_remainder = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, b_remainder + 1);
      sintab.set_size(1, b_remainder + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, b_remainder + 1);
      for (k = 0; k < ihi; k++) {
        sintabinv[k + 1] = costab1q[(ihi - k) - 1];
      }
      istart = costab1q.size(1);
      for (k = istart; k <= b_remainder; k++) {
        sintabinv[k] = costab1q[k - ihi];
      }
      for (k = 0; k < ihi; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(ihi - k) - 1];
      }
      istart = costab1q.size(1);
      for (k = istart; k <= b_remainder; k++) {
        costab[k] = -costab1q[b_remainder - k];
        sintab[k] = -costab1q[k - ihi];
      }
    } else {
      ihi = costab1q.size(1) - 1;
      b_remainder = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, b_remainder + 1);
      sintab.set_size(1, b_remainder + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < ihi; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(ihi - k) - 1];
      }
      istart = costab1q.size(1);
      for (k = istart; k <= b_remainder; k++) {
        costab[k] = -costab1q[b_remainder - k];
        sintab[k] = -costab1q[k - ihi];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      Xx.set_size(loop_ub_tmp);
      if (static_cast<int>(nfft) > xw.size(0)) {
        Xx.set_size(loop_ub_tmp);
        for (istart = 0; istart < loop_ub_tmp; istart++) {
          Xx[istart].re = 0.0;
          Xx[istart].im = 0.0;
        }
      }
      if (static_cast<int>(nfft) != 1) {
        internal::fft::FFTImplementationCallback::doHalfLengthRadix2(
            xw, Xx, static_cast<int>(nfft), costab, sintab);
      } else {
        int i;
        int nRowsD2;
        offset = xw.size(0);
        istart = static_cast<int>(nfft);
        if (offset <= istart) {
          istart = offset;
        }
        offset = static_cast<int>(nfft) - 2;
        nRowsD2 = static_cast<int>(nfft) / 2;
        k = nRowsD2 / 2;
        b_remainder = 0;
        nFullPasses = 0;
        for (i = 0; i <= istart - 2; i++) {
          Xx[b_remainder].re = xw[i];
          Xx[b_remainder].im = 0.0;
          ihi = static_cast<int>(nfft);
          useRadix2 = true;
          while (useRadix2) {
            ihi >>= 1;
            nFullPasses ^= ihi;
            useRadix2 = ((nFullPasses & ihi) == 0);
          }
          b_remainder = nFullPasses;
        }
        Xx[b_remainder].re = xw[istart - 1];
        Xx[b_remainder].im = 0.0;
        if (static_cast<int>(nfft) > 1) {
          for (i = 0; i <= offset; i += 2) {
            temp_re_tmp = Xx[i + 1].re;
            temp_im = Xx[i + 1].im;
            temp_re = Xx[i].re;
            twid_re = Xx[i].im;
            Xx[i + 1].re = temp_re - temp_re_tmp;
            Xx[i + 1].im = twid_re - temp_im;
            Xx[i].re = temp_re + temp_re_tmp;
            Xx[i].im = twid_re + temp_im;
          }
        }
        b_remainder = 2;
        offset = 4;
        nFullPasses = ((k - 1) << 2) + 1;
        while (k > 0) {
          for (i = 0; i < nFullPasses; i += offset) {
            loop_ub_tmp = i + b_remainder;
            temp_re = Xx[loop_ub_tmp].re;
            temp_im = Xx[loop_ub_tmp].im;
            Xx[loop_ub_tmp].re = Xx[i].re - temp_re;
            Xx[loop_ub_tmp].im = Xx[i].im - temp_im;
            Xx[i].re = Xx[i].re + temp_re;
            Xx[i].im = Xx[i].im + temp_im;
          }
          istart = 1;
          for (int j{k}; j < nRowsD2; j += k) {
            twid_re = costab[j];
            twid_im = sintab[j];
            i = istart;
            ihi = istart + nFullPasses;
            while (i < ihi) {
              loop_ub_tmp = i + b_remainder;
              temp_re_tmp = Xx[loop_ub_tmp].im;
              temp_im = Xx[loop_ub_tmp].re;
              temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
              temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
              Xx[loop_ub_tmp].re = Xx[i].re - temp_re;
              Xx[loop_ub_tmp].im = Xx[i].im - temp_im;
              Xx[i].re = Xx[i].re + temp_re;
              Xx[i].im = Xx[i].im + temp_im;
              i += offset;
            }
            istart++;
          }
          k /= 2;
          b_remainder = offset;
          offset += offset;
          nFullPasses -= b_remainder;
        }
      }
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xw, nFullPasses, static_cast<int>(nfft), costab, sintab, sintabinv,
          Xx);
    }
  }
  if (std::isnan(varargin_1)) {
    temp_im = 6.2831853071795862;
  } else {
    temp_im = varargin_1;
  }
  temp_re = temp_im / nfft;
  if (nfft - 1.0 < 0.0) {
    costab1q.set_size(costab1q.size(0), 0);
  } else {
    costab1q.set_size(1, static_cast<int>(nfft - 1.0) + 1);
    offset = static_cast<int>(nfft - 1.0);
    for (istart = 0; istart <= offset; istart++) {
      costab1q[istart] = istart;
    }
  }
  costab1q.set_size(1, costab1q.size(1));
  offset = costab1q.size(1) - 1;
  for (istart = 0; istart <= offset; istart++) {
    costab1q[istart] = temp_re * costab1q[istart];
  }
  twid_re = temp_im / 2.0;
  twid_im = temp_re / 2.0;
  if (rt_remd_snf(nfft, 2.0) != 0.0) {
    temp_re_tmp = (nfft + 1.0) / 2.0;
    costab1q[static_cast<int>(temp_re_tmp) - 1] = twid_re - twid_im;
    costab1q[static_cast<int>(static_cast<unsigned int>(temp_re_tmp))] =
        twid_re + twid_im;
  } else {
    costab1q[static_cast<int>(nfft / 2.0 + 1.0) - 1] = twid_re;
  }
  costab1q[static_cast<int>(nfft) - 1] = temp_im - temp_re;
  f.set_size(costab1q.size(1));
  offset = costab1q.size(1);
  for (istart = 0; istart < offset; istart++) {
    f[istart] = costab1q[istart];
  }
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
