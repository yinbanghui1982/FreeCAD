//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:57:41
//

// Include Files
#include "FFTImplementationCallback.h"
#include "daopu_analysis_data.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int nRows
//                ::coder::array<double, 2U> &costab
//                ::coder::array<double, 2U> &sintab
//                ::coder::array<double, 2U> &sintabinv
// Return Type  : void
//
namespace coder {
namespace internal {
void FFTImplementationCallback::generate_twiddle_tables(
    int nRows, ::coder::array<double, 2U> &costab,
    ::coder::array<double, 2U> &sintab, ::coder::array<double, 2U> &sintabinv)
{
  array<double, 2U> costab1q;
  double e;
  int i;
  int n;
  int nd2;
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  costab1q.set_size(1, n + 1);
  costab1q[0] = 1.0;
  nd2 = n / 2 - 1;
  for (int k{0}; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (int k{i}; k <= nd2; k++) {
    costab1q[k] = std::sin(e * static_cast<double>(n - k));
  }
  costab1q[n] = 0.0;
  n = costab1q.size(1) - 1;
  nd2 = (costab1q.size(1) - 1) << 1;
  costab.set_size(1, nd2 + 1);
  sintab.set_size(1, nd2 + 1);
  costab[0] = 1.0;
  sintab[0] = 0.0;
  sintabinv.set_size(1, nd2 + 1);
  for (int k{0}; k < n; k++) {
    sintabinv[k + 1] = costab1q[(n - k) - 1];
  }
  i = costab1q.size(1);
  for (int k{i}; k <= nd2; k++) {
    sintabinv[k] = costab1q[k - n];
  }
  for (int k{0}; k < n; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[(n - k) - 1];
  }
  i = costab1q.size(1);
  for (int k{i}; k <= nd2; k++) {
    costab[k] = -costab1q[nd2 - k];
    sintab[k] = -costab1q[k - n];
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                const ::coder::array<double, 2U> &costabinv
//                const ::coder::array<double, 2U> &sintabinv
//                ::coder::array<double, 2U> &hcostab
//                ::coder::array<double, 2U> &hsintab
//                ::coder::array<double, 2U> &hcostabinv
//                ::coder::array<double, 2U> &hsintabinv
// Return Type  : void
//
void FFTImplementationCallback::get_half_twiddle_tables(
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &costabinv,
    const ::coder::array<double, 2U> &sintabinv,
    ::coder::array<double, 2U> &hcostab, ::coder::array<double, 2U> &hsintab,
    ::coder::array<double, 2U> &hcostabinv,
    ::coder::array<double, 2U> &hsintabinv)
{
  int hszCostab;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  hcostabinv.set_size(1, hszCostab);
  hsintabinv.set_size(1, hszCostab);
  for (int i{0}; i < hszCostab; i++) {
    int hcostab_tmp;
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab[i] = costab[hcostab_tmp];
    hsintab[i] = sintab[hcostab_tmp];
    hcostabinv[i] = costabinv[hcostab_tmp];
    hsintabinv[i] = sintabinv[hcostab_tmp];
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
//                int nrowsx
//                int nRows
//                int nfft
//                const ::coder::array<creal_T, 1U> &wwc
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                const ::coder::array<double, 2U> &costabinv
//                const ::coder::array<double, 2U> &sintabinv
// Return Type  : void
//
void FFTImplementationCallback::b_doHalfLengthBluestein(
    const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y,
    int nrowsx, int nRows, int nfft, const ::coder::array<creal_T, 1U> &wwc,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &costabinv,
    const ::coder::array<double, 2U> &sintabinv)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> reconVar1;
  array<creal_T, 1U> reconVar2;
  array<creal_T, 1U> ytmp;
  array<double, 2U> a__1;
  array<double, 2U> costable;
  array<double, 2U> hcostabinv;
  array<double, 2U> hsintab;
  array<double, 2U> hsintabinv;
  array<double, 2U> sintable;
  array<int, 2U> wrapIndex;
  double a_im;
  double a_re;
  double b_im;
  double b_re;
  double z_tmp;
  int b_i;
  int b_re_tmp;
  int hnRows;
  int i;
  int u0;
  boolean_T nxeven;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (i = 0; i < hnRows; i++) {
      ytmp[i].re = 0.0;
      ytmp[i].im = 0.0;
    }
  }
  if ((x.size(0) & 1) == 0) {
    nxeven = true;
    u0 = x.size(0);
  } else if (x.size(0) >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x.size(0) - 1;
  }
  if (u0 > nRows) {
    u0 = nRows;
  }
  FFTImplementationCallback::generate_twiddle_tables(nRows << 1, costable,
                                                     sintable, a__1);
  FFTImplementationCallback::get_half_twiddle_tables(costab, sintab, costabinv,
                                                     sintabinv, a__1, hsintab,
                                                     hcostabinv, hsintabinv);
  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  wrapIndex.set_size(1, hnRows);
  for (b_i = 0; b_i < hnRows; b_i++) {
    i = b_i << 1;
    z_tmp = sintable[i];
    a_re = costable[i];
    reconVar1[b_i].re = 1.0 - z_tmp;
    reconVar1[b_i].im = -a_re;
    reconVar2[b_i].re = z_tmp + 1.0;
    reconVar2[b_i].im = a_re;
    if (b_i + 1 != 1) {
      wrapIndex[b_i] = (hnRows - b_i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }
  z_tmp = static_cast<double>(u0) / 2.0;
  i = static_cast<int>(z_tmp);
  for (int k1{0}; k1 < i; k1++) {
    b_i = (hnRows + k1) - 1;
    a_re = wwc[b_i].re;
    a_im = wwc[b_i].im;
    b_re_tmp = k1 << 1;
    b_re = x[b_re_tmp];
    b_im = x[b_re_tmp + 1];
    ytmp[k1].re = a_re * b_re + a_im * b_im;
    ytmp[k1].im = a_re * b_im - a_im * b_re;
  }
  if (!nxeven) {
    b_i = (hnRows + static_cast<int>(z_tmp)) - 1;
    a_re = wwc[b_i].re;
    a_im = wwc[b_i].im;
    b_re = x[static_cast<int>(z_tmp) << 1];
    ytmp[static_cast<int>(z_tmp)].re = a_re * b_re + a_im * 0.0;
    ytmp[static_cast<int>(z_tmp)].im = a_re * 0.0 - a_im * b_re;
    if (static_cast<int>(z_tmp) + 2 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
      for (b_i = i; b_i <= hnRows; b_i++) {
        ytmp[b_i - 1].re = 0.0;
        ytmp[b_i - 1].im = 0.0;
      }
    }
  } else if (static_cast<int>(z_tmp) + 1 <= hnRows) {
    i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
    for (b_i = i; b_i <= hnRows; b_i++) {
      ytmp[b_i - 1].re = 0.0;
      ytmp[b_i - 1].im = 0.0;
    }
  }
  b_i = static_cast<int>(static_cast<double>(nfft) / 2.0);
  FFTImplementationCallback::r2br_r2dit_trig_impl(ytmp, b_i, a__1, hsintab, fv);
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, b_i, a__1, hsintab,
                                                  b_fv);
  b_fv.set_size(fv.size(0));
  b_re_tmp = fv.size(0);
  for (i = 0; i < b_re_tmp; i++) {
    z_tmp = fv[i].re;
    a_re = b_fv[i].im;
    a_im = fv[i].im;
    b_re = b_fv[i].re;
    b_fv[i].re = z_tmp * b_re - a_im * a_re;
    b_fv[i].im = z_tmp * a_re + a_im * b_re;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(b_fv, b_i, hcostabinv,
                                                  hsintabinv, fv);
  if (fv.size(0) > 1) {
    z_tmp = 1.0 / static_cast<double>(fv.size(0));
    b_re_tmp = fv.size(0);
    for (i = 0; i < b_re_tmp; i++) {
      fv[i].re = z_tmp * fv[i].re;
      fv[i].im = z_tmp * fv[i].im;
    }
  }
  i = wwc.size(0);
  for (b_re_tmp = hnRows; b_re_tmp <= i; b_re_tmp++) {
    z_tmp = wwc[b_re_tmp - 1].re;
    a_re = fv[b_re_tmp - 1].im;
    a_im = wwc[b_re_tmp - 1].im;
    b_re = fv[b_re_tmp - 1].re;
    b_im = z_tmp * b_re + a_im * a_re;
    z_tmp = z_tmp * a_re - a_im * b_re;
    if (z_tmp == 0.0) {
      b_i = b_re_tmp - hnRows;
      ytmp[b_i].re = b_im / static_cast<double>(hnRows);
      ytmp[b_i].im = 0.0;
    } else if (b_im == 0.0) {
      b_i = b_re_tmp - hnRows;
      ytmp[b_i].re = 0.0;
      ytmp[b_i].im = z_tmp / static_cast<double>(hnRows);
    } else {
      b_i = b_re_tmp - hnRows;
      ytmp[b_i].re = b_im / static_cast<double>(hnRows);
      ytmp[b_i].im = z_tmp / static_cast<double>(hnRows);
    }
  }
  for (b_i = 0; b_i < hnRows; b_i++) {
    double b_ytmp_re_tmp;
    double ytmp_im_tmp;
    double ytmp_re_tmp;
    i = wrapIndex[b_i];
    z_tmp = ytmp[b_i].re;
    a_re = reconVar1[b_i].im;
    a_im = ytmp[b_i].im;
    b_re = reconVar1[b_i].re;
    b_im = ytmp[i - 1].re;
    ytmp_im_tmp = -ytmp[i - 1].im;
    ytmp_re_tmp = reconVar2[b_i].im;
    b_ytmp_re_tmp = reconVar2[b_i].re;
    y[b_i].re = 0.5 * ((z_tmp * b_re - a_im * a_re) +
                       (b_im * b_ytmp_re_tmp - ytmp_im_tmp * ytmp_re_tmp));
    y[b_i].im = 0.5 * ((z_tmp * a_re + a_im * b_re) +
                       (b_im * ytmp_re_tmp + ytmp_im_tmp * b_ytmp_re_tmp));
    i = hnRows + b_i;
    y[i].re = 0.5 * ((z_tmp * b_ytmp_re_tmp - a_im * ytmp_re_tmp) +
                     (b_im * b_re - ytmp_im_tmp * a_re));
    y[i].im = 0.5 * ((z_tmp * ytmp_re_tmp + a_im * b_ytmp_re_tmp) +
                     (b_im * a_re + ytmp_im_tmp * b_re));
  }
  b_re_tmp = y.size(0);
  for (i = 0; i < b_re_tmp; i++) {
    b_im = y[i].re;
    z_tmp = y[i].im;
    if (z_tmp == 0.0) {
      a_re = b_im / 2.0;
      z_tmp = 0.0;
    } else if (b_im == 0.0) {
      a_re = 0.0;
      z_tmp /= 2.0;
    } else {
      a_re = b_im / 2.0;
      z_tmp /= 2.0;
    }
    y[i].re = a_re;
    y[i].im = z_tmp;
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
//                int nrowsx
//                int nRows
//                int nfft
//                const ::coder::array<creal_T, 1U> &wwc
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                const ::coder::array<double, 2U> &costabinv
//                const ::coder::array<double, 2U> &sintabinv
// Return Type  : void
//
void FFTImplementationCallback::doHalfLengthBluestein(
    const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y,
    int nrowsx, int nRows, int nfft, const ::coder::array<creal_T, 1U> &wwc,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &costabinv,
    const ::coder::array<double, 2U> &sintabinv)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> reconVar1;
  array<creal_T, 1U> reconVar2;
  array<creal_T, 1U> ytmp;
  array<double, 2U> a__1;
  array<double, 2U> costable;
  array<double, 2U> hcostabinv;
  array<double, 2U> hsintab;
  array<double, 2U> hsintabinv;
  array<double, 2U> sintable;
  array<int, 2U> wrapIndex;
  double a_im;
  double a_re;
  double b_im;
  double b_re;
  double z_tmp;
  int b_i;
  int b_re_tmp;
  int hnRows;
  int i;
  int u0;
  boolean_T nxeven;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (i = 0; i < hnRows; i++) {
      ytmp[i].re = 0.0;
      ytmp[i].im = 0.0;
    }
  }
  if ((x.size(0) & 1) == 0) {
    nxeven = true;
    u0 = x.size(0);
  } else if (x.size(0) >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x.size(0) - 1;
  }
  if (u0 > nRows) {
    u0 = nRows;
  }
  FFTImplementationCallback::generate_twiddle_tables(nRows << 1, costable,
                                                     sintable, a__1);
  FFTImplementationCallback::get_half_twiddle_tables(costab, sintab, costabinv,
                                                     sintabinv, a__1, hsintab,
                                                     hcostabinv, hsintabinv);
  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  wrapIndex.set_size(1, hnRows);
  for (b_i = 0; b_i < hnRows; b_i++) {
    i = b_i << 1;
    z_tmp = sintable[i];
    a_re = costable[i];
    reconVar1[b_i].re = z_tmp + 1.0;
    reconVar1[b_i].im = -a_re;
    reconVar2[b_i].re = 1.0 - z_tmp;
    reconVar2[b_i].im = a_re;
    if (b_i + 1 != 1) {
      wrapIndex[b_i] = (hnRows - b_i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }
  z_tmp = static_cast<double>(u0) / 2.0;
  i = static_cast<int>(z_tmp);
  for (int k1{0}; k1 < i; k1++) {
    b_i = (hnRows + k1) - 1;
    a_re = wwc[b_i].re;
    a_im = wwc[b_i].im;
    b_re_tmp = k1 << 1;
    b_re = x[b_re_tmp];
    b_im = x[b_re_tmp + 1];
    ytmp[k1].re = a_re * b_re + a_im * b_im;
    ytmp[k1].im = a_re * b_im - a_im * b_re;
  }
  if (!nxeven) {
    b_i = (hnRows + static_cast<int>(z_tmp)) - 1;
    a_re = wwc[b_i].re;
    a_im = wwc[b_i].im;
    b_re = x[static_cast<int>(z_tmp) << 1];
    ytmp[static_cast<int>(z_tmp)].re = a_re * b_re + a_im * 0.0;
    ytmp[static_cast<int>(z_tmp)].im = a_re * 0.0 - a_im * b_re;
    if (static_cast<int>(z_tmp) + 2 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
      for (b_i = i; b_i <= hnRows; b_i++) {
        ytmp[b_i - 1].re = 0.0;
        ytmp[b_i - 1].im = 0.0;
      }
    }
  } else if (static_cast<int>(z_tmp) + 1 <= hnRows) {
    i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
    for (b_i = i; b_i <= hnRows; b_i++) {
      ytmp[b_i - 1].re = 0.0;
      ytmp[b_i - 1].im = 0.0;
    }
  }
  b_i = static_cast<int>(static_cast<double>(nfft) / 2.0);
  FFTImplementationCallback::r2br_r2dit_trig_impl(ytmp, b_i, a__1, hsintab, fv);
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, b_i, a__1, hsintab,
                                                  b_fv);
  b_fv.set_size(fv.size(0));
  b_re_tmp = fv.size(0);
  for (i = 0; i < b_re_tmp; i++) {
    z_tmp = fv[i].re;
    a_re = b_fv[i].im;
    a_im = fv[i].im;
    b_re = b_fv[i].re;
    b_fv[i].re = z_tmp * b_re - a_im * a_re;
    b_fv[i].im = z_tmp * a_re + a_im * b_re;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(b_fv, b_i, hcostabinv,
                                                  hsintabinv, fv);
  if (fv.size(0) > 1) {
    z_tmp = 1.0 / static_cast<double>(fv.size(0));
    b_re_tmp = fv.size(0);
    for (i = 0; i < b_re_tmp; i++) {
      fv[i].re = z_tmp * fv[i].re;
      fv[i].im = z_tmp * fv[i].im;
    }
  }
  i = wwc.size(0);
  for (b_re_tmp = hnRows; b_re_tmp <= i; b_re_tmp++) {
    z_tmp = wwc[b_re_tmp - 1].re;
    a_re = fv[b_re_tmp - 1].im;
    a_im = wwc[b_re_tmp - 1].im;
    b_re = fv[b_re_tmp - 1].re;
    b_i = b_re_tmp - hnRows;
    ytmp[b_i].re = z_tmp * b_re + a_im * a_re;
    ytmp[b_i].im = z_tmp * a_re - a_im * b_re;
  }
  for (b_i = 0; b_i < hnRows; b_i++) {
    double b_ytmp_re_tmp;
    double ytmp_im_tmp;
    double ytmp_re_tmp;
    i = wrapIndex[b_i];
    z_tmp = ytmp[b_i].re;
    a_re = reconVar1[b_i].im;
    a_im = ytmp[b_i].im;
    b_re = reconVar1[b_i].re;
    b_im = ytmp[i - 1].re;
    ytmp_im_tmp = -ytmp[i - 1].im;
    ytmp_re_tmp = reconVar2[b_i].im;
    b_ytmp_re_tmp = reconVar2[b_i].re;
    y[b_i].re = 0.5 * ((z_tmp * b_re - a_im * a_re) +
                       (b_im * b_ytmp_re_tmp - ytmp_im_tmp * ytmp_re_tmp));
    y[b_i].im = 0.5 * ((z_tmp * a_re + a_im * b_re) +
                       (b_im * ytmp_re_tmp + ytmp_im_tmp * b_ytmp_re_tmp));
    i = hnRows + b_i;
    y[i].re = 0.5 * ((z_tmp * b_ytmp_re_tmp - a_im * ytmp_re_tmp) +
                     (b_im * b_re - ytmp_im_tmp * a_re));
    y[i].im = 0.5 * ((z_tmp * ytmp_re_tmp + a_im * b_ytmp_re_tmp) +
                     (b_im * a_re + ytmp_im_tmp * b_re));
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
//                int unsigned_nRows
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
// Return Type  : void
//
void FFTImplementationCallback::doHalfLengthRadix2(
    const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y,
    int unsigned_nRows, const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab)
{
  array<creal_T, 1U> reconVar1;
  array<creal_T, 1U> reconVar2;
  array<double, 2U> hcostab;
  array<double, 2U> hsintab;
  array<int, 2U> wrapIndex;
  array<int, 1U> bitrevIndex;
  double b_y_re_tmp;
  double c_y_re_tmp;
  double d_y_re_tmp;
  double temp2_im;
  double temp2_re;
  double temp_im;
  double temp_im_tmp;
  double temp_re;
  double temp_re_tmp;
  double y_re_tmp;
  double z_tmp;
  int hszCostab;
  int i;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  int nRows;
  int nRowsD2;
  int nRowsM2;
  boolean_T tst;
  nRows = unsigned_nRows / 2;
  j = y.size(0);
  if (j > nRows) {
    j = nRows;
  }
  nRowsM2 = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  for (i = 0; i < hszCostab; i++) {
    iy = ((i + 1) << 1) - 2;
    hcostab[i] = costab[iy];
    hsintab[i] = sintab[iy];
  }
  reconVar1.set_size(nRows);
  reconVar2.set_size(nRows);
  wrapIndex.set_size(1, nRows);
  for (i = 0; i < nRows; i++) {
    temp_re = sintab[i];
    temp2_re = costab[i];
    reconVar1[i].re = temp_re + 1.0;
    reconVar1[i].im = -temp2_re;
    reconVar2[i].re = 1.0 - temp_re;
    reconVar2[i].im = temp2_re;
    if (i + 1 != 1) {
      wrapIndex[i] = (nRows - i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }
  z_tmp = static_cast<double>(unsigned_nRows) / 2.0;
  ju = 0;
  iy = 1;
  hszCostab = static_cast<int>(z_tmp);
  bitrevIndex.set_size(hszCostab);
  for (istart = 0; istart < hszCostab; istart++) {
    bitrevIndex[istart] = 0;
  }
  for (istart = 0; istart <= j - 2; istart++) {
    bitrevIndex[istart] = iy;
    hszCostab = static_cast<int>(z_tmp);
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex[j - 1] = iy;
  if ((x.size(0) & 1) == 0) {
    tst = true;
    j = x.size(0);
  } else if (x.size(0) >= unsigned_nRows) {
    tst = true;
    j = unsigned_nRows;
  } else {
    tst = false;
    j = x.size(0) - 1;
  }
  if (j > unsigned_nRows) {
    j = unsigned_nRows;
  }
  temp_re = static_cast<double>(j) / 2.0;
  istart = static_cast<int>(temp_re);
  for (i = 0; i < istart; i++) {
    iy = i << 1;
    y[bitrevIndex[i] - 1].re = x[iy];
    y[bitrevIndex[i] - 1].im = x[iy + 1];
  }
  if (!tst) {
    istart = bitrevIndex[static_cast<int>(temp_re)] - 1;
    y[istart].re = x[static_cast<int>(temp_re) << 1];
    y[istart].im = 0.0;
  }
  if (nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im_tmp = y[i + 1].im;
      y[i + 1].re = y[i].re - temp_re_tmp;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re = y[i].re + temp_re_tmp;
      y[i].im = y[i].im + temp_im_tmp;
    }
  }
  hszCostab = 2;
  iy = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iy) {
      nRowsM2 = i + hszCostab;
      temp_re = y[nRowsM2].re;
      temp_im = y[nRowsM2].im;
      y[nRowsM2].re = y[i].re - temp_re;
      y[nRowsM2].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      temp2_re = hcostab[j];
      temp2_im = hsintab[j];
      i = istart;
      nRows = istart + ju;
      while (i < nRows) {
        nRowsM2 = i + hszCostab;
        temp_re_tmp = y[nRowsM2].im;
        y_re_tmp = y[nRowsM2].re;
        temp_re = temp2_re * y_re_tmp - temp2_im * temp_re_tmp;
        temp_im = temp2_re * temp_re_tmp + temp2_im * y_re_tmp;
        y[nRowsM2].re = y[i].re - temp_re;
        y[nRowsM2].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += iy;
      }
      istart++;
    }
    k /= 2;
    hszCostab = iy;
    iy += iy;
    ju -= hszCostab;
  }
  hszCostab = static_cast<int>(z_tmp) / 2;
  temp_re_tmp = y[0].re;
  temp_im_tmp = y[0].im;
  y[0].re =
      0.5 * ((temp_re_tmp * reconVar1[0].re - temp_im_tmp * reconVar1[0].im) +
             (temp_re_tmp * reconVar2[0].re - -temp_im_tmp * reconVar2[0].im));
  y[0].im =
      0.5 * ((temp_re_tmp * reconVar1[0].im + temp_im_tmp * reconVar1[0].re) +
             (temp_re_tmp * reconVar2[0].im + -temp_im_tmp * reconVar2[0].re));
  y[static_cast<int>(z_tmp)].re =
      0.5 * ((temp_re_tmp * reconVar2[0].re - temp_im_tmp * reconVar2[0].im) +
             (temp_re_tmp * reconVar1[0].re - -temp_im_tmp * reconVar1[0].im));
  y[static_cast<int>(z_tmp)].im =
      0.5 * ((temp_re_tmp * reconVar2[0].im + temp_im_tmp * reconVar2[0].re) +
             (temp_re_tmp * reconVar1[0].im + -temp_im_tmp * reconVar1[0].re));
  for (i = 2; i <= hszCostab; i++) {
    double temp2_im_tmp;
    temp_re_tmp = y[i - 1].re;
    temp_im_tmp = y[i - 1].im;
    istart = wrapIndex[i - 1];
    temp2_im = y[istart - 1].re;
    temp2_im_tmp = y[istart - 1].im;
    y_re_tmp = reconVar1[i - 1].im;
    b_y_re_tmp = reconVar1[i - 1].re;
    c_y_re_tmp = reconVar2[i - 1].im;
    d_y_re_tmp = reconVar2[i - 1].re;
    y[i - 1].re = 0.5 * ((temp_re_tmp * b_y_re_tmp - temp_im_tmp * y_re_tmp) +
                         (temp2_im * d_y_re_tmp - -temp2_im_tmp * c_y_re_tmp));
    y[i - 1].im = 0.5 * ((temp_re_tmp * y_re_tmp + temp_im_tmp * b_y_re_tmp) +
                         (temp2_im * c_y_re_tmp + -temp2_im_tmp * d_y_re_tmp));
    iy = (static_cast<int>(z_tmp) + i) - 1;
    y[iy].re = 0.5 * ((temp_re_tmp * d_y_re_tmp - temp_im_tmp * c_y_re_tmp) +
                      (temp2_im * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y[iy].im = 0.5 * ((temp_re_tmp * c_y_re_tmp + temp_im_tmp * d_y_re_tmp) +
                      (temp2_im * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    temp_im = reconVar1[istart - 1].im;
    temp_re = reconVar1[istart - 1].re;
    y_re_tmp = reconVar2[istart - 1].im;
    temp2_re = reconVar2[istart - 1].re;
    y[istart - 1].re =
        0.5 * ((temp2_im * temp_re - temp2_im_tmp * temp_im) +
               (temp_re_tmp * temp2_re - -temp_im_tmp * y_re_tmp));
    y[istart - 1].im =
        0.5 * ((temp2_im * temp_im + temp2_im_tmp * temp_re) +
               (temp_re_tmp * y_re_tmp + -temp_im_tmp * temp2_re));
    istart = (istart + static_cast<int>(z_tmp)) - 1;
    y[istart].re = 0.5 * ((temp2_im * temp2_re - temp2_im_tmp * y_re_tmp) +
                          (temp_re_tmp * temp_re - -temp_im_tmp * temp_im));
    y[istart].im = 0.5 * ((temp2_im * y_re_tmp + temp2_im_tmp * temp2_re) +
                          (temp_re_tmp * temp_im + -temp_im_tmp * temp_re));
  }
  if (hszCostab != 0) {
    temp_re_tmp = y[hszCostab].re;
    temp_im_tmp = y[hszCostab].im;
    y_re_tmp = reconVar1[hszCostab].im;
    b_y_re_tmp = reconVar1[hszCostab].re;
    c_y_re_tmp = reconVar2[hszCostab].im;
    d_y_re_tmp = reconVar2[hszCostab].re;
    temp_re = temp_re_tmp * d_y_re_tmp;
    temp2_re = temp_re_tmp * b_y_re_tmp;
    y[hszCostab].re = 0.5 * ((temp2_re - temp_im_tmp * y_re_tmp) +
                             (temp_re - -temp_im_tmp * c_y_re_tmp));
    temp2_im = temp_re_tmp * c_y_re_tmp;
    temp_im = temp_re_tmp * y_re_tmp;
    y[hszCostab].im = 0.5 * ((temp_im + temp_im_tmp * b_y_re_tmp) +
                             (temp2_im + -temp_im_tmp * d_y_re_tmp));
    istart = static_cast<int>(z_tmp) + hszCostab;
    y[istart].re = 0.5 * ((temp_re - temp_im_tmp * c_y_re_tmp) +
                          (temp2_re - -temp_im_tmp * y_re_tmp));
    y[istart].im = 0.5 * ((temp2_im + temp_im_tmp * d_y_re_tmp) +
                          (temp_im + -temp_im_tmp * b_y_re_tmp));
  }
}

//
// Arguments    : int nfft
//                boolean_T useRadix2
//                int *n2blue
//                int *nRows
// Return Type  : void
//
void FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
                                               int *n2blue, int *nRows)
{
  *n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    if (nfft > 0) {
      int n;
      int pmax;
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      *n2blue = 1 << pmax;
    }
    *nRows = *n2blue;
  }
}

//
// Arguments    : const ::coder::array<creal_T, 1U> &x
//                int unsigned_nRows
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const ::coder::array<creal_T, 1U> &x, int unsigned_nRows,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T, 1U> &y)
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0;
      y[iy].im = 0.0;
    }
  }
  iDelta2 = x.size(0);
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    boolean_T tst;
    y[iy] = x[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y[iy] = x[iDelta2 - 1];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
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
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    ju = 1;
    for (int j{k}; j < nRowsD2; j += k) {
      double twid_im;
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
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
      ju++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
