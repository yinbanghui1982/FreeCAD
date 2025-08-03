//
// File: onethird.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
//

// Include Files
#include "onethird.h"
#include "fft.h"
#include "ifft.h"
#include "onethird_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
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
// 傅里叶变换
//
// Arguments    : const coder::array<double, 2U> &t
//                const coder::array<double, 1U> &x
//                coder::array<double, 1U> &Ya_1
//                double Ya_2[30]
//                coder::array<double, 2U> &f
//                double fc[30]
//                double *nfft
//                double *nc
// Return Type  : void
//
void onethird(const coder::array<double, 2U> &t,
              const coder::array<double, 1U> &x, coder::array<double, 1U> &Ya_1,
              double Ya_2[30], coder::array<double, 2U> &f, double fc[30],
              double *nfft, double *nc)
{
  static const double dv[30]{20.0,   25.0,   31.5,   40.0,    50.0,    63.0,
                             80.0,   100.0,  125.0,  160.0,   200.0,   250.0,
                             315.0,  400.0,  500.0,  630.0,   800.0,   1000.0,
                             1250.0, 1600.0, 2000.0, 2500.0,  3150.0,  4000.0,
                             5000.0, 6300.0, 8000.0, 10000.0, 12500.0, 16000.0};
  static const short iv[30]{22,   28,   35,   45,    56,    71,   90,   112,
                            140,  180,  224,  281,   354,   449,  561,  707,
                            898,  1122, 1403, 1796,  2245,  2806, 3536, 4490,
                            5612, 7072, 8980, 11225, 14031, 17959};
  static const short y[30]{36,   44,    56,    72,    90,    112,  142,  178,
                           222,  286,   356,   446,   562,   712,  890,  1122,
                           1426, 1782,  2228,  2850,  3564,  4454, 5612, 7128,
                           8908, 11226, 14254, 17818, 22272, 28508};
  coder::array<creal_T, 2U> cc;
  coder::array<creal_T, 2U> nn;
  coder::array<creal_T, 1U> Y;
  coder::array<creal_T, 1U> Y1;
  coder::array<double, 2U> f1;
  double fu[30];
  double nl[30];
  double b;
  double b_b;
  double bsum;
  double fs;
  double xbar;
  int b_nfft;
  int hi;
  int loop_ub;
  int nblocks;
  int nx;
  std::copy(&dv[0], &dv[30], &fc[0]);
  b_nfft = t.size(1);
  fs = 1.0 / (t[1] - t[0]);
  coder::fft(x, static_cast<double>(t.size(1)), Y1);
  //  傅里叶变换
  if (t.size(1) - 1 < 0) {
    f1.set_size(f1.size(0), 0);
  } else {
    f1.set_size(1, t.size(1));
    loop_ub = t.size(1) - 1;
    for (nblocks = 0; nblocks <= loop_ub; nblocks++) {
      f1[nblocks] = nblocks;
    }
  }
  f1.set_size(1, f1.size(1));
  loop_ub = f1.size(1) - 1;
  for (nblocks = 0; nblocks <= loop_ub; nblocks++) {
    f1[nblocks] = f1[nblocks] / (static_cast<double>(t.size(1)) - 1.0) * fs;
  }
  //  频率向量
  bsum = static_cast<double>(t.size(1)) / 2.0;
  if (bsum < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(bsum);
  }
  f.set_size(1, loop_ub);
  for (nblocks = 0; nblocks < loop_ub; nblocks++) {
    f[nblocks] = f1[nblocks];
  }
  //  根据对称性取半
  bsum = static_cast<double>(t.size(1)) / 2.0;
  if (bsum < 1.0) {
    hi = 0;
  } else {
    hi = static_cast<int>(bsum);
  }
  nx = t.size(1);
  Y.set_size(hi);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    bsum = Y1[nblocks].re * 2.0;
    xbar = Y1[nblocks].im * 2.0;
    if (xbar == 0.0) {
      Y[nblocks].re = bsum / static_cast<double>(nx);
      Y[nblocks].im = 0.0;
    } else if (bsum == 0.0) {
      Y[nblocks].re = 0.0;
      Y[nblocks].im = xbar / static_cast<double>(nx);
    } else {
      Y[nblocks].re = bsum / static_cast<double>(nx);
      Y[nblocks].im = xbar / static_cast<double>(nx);
    }
  }
  //  根据对称性取半
  nx = Y.size(0);
  Ya_1.set_size(Y.size(0));
  for (int k{0}; k < nx; k++) {
    Ya_1[k] = rt_hypotd_snf(Y[k].re, Y[k].im);
  }
  //  频域中的能量
  //  声压级基底
  //  计算频谱声压级
  hi = Ya_1.size(0);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    Ya_1[nblocks] = Ya_1[nblocks] / 1.9999999999999998E-5;
  }
  nx = Ya_1.size(0);
  for (int k{0}; k < nx; k++) {
    Ya_1[k] = std::log10(Ya_1[k]);
  }
  hi = Ya_1.size(0);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    Ya_1[nblocks] = 20.0 * Ya_1[nblocks];
  }
  //  计算频谱声压级
  //  计算总声压级
  //  找出10-8k
  //  三分之一倍频程
  //  定义三分之一倍频程的中心频率fc
  //  下限频率
  //  上限频率
  for (nblocks = 0; nblocks < 30; nblocks++) {
    fu[nblocks] = iv[nblocks];
  }
  fu[29] = f1[loop_ub - 1];
  //  修复fu，末尾变为16000
  //
  //  频率向量f中有L/2个数据，对应的频率是(0：L/2-1)/(L/2-1)*fs/2;
  b = static_cast<double>(t.size(1)) / 2.0 - 1.0;
  //  下限频率对应的频率向量的序号
  b_b = static_cast<double>(t.size(1)) / 2.0 - 1.0;
  //  上限频率对应的频率向量的序号
  //  中心频率的长度
  if (t.size(1) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = t.size(1);
  }
  for (int i{0}; i < 30; i++) {
    double b_y;
    double d;
    int n;
    nl[i] = std::round(static_cast<double>(y[i]) / fs * b + 1.0);
    fu[i] = std::round(fu[i] * 2.0 / fs * b_b + 1.0);
    nn.set_size(1, b_nfft);
    for (nblocks = 0; nblocks < b_nfft; nblocks++) {
      nn[nblocks].re = 0.0;
      nn[nblocks].im = 0.0;
    }
    bsum = nl[i];
    xbar = fu[i];
    if (bsum > xbar) {
      nblocks = 0;
      n = 0;
      nx = 1;
    } else {
      nblocks = static_cast<int>(bsum) - 1;
      n = static_cast<int>(xbar);
      nx = static_cast<int>(bsum);
    }
    hi = n - nblocks;
    for (n = 0; n < hi; n++) {
      nn[(nx + n) - 1] = Y1[nblocks + n];
    }
    bsum = fu[i];
    xbar = (static_cast<double>(Y1.size(0)) - bsum) + 1.0;
    b_y = nl[i];
    d = (static_cast<double>(Y1.size(0)) - b_y) + 1.0;
    if (xbar > d) {
      nblocks = 0;
      n = 0;
    } else {
      nblocks = static_cast<int>(xbar) - 1;
      n = static_cast<int>(d);
    }
    bsum = (static_cast<double>(nn.size(1)) - bsum) + 1.0;
    if (bsum > (static_cast<double>(nn.size(1)) - b_y) + 1.0) {
      nx = 1;
    } else {
      nx = static_cast<int>(bsum);
    }
    hi = n - nblocks;
    for (n = 0; n < hi; n++) {
      nn[(nx + n) - 1] = Y1[nblocks + n];
    }
    coder::ifft(nn, cc);
    f1.set_size(1, loop_ub);
    for (nblocks = 0; nblocks < loop_ub; nblocks++) {
      f1[nblocks] = cc[nblocks].re;
    }
    n = f1.size(1);
    if (f1.size(1) == 0) {
      bsum = rtNaN;
    } else if (f1.size(1) == 1) {
      if ((!std::isinf(f1[0])) && (!std::isnan(f1[0]))) {
        bsum = 0.0;
      } else {
        bsum = rtNaN;
      }
    } else {
      int lastBlockLength;
      if (f1.size(1) <= 1024) {
        nx = f1.size(1);
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        nx = 1024;
        nblocks = f1.size(1) / 1024;
        lastBlockLength = f1.size(1) - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      b_y = f1[0];
      for (int k{2}; k <= nx; k++) {
        b_y += f1[k - 1];
      }
      for (int ib{2}; ib <= nblocks; ib++) {
        nx = (ib - 1) << 10;
        bsum = f1[nx];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (int k{2}; k <= hi; k++) {
          bsum += f1[(nx + k) - 1];
        }
        b_y += bsum;
      }
      xbar = b_y / static_cast<double>(f1.size(1));
      b_y = 0.0;
      for (int k{0}; k < n; k++) {
        bsum = f1[k] - xbar;
        b_y += bsum * bsum;
      }
      bsum = b_y / (static_cast<double>(f1.size(1)) - 1.0);
    }
    Ya_2[i] = std::sqrt(bsum);
    //  求取1/3倍频程
    //      YE_C(i) = sqrt(sum(YE(nl(i):nu(i)).^2)/2);    %
    //      求取第i个中心频率的能量：频带的平均能量；
    Ya_2[i] = 20.0 * std::log10(Ya_2[i] / 1.9999999999999998E-5);
  }
  //  计算中心频率的声压级
  *nfft = b_nfft;
  *nc = 30.0;
}

//
// File trailer for onethird.cpp
//
// [EOF]
//
