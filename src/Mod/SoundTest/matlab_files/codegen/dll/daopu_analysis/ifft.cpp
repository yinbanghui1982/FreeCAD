//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:57:41
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "daopu_analysis_data.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> wwc;
  array<creal_T, 1U> yCol;
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 1U> b_x;
  int N2blue;
  int nd2;
  int nfft;
  nfft = x.size(1);
  if (x.size(1) == 0) {
    y.set_size(1, 0);
  } else {
    double nt_re;
    int i;
    int nInt2m1;
    int rt;
    boolean_T useRadix2;
    useRadix2 = ((x.size(1) & (x.size(1) - 1)) == 0);
    internal::FFTImplementationCallback::get_algo_sizes(x.size(1), useRadix2,
                                                        &N2blue, &nd2);
    nt_re = 6.2831853071795862 / static_cast<double>(nd2);
    rt = nd2 / 2 / 2;
    costab1q.set_size(1, rt + 1);
    costab1q[0] = 1.0;
    nd2 = rt / 2 - 1;
    for (int k{0}; k <= nd2; k++) {
      costab1q[k + 1] = std::cos(nt_re * (static_cast<double>(k) + 1.0));
    }
    i = nd2 + 2;
    nInt2m1 = rt - 1;
    for (int k{i}; k <= nInt2m1; k++) {
      costab1q[k] = std::sin(nt_re * static_cast<double>(rt - k));
    }
    costab1q[rt] = 0.0;
    if (!useRadix2) {
      rt = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nd2 + 1);
      for (int k{0}; k < rt; k++) {
        sintabinv[k + 1] = costab1q[(rt - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        sintabinv[k] = costab1q[k - rt];
      }
      for (int k{0}; k < rt; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(rt - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - rt];
      }
    } else {
      rt = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (int k{0}; k < rt; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = costab1q[(rt - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = costab1q[k - rt];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      nd2 = x.size(1);
      b_x = x.reshape(nd2);
      nd2 = x.size(1);
      yCol.set_size(nd2);
      if (nd2 > b_x.size(0)) {
        yCol.set_size(nd2);
        for (i = 0; i < nd2; i++) {
          yCol[i].re = 0.0;
          yCol[i].im = 0.0;
        }
      }
      if (nd2 != 1) {
        internal::FFTImplementationCallback::doHalfLengthRadix2(b_x, yCol, nd2,
                                                                costab, sintab);
      } else {
        nd2 = b_x.size(0);
        if (nd2 > 1) {
          nd2 = 1;
        }
        yCol[0].re = b_x[nd2 - 1];
        yCol[0].im = 0.0;
      }
      if (yCol.size(0) > 1) {
        nt_re = 1.0 / static_cast<double>(yCol.size(0));
        nd2 = yCol.size(0);
        for (i = 0; i < nd2; i++) {
          yCol[i].re = nt_re * yCol[i].re;
          yCol[i].im = nt_re * yCol[i].im;
        }
      }
    } else {
      double nt_im;
      if ((x.size(1) != 1) && ((x.size(1) & 1) == 0)) {
        int nInt2;
        nd2 = x.size(1) / 2;
        nInt2m1 = (nd2 + nd2) - 1;
        wwc.set_size(nInt2m1);
        rt = 0;
        wwc[nd2 - 1].re = 1.0;
        wwc[nd2 - 1].im = 0.0;
        nInt2 = nd2 << 1;
        for (int k{0}; k <= nd2 - 2; k++) {
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }
          nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                  static_cast<double>(nd2);
          if (nt_im == 0.0) {
            nt_re = 1.0;
            nt_im = 0.0;
          } else {
            nt_re = std::cos(nt_im);
            nt_im = std::sin(nt_im);
          }
          i = (nd2 - k) - 2;
          wwc[i].re = nt_re;
          wwc[i].im = -nt_im;
        }
        i = nInt2m1 - 1;
        for (int k{i}; k >= nd2; k--) {
          wwc[k] = wwc[(nInt2m1 - k) - 1];
        }
      } else {
        int nInt2;
        nInt2m1 = (x.size(1) + x.size(1)) - 1;
        wwc.set_size(nInt2m1);
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
        i = nInt2m1 - 1;
        for (int k{i}; k >= nfft; k--) {
          wwc[k] = wwc[(nInt2m1 - k) - 1];
        }
      }
      yCol.set_size(x.size(1));
      if ((N2blue != 1) && ((x.size(1) & 1) == 0)) {
        nd2 = x.size(1);
        b_x = x.reshape(nd2);
        internal::FFTImplementationCallback::b_doHalfLengthBluestein(
            b_x, yCol, x.size(1), x.size(1), N2blue, wwc, costab, sintab,
            costab, sintabinv);
      } else {
        double b_re_tmp;
        double re_tmp;
        nd2 = x.size(1);
        for (int k{0}; k < nd2; k++) {
          nt_re = x[k];
          yCol[k].re = wwc[(nfft + k) - 1].re * nt_re;
          yCol[k].im = wwc[(nfft + k) - 1].im * -nt_re;
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
          nt_re = fv[i].re;
          nt_im = b_fv[i].im;
          re_tmp = fv[i].im;
          b_re_tmp = b_fv[i].re;
          b_fv[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
          b_fv[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
        }
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            b_fv, N2blue, costab, sintabinv, fv);
        if (fv.size(0) > 1) {
          nt_re = 1.0 / static_cast<double>(fv.size(0));
          nd2 = fv.size(0);
          for (i = 0; i < nd2; i++) {
            fv[i].re = nt_re * fv[i].re;
            fv[i].im = nt_re * fv[i].im;
          }
        }
        i = x.size(1);
        nInt2m1 = wwc.size(0);
        for (int k{i}; k <= nInt2m1; k++) {
          double ar;
          nt_re = wwc[k - 1].re;
          nt_im = fv[k - 1].im;
          re_tmp = wwc[k - 1].im;
          b_re_tmp = fv[k - 1].re;
          ar = nt_re * b_re_tmp + re_tmp * nt_im;
          nt_re = nt_re * nt_im - re_tmp * b_re_tmp;
          if (nt_re == 0.0) {
            nd2 = k - i;
            yCol[nd2].re = ar / static_cast<double>(nfft);
            yCol[nd2].im = 0.0;
          } else if (ar == 0.0) {
            nd2 = k - i;
            yCol[nd2].re = 0.0;
            yCol[nd2].im = nt_re / static_cast<double>(nfft);
          } else {
            nd2 = k - i;
            yCol[nd2].re = ar / static_cast<double>(nfft);
            yCol[nd2].im = nt_re / static_cast<double>(nfft);
          }
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
