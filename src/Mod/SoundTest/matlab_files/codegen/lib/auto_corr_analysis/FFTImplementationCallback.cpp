//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:06:11
//

// Include Files
#include "FFTImplementationCallback.h"
#include "auto_corr_analysis_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
//                int unsigned_nRows
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
// Return Type  : void
//
namespace corr
{
  namespace coder
  {
    namespace internal
    {
      void FFTImplementationCallback::doHalfLengthRadix2(const ::coder::array<
        double, 1U> &x, ::coder::array<creal_T, 1U> &y, int unsigned_nRows,
        const ::coder::array<double, 2U> &costab, const ::coder::array<double,
        2U> &sintab)
      {
        ::coder::array<creal_T, 1U> reconVar1;
        ::coder::array<creal_T, 1U> reconVar2;
        ::coder::array<double, 2U> hcostab;
        ::coder::array<double, 2U> hsintab;
        ::coder::array<int, 2U> wrapIndex;
        ::coder::array<int, 1U> bitrevIndex;
        double temp2_im;
        double temp2_re;
        double temp_im;
        double temp_re;
        double y_im;
        double y_im_tmp;
        double z;
        int hszCostab;
        int i;
        int ihi;
        int istart;
        int iy;
        int ju;
        int k;
        int nRows;
        int nRowsD2;
        int nRowsM2;
        boolean_T tst;
        nRows = unsigned_nRows / 2;
        ihi = y.size(0);
        if (ihi >= nRows) {
          ihi = nRows;
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
          temp2_im = sintab[i];
          temp2_re = costab[i];
          reconVar1[i].re = temp2_im + 1.0;
          reconVar1[i].im = -temp2_re;
          reconVar2[i].re = 1.0 - temp2_im;
          reconVar2[i].im = temp2_re;
          if (i + 1 != 1) {
            wrapIndex[i] = (nRows - i) + 1;
          } else {
            wrapIndex[0] = 1;
          }
        }

        z = static_cast<double>(unsigned_nRows) / 2.0;
        ju = 0;
        iy = 1;
        bitrevIndex.set_size((static_cast<int>(z)));
        hszCostab = static_cast<int>(z);
        for (istart = 0; istart < hszCostab; istart++) {
          bitrevIndex[istart] = 0;
        }

        for (istart = 0; istart <= ihi - 2; istart++) {
          bitrevIndex[istart] = iy;
          hszCostab = static_cast<int>(z);
          tst = true;
          while (tst) {
            hszCostab >>= 1;
            ju ^= hszCostab;
            tst = ((ju & hszCostab) == 0);
          }

          iy = ju + 1;
        }

        bitrevIndex[ihi - 1] = iy;
        if ((x.size(0) & 1) == 0) {
          tst = true;
          ihi = x.size(0);
        } else if (x.size(0) >= unsigned_nRows) {
          tst = true;
          ihi = unsigned_nRows;
        } else {
          tst = false;
          ihi = x.size(0) - 1;
        }

        hszCostab = 0;
        if (ihi >= unsigned_nRows) {
          ihi = unsigned_nRows;
        }

        temp2_im = static_cast<double>(ihi) / 2.0;
        istart = static_cast<int>(temp2_im);
        for (i = 0; i < istart; i++) {
          y[bitrevIndex[i] - 1].re = x[hszCostab];
          y[bitrevIndex[i] - 1].im = x[hszCostab + 1];
          hszCostab += 2;
        }

        if (!tst) {
          istart = bitrevIndex[static_cast<int>(temp2_im)] - 1;
          y[istart].re = x[hszCostab];
          y[istart].im = 0.0;
        }

        if (nRows > 1) {
          for (i = 0; i <= nRowsM2; i += 2) {
            temp_re = y[i + 1].re;
            temp_im = y[i + 1].im;
            y[i + 1].re = y[i].re - y[i + 1].re;
            y[i + 1].im = y[i].im - y[i + 1].im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
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
          for (nRows = k; nRows < nRowsD2; nRows += k) {
            temp2_re = hcostab[nRows];
            temp2_im = hsintab[nRows];
            i = istart;
            ihi = istart + ju;
            while (i < ihi) {
              nRowsM2 = i + hszCostab;
              temp_re = temp2_re * y[nRowsM2].re - temp2_im * y[nRowsM2].im;
              temp_im = temp2_re * y[nRowsM2].im + temp2_im * y[nRowsM2].re;
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

        hszCostab = static_cast<int>(z) / 2;
        temp_re = y[0].re;
        temp_im = y[0].im;
        y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
        temp2_re = y[0].re;
        temp2_im = -y[0].im;
        y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im)
                         + (temp2_re * reconVar2[0].re - temp2_im * reconVar2[0]
                            .im));
        y[0].im = 0.5 * (y_im + (temp2_re * reconVar2[0].im + temp2_im *
          reconVar2[0].re));
        y[static_cast<int>(z)].re = 0.5 * ((temp_re * reconVar2[0].re - temp_im *
          reconVar2[0].im) + (temp_re * reconVar1[0].re - -temp_im * reconVar1[0]
                              .im));
        y[static_cast<int>(z)].im = 0.5 * ((temp_re * reconVar2[0].im + temp_im *
          reconVar2[0].re) + (temp_re * reconVar1[0].im + -temp_im * reconVar1[0]
                              .re));
        for (i = 2; i <= hszCostab; i++) {
          temp_re = y[i - 1].re;
          temp_im = y[i - 1].im;
          istart = wrapIndex[i - 1];
          temp2_re = y[istart - 1].re;
          temp2_im = y[istart - 1].im;
          y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i -
            1].re;
          y_im_tmp = -y[istart - 1].im;
          y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                                reconVar1[i - 1].im) + (temp2_re * reconVar2[i -
            1].re - y_im_tmp * reconVar2[i - 1].im));
          y[i - 1].im = 0.5 * (y_im + (temp2_re * reconVar2[i - 1].im + y_im_tmp
            * reconVar2[i - 1].re));
          iy = (static_cast<int>(z) + i) - 1;
          y[iy].re = 0.5 * ((temp_re * reconVar2[i - 1].re - temp_im *
                             reconVar2[i - 1].im) + (temp2_re * reconVar1[i - 1]
            .re - -temp2_im * reconVar1[i - 1].im));
          y[iy].im = 0.5 * ((temp_re * reconVar2[i - 1].im + temp_im *
                             reconVar2[i - 1].re) + (temp2_re * reconVar1[i - 1]
            .im + -temp2_im * reconVar1[i - 1].re));
          y[istart - 1].re = 0.5 * ((temp2_re * reconVar1[istart - 1].re -
            temp2_im * reconVar1[istart - 1].im) + (temp_re * reconVar2[istart -
            1].re - -temp_im * reconVar2[istart - 1].im));
          y[istart - 1].im = 0.5 * ((temp2_re * reconVar1[istart - 1].im +
            temp2_im * reconVar1[istart - 1].re) + (temp_re * reconVar2[istart -
            1].im + -temp_im * reconVar2[istart - 1].re));
          iy = (istart + static_cast<int>(z)) - 1;
          y[iy].re = 0.5 * ((temp2_re * reconVar2[istart - 1].re - temp2_im *
                             reconVar2[istart - 1].im) + (temp_re *
            reconVar1[istart - 1].re - -temp_im * reconVar1[istart - 1].im));
          y[iy].im = 0.5 * ((temp2_re * reconVar2[istart - 1].im + temp2_im *
                             reconVar2[istart - 1].re) + (temp_re *
            reconVar1[istart - 1].im + -temp_im * reconVar1[istart - 1].re));
        }

