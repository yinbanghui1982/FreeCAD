//
// File: daopu_analysis.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Dec-2023 13:53:49
//

// Include Files
#include "daopu_analysis.h"
#include "FFTImplementationCallback.h"
#include "ifft.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else if (!std::isnan(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

//
// nn=1:nfft/2;
//  ff=(nn-1)*fs/nfft;               % 计算频率刻度
//
// Arguments    : const coder::array<double, 2U> &y
//                coder::array<creal_T, 2U> &z
// Return Type  : void
//
void daopu_analysis(const coder::array<double, 2U> &y,
                    coder::array<creal_T, 2U> &z)
{
  coder::array<creal_T, 2U> b_y;
  coder::array<creal_T, 1U> b_fv;
  coder::array<creal_T, 1U> fv;
  coder::array<creal_T, 1U> wwc;
  coder::array<creal_T, 1U> yCol;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 1U> d_y;
  int N2blue;
  int nd2;
  int nfft;
  nfft = y.size(1);
  if (y.size(1) == 0) {
    b_y.set_size(1, 0);
  } else {
    double nt_re;
    int i;
    int nInt2m1;
    int rt;
    boolean_T useRadix2;
    useRadix2 = ((y.size(1) & (y.size(1) - 1)) == 0);
    coder::internal::FFTImplementationCallback::get_algo_sizes(
        y.size(1), useRadix2, &N2blue, &nd2);
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
        sintab[k + 1] = -costab1q[(rt - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - rt];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      int c_y;
      c_y = y.size(1);
      d_y = y.reshape(c_y);
      nd2 = y.size(1);
      yCol.set_size(nd2);
      if (nd2 > d_y.size(0)) {
        yCol.set_size(nd2);
        for (i = 0; i < nd2; i++) {
          yCol[i].re = 0.0;
          yCol[i].im = 0.0;
        }
      }
      if (nd2 != 1) {
        coder::internal::FFTImplementationCallback::doHalfLengthRadix2(
            d_y, yCol, nd2, costab, sintab);
      } else {
        nd2 = d_y.size(0);
        if (nd2 > 1) {
          nd2 = 1;
        }
        yCol[0].re = d_y[nd2 - 1];
        yCol[0].im = 0.0;
      }
    } else {
      double nt_im;
      int c_y;
      if ((y.size(1) != 1) && ((y.size(1) & 1) == 0)) {
        int nInt2;
        nd2 = y.size(1) / 2;
        nInt2m1 = (nd2 + nd2) - 1;
        wwc.set_size(nInt2m1);
        rt = 0;
        wwc[nd2 - 1].re = 1.0;
        wwc[nd2 - 1].im = 0.0;
        nInt2 = nd2 << 1;
        for (int k{0}; k <= nd2 - 2; k++) {
          c_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= c_y) {
            rt += c_y - nInt2;
          } else {
            rt += c_y;
          }
          nt_im = -3.1415926535897931 * static_cast<double>(rt) /
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
        nInt2m1 = (y.size(1) + y.size(1)) - 1;
        wwc.set_size(nInt2m1);
        rt = 0;
        wwc[y.size(1) - 1].re = 1.0;
        wwc[y.size(1) - 1].im = 0.0;
        nInt2 = y.size(1) << 1;
        i = y.size(1);
        for (int k{0}; k <= i - 2; k++) {
          c_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= c_y) {
            rt += c_y - nInt2;
          } else {
            rt += c_y;
          }
          nt_im = -3.1415926535897931 * static_cast<double>(rt) /
                  static_cast<double>(nfft);
          if (nt_im == 0.0) {
            nt_re = 1.0;
            nt_im = 0.0;
          } else {
            nt_re = std::cos(nt_im);
            nt_im = std::sin(nt_im);
          }
          wwc[(y.size(1) - k) - 2].re = nt_re;
          wwc[(y.size(1) - k) - 2].im = -nt_im;
        }
        i = nInt2m1 - 1;
        for (int k{i}; k >= nfft; k--) {
          wwc[k] = wwc[(nInt2m1 - k) - 1];
        }
      }
      yCol.set_size(y.size(1));
      if ((N2blue != 1) && ((y.size(1) & 1) == 0)) {
        c_y = y.size(1);
        d_y = y.reshape(c_y);
        coder::internal::FFTImplementationCallback::doHalfLengthBluestein(
            d_y, yCol, y.size(1), y.size(1), N2blue, wwc, costab, sintab,
            costab, sintabinv);
      } else {
        double b_re_tmp;
        double re_tmp;
        nd2 = y.size(1);
        for (int k{0}; k < nd2; k++) {
          nt_re = y[k];
          yCol[k].re = wwc[(nfft + k) - 1].re * nt_re;
          yCol[k].im = wwc[(nfft + k) - 1].im * -nt_re;
        }
        i = y.size(1) + 1;
        for (int k{i}; k <= nfft; k++) {
          yCol[k - 1].re = 0.0;
          yCol[k - 1].im = 0.0;
        }
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            yCol, N2blue, costab, sintab, fv);
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
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
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            b_fv, N2blue, costab, sintabinv, fv);
        if (fv.size(0) > 1) {
          nt_re = 1.0 / static_cast<double>(fv.size(0));
          nd2 = fv.size(0);
          for (i = 0; i < nd2; i++) {
            fv[i].re = nt_re * fv[i].re;
            fv[i].im = nt_re * fv[i].im;
          }
        }
        i = y.size(1);
        nInt2m1 = wwc.size(0);
        for (int k{i}; k <= nInt2m1; k++) {
          nt_re = wwc[k - 1].re;
          nt_im = fv[k - 1].im;
          re_tmp = wwc[k - 1].im;
          b_re_tmp = fv[k - 1].re;
          nd2 = k - i;
          yCol[nd2].re = nt_re * b_re_tmp + re_tmp * nt_im;
          yCol[nd2].im = nt_re * nt_im - re_tmp * b_re_tmp;
        }
      }
    }
    b_y.set_size(1, y.size(1));
    nd2 = y.size(1);
    for (i = 0; i < nd2; i++) {
      b_y[i] = yCol[i];
    }
  }
  nd2 = b_y.size(1);
  costab1q.set_size(1, b_y.size(1));
  for (int k{0}; k < nd2; k++) {
    costab1q[k] = rt_hypotd_snf(b_y[k].re, b_y[k].im);
  }
  nd2 = costab1q.size(1);
  for (int k{0}; k < nd2; k++) {
    costab1q[k] = std::log(costab1q[k]);
  }
  //  按式(3-1-8)取实数部分
  //  subplot 211; plot(ff,Y(nn),'k'); hold on;     % 画出信号的频谱图
  coder::ifft(costab1q, z);
  //  按式(3-1-8)求取倒谱
}

//
// File trailer for daopu_analysis.cpp
//
// [EOF]
//
