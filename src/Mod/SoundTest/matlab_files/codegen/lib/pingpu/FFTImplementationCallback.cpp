//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 03-Dec-2023 12:42:37
//

// Include Files
#include "FFTImplementationCallback.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
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
namespace coder {
namespace internal {
namespace fft {
void FFTImplementationCallback::doHalfLengthBluestein(
    const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y,
    int nrowsx, int nRows, int nfft, const ::coder::array<creal_T, 1U> &wwc,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &costabinv,
    const ::coder::array<double, 2U> &sintabinv)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> reconVar1;
  array<creal_T, 1U> reconVar2;
  array<creal_T, 1U> ytmp;
  array<double, 2U> b_costab;
  array<double, 2U> b_sintab;
  array<double, 2U> costab1q;
  array<double, 2U> hcostabinv;
  array<double, 2U> hsintab;
  array<double, 2U> hsintabinv;
  array<int, 2U> wrapIndex;
  double b_temp_re_tmp;
  double re_tmp;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double z_tmp;
  int hnRows;
  int i;
  int iDelta2;
  int ihi;
  int istart;
  int j;
  int ju;
  int k;
  int nRowsD2;
  int nd2;
  int temp_re_tmp;
  boolean_T tst;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (iDelta2 = 0; iDelta2 < hnRows; iDelta2++) {
      ytmp[iDelta2].re = 0.0;
      ytmp[iDelta2].im = 0.0;
    }
  }
  if ((x.size(0) & 1) == 0) {
    tst = true;
    ihi = x.size(0);
  } else if (x.size(0) >= nRows) {
    tst = true;
    ihi = nRows;
  } else {
    tst = false;
    ihi = x.size(0) - 1;
  }
  if (ihi > nRows) {
    ihi = nRows;
  }
  nd2 = nRows << 1;
  temp_im = 6.2831853071795862 / static_cast<double>(nd2);
  j = nd2 / 2 / 2;
  costab1q.set_size(1, j + 1);
  costab1q[0] = 1.0;
  nd2 = j / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(temp_im * (static_cast<double>(k) + 1.0));
  }
  iDelta2 = nd2 + 2;
  nd2 = j - 1;
  for (k = iDelta2; k <= nd2; k++) {
    costab1q[k] = std::sin(temp_im * static_cast<double>(j - k));
  }
  costab1q[j] = 0.0;
  j = costab1q.size(1) - 1;
  nd2 = (costab1q.size(1) - 1) << 1;
  b_costab.set_size(1, nd2 + 1);
  b_sintab.set_size(1, nd2 + 1);
  b_costab[0] = 1.0;
  b_sintab[0] = 0.0;
  for (k = 0; k < j; k++) {
    b_costab[k + 1] = costab1q[k + 1];
    b_sintab[k + 1] = -costab1q[(j - k) - 1];
  }
  iDelta2 = costab1q.size(1);
  for (k = iDelta2; k <= nd2; k++) {
    b_costab[k] = -costab1q[nd2 - k];
    b_sintab[k] = -costab1q[k - j];
  }
  nd2 = costab.size(1) / 2;
  costab1q.set_size(1, nd2);
  hsintab.set_size(1, nd2);
  hcostabinv.set_size(1, nd2);
  hsintabinv.set_size(1, nd2);
  for (i = 0; i < nd2; i++) {
    iDelta2 = ((i + 1) << 1) - 2;
    costab1q[i] = costab[iDelta2];
    hsintab[i] = sintab[iDelta2];
    hcostabinv[i] = costabinv[iDelta2];
    hsintabinv[i] = sintabinv[iDelta2];
  }
  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  wrapIndex.set_size(1, hnRows);
  for (i = 0; i < hnRows; i++) {
    iDelta2 = i << 1;
    temp_im = b_sintab[iDelta2];
    temp_re = b_costab[iDelta2];
    reconVar1[i].re = temp_im + 1.0;
    reconVar1[i].im = -temp_re;
    reconVar2[i].re = 1.0 - temp_im;
    reconVar2[i].im = temp_re;
    if (i + 1 != 1) {
      wrapIndex[i] = (hnRows - i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }
  z_tmp = static_cast<double>(ihi) / 2.0;
  iDelta2 = static_cast<int>(z_tmp);
  for (ju = 0; ju < iDelta2; ju++) {
    temp_re_tmp = (hnRows + ju) - 1;
    temp_re = wwc[temp_re_tmp].re;
    temp_im = wwc[temp_re_tmp].im;
    nd2 = ju << 1;
    twid_re = x[nd2];
    twid_im = x[nd2 + 1];
    ytmp[ju].re = temp_re * twid_re + temp_im * twid_im;
    ytmp[ju].im = temp_re * twid_im - temp_im * twid_re;
  }
  if (!tst) {
    temp_re_tmp = (hnRows + static_cast<int>(z_tmp)) - 1;
    temp_re = wwc[temp_re_tmp].re;
    temp_im = wwc[temp_re_tmp].im;
    twid_re = x[static_cast<int>(z_tmp) << 1];
    ytmp[static_cast<int>(z_tmp)].re = temp_re * twid_re + temp_im * 0.0;
    ytmp[static_cast<int>(z_tmp)].im = temp_re * 0.0 - temp_im * twid_re;
    if (static_cast<int>(z_tmp) + 2 <= hnRows) {
      iDelta2 = static_cast<int>(static_cast<double>(ihi) / 2.0) + 2;
      for (i = iDelta2; i <= hnRows; i++) {
        ytmp[i - 1].re = 0.0;
        ytmp[i - 1].im = 0.0;
      }
    }
  } else if (static_cast<int>(z_tmp) + 1 <= hnRows) {
    iDelta2 = static_cast<int>(static_cast<double>(ihi) / 2.0) + 1;
    for (i = iDelta2; i <= hnRows; i++) {
      ytmp[i - 1].re = 0.0;
      ytmp[i - 1].im = 0.0;
    }
  }
  z_tmp = static_cast<double>(nfft) / 2.0;
  nd2 = static_cast<int>(z_tmp);
  fy.set_size(nd2);
  if (static_cast<int>(z_tmp) > ytmp.size(0)) {
    fy.set_size(nd2);
    for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
      fy[iDelta2].re = 0.0;
      fy[iDelta2].im = 0.0;
    }
  }
  ihi = ytmp.size(0);
  istart = static_cast<int>(z_tmp);
  if (ihi <= istart) {
    istart = ihi;
  }
  iDelta2 = static_cast<int>(z_tmp) - 2;
  nRowsD2 = static_cast<int>(z_tmp) / 2;
  k = nRowsD2 / 2;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= istart - 2; i++) {
    fy[nd2] = ytmp[i];
    j = static_cast<int>(z_tmp);
    tst = true;
    while (tst) {
      j >>= 1;
      ju ^= j;
      tst = ((ju & j) == 0);
    }
    nd2 = ju;
  }
  fy[nd2] = ytmp[istart - 1];
  if (static_cast<int>(z_tmp) > 1) {
    for (i = 0; i <= iDelta2; i += 2) {
      b_temp_re_tmp = fy[i + 1].re;
      temp_re = fy[i + 1].im;
      re_tmp = fy[i].re;
      twid_re = fy[i].im;
      fy[i + 1].re = re_tmp - b_temp_re_tmp;
      fy[i + 1].im = twid_re - temp_re;
      fy[i].re = re_tmp + b_temp_re_tmp;
      fy[i].im = twid_re + temp_re;
    }
  }
  nd2 = 2;
  iDelta2 = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iDelta2) {
      temp_re_tmp = i + nd2;
      temp_re = fy[temp_re_tmp].re;
      temp_im = fy[temp_re_tmp].im;
      fy[temp_re_tmp].re = fy[i].re - temp_re;
      fy[temp_re_tmp].im = fy[i].im - temp_im;
      fy[i].re = fy[i].re + temp_re;
      fy[i].im = fy[i].im + temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab1q[j];
      twid_im = hsintab[j];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + nd2;
        b_temp_re_tmp = fy[temp_re_tmp].im;
        temp_im = fy[temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * b_temp_re_tmp;
        temp_im = twid_re * b_temp_re_tmp + twid_im * temp_im;
        fy[temp_re_tmp].re = fy[i].re - temp_re;
        fy[temp_re_tmp].im = fy[i].im - temp_im;
        fy[i].re = fy[i].re + temp_re;
        fy[i].im = fy[i].im + temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    nd2 = iDelta2;
    iDelta2 += iDelta2;
    ju -= nd2;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, static_cast<int>(z_tmp),
                                                  costab1q, hsintab, fv);
  nd2 = fy.size(0);
  for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
    re_tmp = fy[iDelta2].re;
    twid_im = fv[iDelta2].im;
    temp_im = fy[iDelta2].im;
    temp_re = fv[iDelta2].re;
    fy[iDelta2].re = re_tmp * temp_re - temp_im * twid_im;
    fy[iDelta2].im = re_tmp * twid_im + temp_im * temp_re;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(fy, static_cast<int>(z_tmp),
                                                  hcostabinv, hsintabinv, fv);
  if (fv.size(0) > 1) {
    temp_im = 1.0 / static_cast<double>(fv.size(0));
    nd2 = fv.size(0);
    for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
      fv[iDelta2].re = temp_im * fv[iDelta2].re;
      fv[iDelta2].im = temp_im * fv[iDelta2].im;
    }
  }
  iDelta2 = wwc.size(0);
  for (k = hnRows; k <= iDelta2; k++) {
    temp_im = wwc[k - 1].re;
    temp_re = fv[k - 1].im;
    twid_re = wwc[k - 1].im;
    twid_im = fv[k - 1].re;
    nd2 = k - hnRows;
    ytmp[nd2].re = temp_im * twid_im + twid_re * temp_re;
    ytmp[nd2].im = temp_im * temp_re - twid_re * twid_im;
  }
  for (i = 0; i < hnRows; i++) {
    double ytmp_re_tmp;
    iDelta2 = wrapIndex[i];
    temp_im = ytmp[i].re;
    temp_re = reconVar1[i].im;
    twid_re = ytmp[i].im;
    twid_im = reconVar1[i].re;
    re_tmp = ytmp[iDelta2 - 1].re;
    b_temp_re_tmp = -ytmp[iDelta2 - 1].im;
    z_tmp = reconVar2[i].im;
    ytmp_re_tmp = reconVar2[i].re;
    y[i].re = 0.5 * ((temp_im * twid_im - twid_re * temp_re) +
                     (re_tmp * ytmp_re_tmp - b_temp_re_tmp * z_tmp));
    y[i].im = 0.5 * ((temp_im * temp_re + twid_re * twid_im) +
                     (re_tmp * z_tmp + b_temp_re_tmp * ytmp_re_tmp));
    iDelta2 = hnRows + i;
    y[iDelta2].re = 0.5 * ((temp_im * ytmp_re_tmp - twid_re * z_tmp) +
                           (re_tmp * twid_im - b_temp_re_tmp * temp_re));
    y[iDelta2].im = 0.5 * ((temp_im * z_tmp + twid_re * ytmp_re_tmp) +
                           (re_tmp * temp_re + b_temp_re_tmp * twid_im));
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
// Arguments    : const ::coder::array<double, 1U> &x
//                int n2blue
//                int nfft
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                const ::coder::array<double, 2U> &sintabinv
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const ::coder::array<double, 1U> &x, int n2blue, int nfft,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &sintabinv, ::coder::array<creal_T, 1U> &y)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> wwc;
  double nt_im;
  double nt_re;
  int ihi;
  int j;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int rt;
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    j = nfft / 2;
    nInt2m1 = (j + j) - 1;
    wwc.set_size(nInt2m1);
    rt = 0;
    wwc[j - 1].re = 1.0;
    wwc[j - 1].im = 0.0;
    nInt2 = j << 1;
    for (k = 0; k <= j - 2; k++) {
      minNrowsNx = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= minNrowsNx) {
        rt += minNrowsNx - nInt2;
      } else {
        rt += minNrowsNx;
      }
      nt_im = -3.1415926535897931 * static_cast<double>(rt) /
              static_cast<double>(j);
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = std::cos(nt_im);
        nt_im = std::sin(nt_im);
      }
      ihi = (j - k) - 2;
      wwc[ihi].re = nt_re;
      wwc[ihi].im = -nt_im;
    }
    ihi = nInt2m1 - 1;
    for (k = ihi; k >= j; k--) {
      wwc[k] = wwc[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    wwc.set_size(nInt2m1);
    rt = 0;
    wwc[nfft - 1].re = 1.0;
    wwc[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      minNrowsNx = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= minNrowsNx) {
        rt += minNrowsNx - nInt2;
      } else {
        rt += minNrowsNx;
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
      ihi = (nfft - k) - 2;
      wwc[ihi].re = nt_re;
      wwc[ihi].im = -nt_im;
    }
    ihi = nInt2m1 - 1;
    for (k = ihi; k >= nfft; k--) {
      wwc[k] = wwc[(nInt2m1 - k) - 1];
    }
  }
  y.set_size(nfft);
  if (nfft > x.size(0)) {
    y.set_size(nfft);
    for (ihi = 0; ihi < nfft; ihi++) {
      y[ihi].re = 0.0;
      y[ihi].im = 0.0;
    }
  }
  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    FFTImplementationCallback::doHalfLengthBluestein(
        x, y, x.size(0), nfft, n2blue, wwc, costab, sintab, costab, sintabinv);
  } else {
    double b_nt_re_tmp;
    double twid_im;
    double twid_re;
    int i;
    int nRowsD2;
    int nt_re_tmp;
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    for (k = 0; k < minNrowsNx; k++) {
      nt_re_tmp = (nfft + k) - 1;
      y[k].re = wwc[nt_re_tmp].re * x[k];
      y[k].im = wwc[nt_re_tmp].im * -x[k];
    }
    ihi = minNrowsNx + 1;
    for (k = ihi; k <= nfft; k++) {
      y[k - 1].re = 0.0;
      y[k - 1].im = 0.0;
    }
    fy.set_size(n2blue);
    if (n2blue > y.size(0)) {
      fy.set_size(n2blue);
      for (ihi = 0; ihi < n2blue; ihi++) {
        fy[ihi].re = 0.0;
        fy[ihi].im = 0.0;
      }
    }
    nInt2m1 = y.size(0);
    if (nInt2m1 > n2blue) {
      nInt2m1 = n2blue;
    }
    rt = n2blue - 2;
    nRowsD2 = n2blue / 2;
    k = nRowsD2 / 2;
    minNrowsNx = 0;
    nInt2 = 0;
    for (i = 0; i <= nInt2m1 - 2; i++) {
      boolean_T tst;
      fy[minNrowsNx] = y[i];
      minNrowsNx = n2blue;
      tst = true;
      while (tst) {
        minNrowsNx >>= 1;
        nInt2 ^= minNrowsNx;
        tst = ((nInt2 & minNrowsNx) == 0);
      }
      minNrowsNx = nInt2;
    }
    fy[minNrowsNx] = y[nInt2m1 - 1];
    if (n2blue > 1) {
      for (i = 0; i <= rt; i += 2) {
        b_nt_re_tmp = fy[i + 1].re;
        nt_im = fy[i + 1].im;
        twid_im = fy[i].re;
        nt_re = fy[i].im;
        fy[i + 1].re = twid_im - b_nt_re_tmp;
        fy[i + 1].im = nt_re - nt_im;
        fy[i].re = twid_im + b_nt_re_tmp;
        fy[i].im = nt_re + nt_im;
      }
    }
    minNrowsNx = 2;
    nInt2m1 = 4;
    rt = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (i = 0; i < rt; i += nInt2m1) {
        nt_re_tmp = i + minNrowsNx;
        nt_re = fy[nt_re_tmp].re;
        nt_im = fy[nt_re_tmp].im;
        fy[nt_re_tmp].re = fy[i].re - nt_re;
        fy[nt_re_tmp].im = fy[i].im - nt_im;
        fy[i].re = fy[i].re + nt_re;
        fy[i].im = fy[i].im + nt_im;
      }
      nInt2 = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = nInt2;
        ihi = nInt2 + rt;
        while (i < ihi) {
          nt_re_tmp = i + minNrowsNx;
          b_nt_re_tmp = fy[nt_re_tmp].im;
          nt_im = fy[nt_re_tmp].re;
          nt_re = twid_re * nt_im - twid_im * b_nt_re_tmp;
          nt_im = twid_re * b_nt_re_tmp + twid_im * nt_im;
          fy[nt_re_tmp].re = fy[i].re - nt_re;
          fy[nt_re_tmp].im = fy[i].im - nt_im;
          fy[i].re = fy[i].re + nt_re;
          fy[i].im = fy[i].im + nt_im;
          i += nInt2m1;
        }
        nInt2++;
      }
      k /= 2;
      minNrowsNx = nInt2m1;
      nInt2m1 += nInt2m1;
      rt -= minNrowsNx;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    minNrowsNx = fy.size(0);
    for (ihi = 0; ihi < minNrowsNx; ihi++) {
      twid_im = fy[ihi].re;
      nt_im = fv[ihi].im;
      nt_re = fy[ihi].im;
      twid_re = fv[ihi].re;
      fy[ihi].re = twid_im * twid_re - nt_re * nt_im;
      fy[ihi].im = twid_im * nt_im + nt_re * twid_re;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      nt_im = 1.0 / static_cast<double>(fv.size(0));
      minNrowsNx = fv.size(0);
      for (ihi = 0; ihi < minNrowsNx; ihi++) {
        fv[ihi].re = nt_im * fv[ihi].re;
        fv[ihi].im = nt_im * fv[ihi].im;
      }
    }
    ihi = wwc.size(0);
    for (k = nfft; k <= ihi; k++) {
      nt_im = wwc[k - 1].re;
      nt_re = fv[k - 1].im;
      twid_re = wwc[k - 1].im;
      twid_im = fv[k - 1].re;
      minNrowsNx = k - nfft;
      y[minNrowsNx].re = nt_im * twid_im + twid_re * nt_re;
      y[minNrowsNx].im = nt_im * nt_re - twid_re * twid_im;
    }
  }
}

} // namespace fft
} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