        if (hszCostab != 0) {
          temp2_im = y[hszCostab].re;
          temp_im = y[hszCostab].im;
          y_im = y[hszCostab].re * reconVar1[hszCostab].im + y[hszCostab].im *
            reconVar1[hszCostab].re;
          y_im_tmp = -y[hszCostab].im;
          y[hszCostab].re = 0.5 * ((y[hszCostab].re * reconVar1[hszCostab].re -
            y[hszCostab].im * reconVar1[hszCostab].im) + (temp2_im *
            reconVar2[hszCostab].re - y_im_tmp * reconVar2[hszCostab].im));
          y[hszCostab].im = 0.5 * (y_im + (temp2_im * reconVar2[hszCostab].im +
            y_im_tmp * reconVar2[hszCostab].re));
          istart = static_cast<int>(z) + hszCostab;
          y[istart].re = 0.5 * ((temp2_im * reconVar2[hszCostab].re - temp_im *
            reconVar2[hszCostab].im) + (temp2_im * reconVar1[hszCostab].re -
            -temp_im * reconVar1[hszCostab].im));
          y[istart].im = 0.5 * ((temp2_im * reconVar2[hszCostab].im + temp_im *
            reconVar2[hszCostab].re) + (temp2_im * reconVar1[hszCostab].im +
            -temp_im * reconVar1[hszCostab].re));
        }
      }

