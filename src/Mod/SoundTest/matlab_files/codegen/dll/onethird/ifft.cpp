//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "onethird_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
void ifft(const ::coder::array<creal_T, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> wwc;
  array<creal_T, 1U> yCol;
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  int N2blue;
  int nd2;
  int nfft;
  nfft = x.size(1);
  if (x.size(1) == 0) {
    y.set_size(1, 0);
  } else {
    double nt_im;
    int i;
    int nInt2;
    int rt;
    boolean_T useRadix2;
    useRadix2 = ((x.size(1) & (x.size(1) - 1)) == 0);
    internal::FFTImplementationCallback::get_algo_sizes(x.size(1), useRadix2,
                                                        &N2blue, &nd2);
    nt_im = 6.2831853071795862 / static_cast<double>(nd2);
    nInt2 = nd2 / 2 / 2;
    costab1q.set_size(1, nInt2 + 1);
    costab1q[0] = 1.0;
    nd2 = nInt2 / 2 - 1;
    for (int k{0}; k <= nd2; k++) {
      costab1q[k + 1] = std::cos(nt_im * (static_cast<double>(k) + 1.0));
    }
    i = nd2 + 2;
    rt = nInt2 - 1;
    for (int k{i}; k <= rt; k++) {
      costab1q[k] = std::sin(nt_im * static_cast<double>(nInt2 - k));
    }
    costab1q[nInt2] = 0.0;
    if (!useRadix2) {
      nInt2 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nd2 + 1);
      for (int k{0}; k < nInt2; k++) {
        sintabinv[k + 1] = costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        sintabinv[k] = costab1q[k - nInt2];
      }
      for (int k{0}; k < nInt2; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - nInt2];
      }
    } else {
      nInt2 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (int k{0}; k < nInt2; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = costab1q[k - nInt2];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      nd2 = x.size(1);
      wwc = x.reshape(nd2);
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          wwc, x.size(1), costab, sintab, yCol);
      if (yCol.size(0) > 1) {
        nt_im = 1.0 / static_cast<double>(yCol.size(0));
        nd2 = yCol.size(0);
        for (i = 0; i < nd2; i++) {
          yCol[i].re = nt_im * yCol[i].re;
          yCol[i].im = nt_im * yCol[i].im;
        }
      }
    } else {
      double b_re_tmp;
      double c_re_tmp;
      double nt_re;
      double re_tmp;
      nd2 = (x.size(1) + x.size(1)) - 1;
      wwc.set_size(nd2);
      rt = 0;
      wwc[x.size(1) - 1].re = 1.0;
      wwc[x.size(1) - 1].im = 0.0;
      nInt2 = x.size(1) << 1;
      i = x.size(1);
      for (int k{0}; k <= i - 2; k++) {
        int b_y;
        b_y = ((k + 1) << 1) - 1;
        if (nInt2 - rt <= b_y) {
          rt += b_y - nInt2;
        } else {
          rt += b_y;
        }
        nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                static_cast<double>(nfft);
        if (nt_im == 0.0) {
          nt_re = 1.0;
          nt_im = 0.0;
        } else {
          nt_re = std::cos(nt_im);
          nt_im = std::sin(nt_im);
        }
        wwc[(x.size(1) - k) - 2].re = nt_re;
        wwc[(x.size(1) - k) - 2].im = -nt_im;
      }
      i = nd2 - 1;
      for (int k{i}; k >= nfft; k--) {
        wwc[k] = wwc[(nd2 - k) - 1];
      }
      yCol.set_size(x.size(1));
      nd2 = x.size(1);
      for (int k{0}; k < nd2; k++) {
        nt_re = wwc[(nfft + k) - 1].re;
        nt_im = wwc[(nfft + k) - 1].im;
        re_tmp = x[k].im;
        b_re_tmp = x[k].re;
        yCol[k].re = nt_re * b_re_tmp + nt_im * re_tmp;
        yCol[k].im = nt_re * re_tmp - nt_im * b_re_tmp;
      }
      i = x.size(1) + 1;
      for (int k{i}; k <= nfft; k++) {
        yCol[k - 1].re = 0.0;
        yCol[k - 1].im = 0.0;
      }
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          yCol, N2blue, costab, sintab, fv);
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          wwc, N2blue, costab, sintab, b_fv);
      b_fv.set_size(fv.size(0));
      nd2 = fv.size(0);
      for (i = 0; i < nd2; i++) {
        nt_im = fv[i].re;
        re_tmp = b_fv[i].im;
        b_re_tmp = fv[i].im;
        c_re_tmp = b_fv[i].re;
        b_fv[i].re = nt_im * c_re_tmp - b_re_tmp * re_tmp;
        b_fv[i].im = nt_im * re_tmp + b_re_tmp * c_re_tmp;
      }
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          b_fv, N2blue, costab, sintabinv, fv);
      if (fv.size(0) > 1) {
        nt_im = 1.0 / static_cast<double>(fv.size(0));
        nd2 = fv.size(0);
        for (i = 0; i < nd2; i++) {
          fv[i].re = nt_im * fv[i].re;
          fv[i].im = nt_im * fv[i].im;
        }
      }
      nt_re = x.size(1);
      i = x.size(1);
      rt = wwc.size(0);
      for (int k{i}; k <= rt; k++) {
        double ar;
        nt_im = wwc[k - 1].re;
        re_tmp = fv[k - 1].im;
        b_re_tmp = wwc[k - 1].im;
        c_re_tmp = fv[k - 1].re;
        ar = nt_im * c_re_tmp + b_re_tmp * re_tmp;
        nt_im = nt_im * re_tmp - b_re_tmp * c_re_tmp;
        if (nt_im == 0.0) {
          nd2 = k - i;
          yCol[nd2].re = ar / nt_re;
          yCol[nd2].im = 0.0;
        } else if (ar == 0.0) {
          nd2 = k - i;
          yCol[nd2].re = 0.0;
          yCol[nd2].im = nt_im / nt_re;
        } else {
          nd2 = k - i;
          yCol[nd2].re = ar / nt_re;
          yCol[nd2].im = nt_im / nt_re;
        }
      }
    }
    y.set_size(1, x.size(1));
    nd2 = x.size(1);
    for (i = 0; i < nd2; i++) {
      y[i] = yCol[i];
    }
  }
}

} // namespace coder

//
// File trailer for ifft.cpp
//
// [EOF]
//