      //
      // Arguments    : int nRows
      //                ::coder::array<double, 2U> &costab
      //                ::coder::array<double, 2U> &sintab
      //                ::coder::array<double, 2U> &sintabinv
      // Return Type  : void
      //
      void FFTImplementationCallback::generate_twiddle_tables(int nRows, ::coder::
        array<double, 2U> &costab, ::coder::array<double, 2U> &sintab, ::coder::
        array<double, 2U> &sintabinv)
      {
        ::coder::array<double, 2U> costab1q;
        double e;
        int i;
        int k;
        int n;
        int nd2;
        e = 6.2831853071795862 / static_cast<double>(nRows);
        n = nRows / 2 / 2;
        costab1q.set_size(1, (n + 1));
        costab1q[0] = 1.0;
        nd2 = n / 2 - 1;
        for (k = 0; k <= nd2; k++) {
          costab1q[k + 1] = cos(e * (static_cast<double>(k) + 1.0));
        }

        i = nd2 + 2;
        nd2 = n - 1;
        for (k = i; k <= nd2; k++) {
          costab1q[k] = sin(e * static_cast<double>(n - k));
        }

        costab1q[n] = 0.0;
        n = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (nd2 + 1));
        for (k = 0; k < n; k++) {
          sintabinv[k + 1] = costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - n];
        }

        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
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
      void FFTImplementationCallback::get_half_twiddle_tables(const ::coder::
        array<double, 2U> &costab, const ::coder::array<double, 2U> &sintab,
        const ::coder::array<double, 2U> &costabinv, const ::coder::array<double,
        2U> &sintabinv, ::coder::array<double, 2U> &hcostab, ::coder::array<
        double, 2U> &hsintab, ::coder::array<double, 2U> &hcostabinv, ::coder::
        array<double, 2U> &hsintabinv)
      {
        int hszCostab;
        hszCostab = costab.size(1) / 2;
        hcostab.set_size(1, hszCostab);
        hsintab.set_size(1, hszCostab);
        hcostabinv.set_size(1, hszCostab);
        hsintabinv.set_size(1, hszCostab);
        for (int i = 0; i < hszCostab; i++) {
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
      void FFTImplementationCallback::b_doHalfLengthBluestein(const ::coder::
        array<double, 1U> &x, ::coder::array<creal_T, 1U> &y, int nrowsx, int
        nRows, int nfft, const ::coder::array<creal_T, 1U> &wwc, const ::coder::
        array<double, 2U> &costab, const ::coder::array<double, 2U> &sintab,
        const ::coder::array<double, 2U> &costabinv, const ::coder::array<double,
        2U> &sintabinv)
      {
        ::coder::array<creal_T, 1U> b_fv;
        ::coder::array<creal_T, 1U> fv;
        ::coder::array<creal_T, 1U> reconVar1;
        ::coder::array<creal_T, 1U> reconVar2;
        ::coder::array<creal_T, 1U> ytmp;
        ::coder::array<double, 2U> costable;
        ::coder::array<double, 2U> hcostabinv;
        ::coder::array<double, 2U> hsintab;
        ::coder::array<double, 2U> hsintabinv;
        ::coder::array<double, 2U> sintable;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<int, 2U> wrapIndex;
        double a_im;
        double a_re;
        double b_re;
        double z_tmp;
        int hnRows;
        int i;
        int idx;
        int u0;
        int xidx;
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

        if (u0 >= nRows) {
          u0 = nRows;
        }

        FFTImplementationCallback::generate_twiddle_tables((nRows << 1),
          (costable), (sintable), (unusedU0));
        FFTImplementationCallback::get_half_twiddle_tables((costab), (sintab),
          (costabinv), (sintabinv), (unusedU0), (hsintab), (hcostabinv),
          (hsintabinv));
        reconVar1.set_size(hnRows);
        reconVar2.set_size(hnRows);
        idx = 0;
        wrapIndex.set_size(1, hnRows);
        for (xidx = 0; xidx < hnRows; xidx++) {
          reconVar1[xidx].re = 1.0 - sintable[idx];
          reconVar1[xidx].im = -costable[idx];
          reconVar2[xidx].re = sintable[idx] + 1.0;
          reconVar2[xidx].im = costable[idx];
          idx += 2;
          if (xidx + 1 != 1) {
            wrapIndex[xidx] = (hnRows - xidx) + 1;
          } else {
            wrapIndex[0] = 1;
          }
        }

        xidx = 0;
        z_tmp = static_cast<double>(u0) / 2.0;
        i = static_cast<int>(z_tmp);
        for (int k1 = 0; k1 < i; k1++) {
          double b_im;
          idx = (hnRows + k1) - 1;
          a_re = wwc[idx].re;
          a_im = wwc[idx].im;
          b_re = x[xidx];
          b_im = x[xidx + 1];
          ytmp[k1].re = a_re * b_re + a_im * b_im;
          ytmp[k1].im = a_re * b_im - a_im * b_re;
          xidx += 2;
        }

        if (!nxeven) {
          idx = (hnRows + static_cast<int>(z_tmp)) - 1;
          a_re = wwc[idx].re;
          a_im = wwc[idx].im;
          b_re = x[xidx];
          ytmp[static_cast<int>(static_cast<double>(u0) / 2.0)].re = a_re * b_re
            + a_im * 0.0;
          ytmp[static_cast<int>(static_cast<double>(u0) / 2.0)].im = a_re * 0.0
            - a_im * b_re;
          if (static_cast<int>(z_tmp) + 2 <= hnRows) {
            i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
            for (xidx = i; xidx <= hnRows; xidx++) {
              ytmp[xidx - 1].re = 0.0;
              ytmp[xidx - 1].im = 0.0;
            }
          }
        } else {
          if (static_cast<int>(z_tmp) + 1 <= hnRows) {
            i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
            for (xidx = i; xidx <= hnRows; xidx++) {
              ytmp[xidx - 1].re = 0.0;
              ytmp[xidx - 1].im = 0.0;
            }
          }
        }

        idx = static_cast<int>(static_cast<double>(nfft) / 2.0);
        FFTImplementationCallback::r2br_r2dit_trig_impl((ytmp), (idx), (unusedU0),
          (hsintab), (fv));
        FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (idx), (unusedU0),
          (hsintab), (b_fv));
        b_fv.set_size(fv.size(0));
        xidx = fv.size(0);
        for (i = 0; i < xidx; i++) {
          z_tmp = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
          b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
          b_fv[i].im = z_tmp;
        }

        FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (idx),
          (hcostabinv), (hsintabinv), (fv));
        if (fv.size(0) > 1) {
          z_tmp = 1.0 / static_cast<double>(fv.size(0));
          xidx = fv.size(0);
          for (i = 0; i < xidx; i++) {
            fv[i].re = z_tmp * fv[i].re;
            fv[i].im = z_tmp * fv[i].im;
          }
        }

        idx = 0;
        i = wwc.size(0);
        for (xidx = hnRows; xidx <= i; xidx++) {
          ytmp[idx].re = wwc[xidx - 1].re * fv[xidx - 1].re + wwc[xidx - 1].im *
            fv[xidx - 1].im;
          ytmp[idx].im = wwc[xidx - 1].re * fv[xidx - 1].im - wwc[xidx - 1].im *
            fv[xidx - 1].re;
          z_tmp = ytmp[idx].re;
          a_im = ytmp[idx].im;
          if (a_im == 0.0) {
            a_re = z_tmp / static_cast<double>(hnRows);
            z_tmp = 0.0;
          } else if (z_tmp == 0.0) {
            a_re = 0.0;
            z_tmp = a_im / static_cast<double>(hnRows);
          } else {
            a_re = z_tmp / static_cast<double>(hnRows);
            z_tmp = a_im / static_cast<double>(hnRows);
          }

          ytmp[idx].re = a_re;
          ytmp[idx].im = z_tmp;
          idx++;
        }

        for (xidx = 0; xidx < hnRows; xidx++) {
          i = wrapIndex[xidx];
          z_tmp = ytmp[i - 1].re;
          a_re = -ytmp[i - 1].im;
          y[xidx].re = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].re - ytmp[xidx].
                               im * reconVar1[xidx].im) + (z_tmp *
            reconVar2[xidx].re - a_re * reconVar2[xidx].im));
          y[xidx].im = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].im + ytmp[xidx].
                               im * reconVar1[xidx].re) + (z_tmp *
            reconVar2[xidx].im + a_re * reconVar2[xidx].re));
          i = hnRows + xidx;
          y[i].re = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].re - ytmp[xidx].im *
                            reconVar2[xidx].im) + (z_tmp * reconVar1[xidx].re -
            a_re * reconVar1[xidx].im));
          y[i].im = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].im + ytmp[xidx].im *
                            reconVar2[xidx].re) + (z_tmp * reconVar1[xidx].im +
            a_re * reconVar1[xidx].re));
        }

        xidx = y.size(0);
        for (i = 0; i < xidx; i++) {
          z_tmp = y[i].re;
          a_im = y[i].im;
          if (a_im == 0.0) {
            a_re = z_tmp / 2.0;
            z_tmp = 0.0;
          } else if (z_tmp == 0.0) {
            a_re = 0.0;
            z_tmp = a_im / 2.0;
          } else {
            a_re = z_tmp / 2.0;
            z_tmp = a_im / 2.0;
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
      void FFTImplementationCallback::doHalfLengthBluestein(const ::coder::array<
        double, 1U> &x, ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
        int nfft, const ::coder::array<creal_T, 1U> &wwc, const ::coder::array<
        double, 2U> &costab, const ::coder::array<double, 2U> &sintab, const ::
        coder::array<double, 2U> &costabinv, const ::coder::array<double, 2U>
        &sintabinv)
      {
        ::coder::array<creal_T, 1U> b_fv;
        ::coder::array<creal_T, 1U> fv;
        ::coder::array<creal_T, 1U> reconVar1;
        ::coder::array<creal_T, 1U> reconVar2;
        ::coder::array<creal_T, 1U> ytmp;
        ::coder::array<double, 2U> costable;
        ::coder::array<double, 2U> hcostabinv;
        ::coder::array<double, 2U> hsintab;
        ::coder::array<double, 2U> hsintabinv;
        ::coder::array<double, 2U> sintable;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<int, 2U> wrapIndex;
        double a_im;
        double a_re;
        double b_re;
        double z_tmp;
        int hnRows;
        int i;
        int idx;
        int u0;
        int xidx;
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

        if (u0 >= nRows) {
          u0 = nRows;
        }

        FFTImplementationCallback::generate_twiddle_tables((nRows << 1),
          (costable), (sintable), (unusedU0));
        FFTImplementationCallback::get_half_twiddle_tables((costab), (sintab),
          (costabinv), (sintabinv), (unusedU0), (hsintab), (hcostabinv),
          (hsintabinv));
        reconVar1.set_size(hnRows);
        reconVar2.set_size(hnRows);
        idx = 0;
        wrapIndex.set_size(1, hnRows);
        for (xidx = 0; xidx < hnRows; xidx++) {
          reconVar1[xidx].re = sintable[idx] + 1.0;
          reconVar1[xidx].im = -costable[idx];
          reconVar2[xidx].re = 1.0 - sintable[idx];
          reconVar2[xidx].im = costable[idx];
          idx += 2;
          if (xidx + 1 != 1) {
            wrapIndex[xidx] = (hnRows - xidx) + 1;
          } else {
            wrapIndex[0] = 1;
          }
        }

        xidx = 0;
        z_tmp = static_cast<double>(u0) / 2.0;
        i = static_cast<int>(z_tmp);
        for (int k1 = 0; k1 < i; k1++) {
          double b_im;
          idx = (hnRows + k1) - 1;
          a_re = wwc[idx].re;
          a_im = wwc[idx].im;
          b_re = x[xidx];
          b_im = x[xidx + 1];
          ytmp[k1].re = a_re * b_re + a_im * b_im;
          ytmp[k1].im = a_re * b_im - a_im * b_re;
          xidx += 2;
        }

        if (!nxeven) {
          idx = (hnRows + static_cast<int>(z_tmp)) - 1;
          a_re = wwc[idx].re;
          a_im = wwc[idx].im;
          b_re = x[xidx];
          ytmp[static_cast<int>(static_cast<double>(u0) / 2.0)].re = a_re * b_re
            + a_im * 0.0;
          ytmp[static_cast<int>(static_cast<double>(u0) / 2.0)].im = a_re * 0.0
            - a_im * b_re;
          if (static_cast<int>(z_tmp) + 2 <= hnRows) {
            i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
            for (xidx = i; xidx <= hnRows; xidx++) {
              ytmp[xidx - 1].re = 0.0;
              ytmp[xidx - 1].im = 0.0;
            }
          }
        } else {
          if (static_cast<int>(z_tmp) + 1 <= hnRows) {
            i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
            for (xidx = i; xidx <= hnRows; xidx++) {
              ytmp[xidx - 1].re = 0.0;
              ytmp[xidx - 1].im = 0.0;
            }
          }
        }

        idx = static_cast<int>(static_cast<double>(nfft) / 2.0);
        FFTImplementationCallback::r2br_r2dit_trig_impl((ytmp), (idx), (unusedU0),
          (hsintab), (fv));
        FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (idx), (unusedU0),
          (hsintab), (b_fv));
        b_fv.set_size(fv.size(0));
        xidx = fv.size(0);
        for (i = 0; i < xidx; i++) {
          z_tmp = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
          b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
          b_fv[i].im = z_tmp;
        }

        FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (idx),
          (hcostabinv), (hsintabinv), (fv));
        if (fv.size(0) > 1) {
          z_tmp = 1.0 / static_cast<double>(fv.size(0));
          xidx = fv.size(0);
          for (i = 0; i < xidx; i++) {
            fv[i].re = z_tmp * fv[i].re;
            fv[i].im = z_tmp * fv[i].im;
          }
        }

        idx = 0;
        i = wwc.size(0);
        for (xidx = hnRows; xidx <= i; xidx++) {
          ytmp[idx].re = wwc[xidx - 1].re * fv[xidx - 1].re + wwc[xidx - 1].im *
            fv[xidx - 1].im;
          ytmp[idx].im = wwc[xidx - 1].re * fv[xidx - 1].im - wwc[xidx - 1].im *
            fv[xidx - 1].re;
          idx++;
        }

        for (xidx = 0; xidx < hnRows; xidx++) {
          i = wrapIndex[xidx];
          z_tmp = ytmp[i - 1].re;
          a_re = -ytmp[i - 1].im;
          y[xidx].re = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].re - ytmp[xidx].
                               im * reconVar1[xidx].im) + (z_tmp *
            reconVar2[xidx].re - a_re * reconVar2[xidx].im));
          y[xidx].im = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].im + ytmp[xidx].
                               im * reconVar1[xidx].re) + (z_tmp *
            reconVar2[xidx].im + a_re * reconVar2[xidx].re));
          i = hnRows + xidx;
          y[i].re = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].re - ytmp[xidx].im *
                            reconVar2[xidx].im) + (z_tmp * reconVar1[xidx].re -
            a_re * reconVar1[xidx].im));
          y[i].im = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].im + ytmp[xidx].im *
                            reconVar2[xidx].re) + (z_tmp * reconVar1[xidx].im +
            a_re * reconVar1[xidx].re));
        }
      }

      //
      // Arguments    : int nfft
      //                boolean_T useRadix2
      //                int *n2blue
      //                int *nRows
      // Return Type  : void
      //
      void FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T
        useRadix2, int *n2blue, int *nRows)
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
      // Arguments    : const ::coder::array<double, 1U> &x
      //                int unsigned_nRows
      //                const ::coder::array<double, 2U> &costab
      //                const ::coder::array<double, 2U> &sintab
      //                ::coder::array<creal_T, 1U> &y
      // Return Type  : void
      //
      void FFTImplementationCallback::r2br_r2dit_trig_impl(const ::coder::array<
        double, 1U> &x, int unsigned_nRows, const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, ::coder::array<
        creal_T, 1U> &y)
      {
        int u0;
        y.set_size(unsigned_nRows);
        if (unsigned_nRows > x.size(0)) {
          y.set_size(unsigned_nRows);
          for (u0 = 0; u0 < unsigned_nRows; u0++) {
            y[u0].re = 0.0;
            y[u0].im = 0.0;
          }
        }

        if (unsigned_nRows != 1) {
          FFTImplementationCallback::doHalfLengthRadix2((x), (y),
            (unsigned_nRows), (costab), (sintab));
        } else {
          int i;
          int loop_ub;
          u0 = x.size(0);
          if (u0 >= 1) {
            u0 = 1;
          }

          loop_ub = u0 - 2;
          i = 0;
          int exitg1;
          do {
            if (i <= loop_ub) {
              y[0].re = x[0];
              y[0].im = 0.0;
              exitg1 = 1;
            } else {
              y[0].re = x[0];
              y[0].im = 0.0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
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
      void FFTImplementationCallback::r2br_r2dit_trig_impl(const ::coder::array<
        creal_T, 1U> &x, int unsigned_nRows, const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, ::coder::array<
        creal_T, 1U> &y)
      {
        double temp_im;
        double temp_re;
        double twid_im;
        double twid_re;
        int i;
        int iDelta2;
        int iheight;
        int ix;
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
        if (iDelta2 >= unsigned_nRows) {
          iDelta2 = unsigned_nRows;
        }

        iheight = unsigned_nRows - 2;
        nRowsD2 = unsigned_nRows / 2;
        k = nRowsD2 / 2;
        ix = 0;
        iy = 0;
        ju = 0;
        for (i = 0; i <= iDelta2 - 2; i++) {
          boolean_T tst;
          y[iy] = x[ix];
          iy = unsigned_nRows;
          tst = true;
          while (tst) {
            iy >>= 1;
            ju ^= iy;
            tst = ((ju & iy) == 0);
          }

          iy = ju;
          ix++;
        }

        y[iy] = x[ix];
        if (unsigned_nRows > 1) {
          for (i = 0; i <= iheight; i += 2) {
            temp_re = y[i + 1].re;
            temp_im = y[i + 1].im;
            twid_re = y[i].re;
            twid_im = y[i].im;
            y[i + 1].re = y[i].re - y[i + 1].re;
            y[i + 1].im = y[i].im - y[i + 1].im;
            twid_re += temp_re;
            twid_im += temp_im;
            y[i].re = twid_re;
            y[i].im = twid_im;
          }
        }

        iy = 2;
        iDelta2 = 4;
        iheight = ((k - 1) << 2) + 1;
        while (k > 0) {
          int temp_re_tmp;
          for (i = 0; i < iheight; i += iDelta2) {
            temp_re_tmp = i + iy;
            temp_re = y[temp_re_tmp].re;
            temp_im = y[temp_re_tmp].im;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }

          ix = 1;
          for (ju = k; ju < nRowsD2; ju += k) {
            int ihi;
            twid_re = costab[ju];
            twid_im = sintab[ju];
            i = ix;
            ihi = ix + iheight;
            while (i < ihi) {
              temp_re_tmp = i + iy;
              temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].
                im;
              temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].
                re;
              y[temp_re_tmp].re = y[i].re - temp_re;
              y[temp_re_tmp].im = y[i].im - temp_im;
              y[i].re = y[i].re + temp_re;
              y[i].im = y[i].im + temp_im;
              i += iDelta2;
            }

            ix++;
          }

          k /= 2;
          iy = iDelta2;
          iDelta2 += iDelta2;
          iheight -= iy;
        }
      }
    }
  }
}

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
