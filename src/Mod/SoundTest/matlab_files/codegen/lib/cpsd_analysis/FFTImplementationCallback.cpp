//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : int nRows
//                ::coder::array<double, 2U> &costab
//                ::coder::array<double, 2U> &sintab
//                ::coder::array<double, 2U> &sintabinv
// Return Type  : void
//
namespace cpsd
{
  namespace coder
  {
    namespace internal
    {
      void FFTImplementationCallback::b_generate_twiddle_tables(int nRows, ::
        coder::array<double, 2U> &costab, ::coder::array<double, 2U> &sintab, ::
        coder::array<double, 2U> &sintabinv)
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
      // Arguments    : int nRowsM1
      //                int nfftLen
      //                ::coder::array<int, 1U> &bitrevIndex
      // Return Type  : void
      //
      void FFTImplementationCallback::get_bitrevIndex(int nRowsM1, int nfftLen, ::
        coder::array<int, 1U> &bitrevIndex)
      {
        int b_j1;
        int iy;
        int ju;
        ju = 0;
        iy = 1;
        bitrevIndex.set_size(nfftLen);
        for (b_j1 = 0; b_j1 < nfftLen; b_j1++) {
          bitrevIndex[b_j1] = 0;
        }

        for (b_j1 = 0; b_j1 < nRowsM1; b_j1++) {
          boolean_T tst;
          bitrevIndex[b_j1] = iy;
          iy = nfftLen;
          tst = true;
          while (tst) {
            iy >>= 1;
            ju ^= iy;
            tst = ((ju & iy) == 0);
          }

          iy = ju + 1;
        }

        bitrevIndex[nRowsM1] = iy;
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
      // Arguments    : ::coder::array<creal_T, 1U> &y
      //                const ::coder::array<creal_T, 1U> &reconVar1
      //                const ::coder::array<creal_T, 1U> &reconVar2
      //                const ::coder::array<int, 2U> &wrapIndex
      //                int hnRows
      // Return Type  : void
      //
      void FFTImplementationCallback::getback_radix2_fft(::coder::array<creal_T,
        1U> &y, const ::coder::array<creal_T, 1U> &reconVar1, const ::coder::
        array<creal_T, 1U> &reconVar2, const ::coder::array<int, 2U> &wrapIndex,
        int hnRows)
      {
        double b_y_im;
        double temp1_im;
        double temp1_re;
        double temp2_im;
        double y_im;
        int b_i;
        int iterVar;
        iterVar = hnRows / 2;
        temp1_re = y[0].re;
        temp1_im = y[0].im;
        y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
        temp2_im = y[0].re;
        b_y_im = -y[0].im;
        y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im)
                         + (temp2_im * reconVar2[0].re - b_y_im * reconVar2[0].
                            im));
        y[0].im = 0.5 * (y_im + (temp2_im * reconVar2[0].im + b_y_im *
          reconVar2[0].re));
        y[hnRows].re = 0.5 * ((temp1_re * reconVar2[0].re - temp1_im *
          reconVar2[0].im) + (temp1_re * reconVar1[0].re - -temp1_im *
                              reconVar1[0].im));
        y[hnRows].im = 0.5 * ((temp1_re * reconVar2[0].im + temp1_im *
          reconVar2[0].re) + (temp1_re * reconVar1[0].im + -temp1_im *
                              reconVar1[0].re));
        for (int i = 2; i <= iterVar; i++) {
          double y_im_tmp;
          int i1;
          temp1_re = y[i - 1].re;
          temp1_im = y[i - 1].im;
          b_i = wrapIndex[i - 1];
          b_y_im = y[b_i - 1].re;
          temp2_im = y[b_i - 1].im;
          y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i -
            1].re;
          y_im_tmp = -y[b_i - 1].im;
          y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                                reconVar1[i - 1].im) + (b_y_im * reconVar2[i - 1]
            .re - y_im_tmp * reconVar2[i - 1].im));
          y[i - 1].im = 0.5 * (y_im + (b_y_im * reconVar2[i - 1].im + y_im_tmp *
            reconVar2[i - 1].re));
          i1 = (hnRows + i) - 1;
          y[i1].re = 0.5 * ((temp1_re * reconVar2[i - 1].re - temp1_im *
                             reconVar2[i - 1].im) + (b_y_im * reconVar1[i - 1].
            re - -temp2_im * reconVar1[i - 1].im));
          y[i1].im = 0.5 * ((temp1_re * reconVar2[i - 1].im + temp1_im *
                             reconVar2[i - 1].re) + (b_y_im * reconVar1[i - 1].
            im + -temp2_im * reconVar1[i - 1].re));
          y[b_i - 1].re = 0.5 * ((b_y_im * reconVar1[b_i - 1].re - temp2_im *
            reconVar1[b_i - 1].im) + (temp1_re * reconVar2[b_i - 1].re -
            -temp1_im * reconVar2[b_i - 1].im));
          y[b_i - 1].im = 0.5 * ((b_y_im * reconVar1[b_i - 1].im + temp2_im *
            reconVar1[b_i - 1].re) + (temp1_re * reconVar2[b_i - 1].im +
            -temp1_im * reconVar2[b_i - 1].re));
          i1 = (b_i + hnRows) - 1;
          y[i1].re = 0.5 * ((b_y_im * reconVar2[b_i - 1].re - temp2_im *
                             reconVar2[b_i - 1].im) + (temp1_re * reconVar1[b_i
            - 1].re - -temp1_im * reconVar1[b_i - 1].im));
          y[i1].im = 0.5 * ((b_y_im * reconVar2[b_i - 1].im + temp2_im *
                             reconVar2[b_i - 1].re) + (temp1_re * reconVar1[b_i
            - 1].im + -temp1_im * reconVar1[b_i - 1].re));
        }

        temp2_im = y[iterVar].re;
        temp1_im = y[iterVar].im;
        y_im = y[iterVar].re * reconVar1[iterVar].im + y[iterVar].im *
          reconVar1[iterVar].re;
        b_y_im = -y[iterVar].im;
        y[iterVar].re = 0.5 * ((y[iterVar].re * reconVar1[iterVar].re -
          y[iterVar].im * reconVar1[iterVar].im) + (temp2_im * reconVar2[iterVar]
          .re - b_y_im * reconVar2[iterVar].im));
        y[iterVar].im = 0.5 * (y_im + (temp2_im * reconVar2[iterVar].im + b_y_im
          * reconVar2[iterVar].re));
        b_i = hnRows + iterVar;
        y[b_i].re = 0.5 * ((temp2_im * reconVar2[iterVar].re - temp1_im *
                            reconVar2[iterVar].im) + (temp2_im *
          reconVar1[iterVar].re - -temp1_im * reconVar1[iterVar].im));
        y[b_i].im = 0.5 * ((temp2_im * reconVar2[iterVar].im + temp1_im *
                            reconVar2[iterVar].re) + (temp2_im *
          reconVar1[iterVar].im + -temp1_im * reconVar1[iterVar].re));
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

        FFTImplementationCallback::b_generate_twiddle_tables((nRows << 1),
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
      // Arguments    : const ::coder::array<double, 2U> &x
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
        double, 2U> &x, ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
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

        FFTImplementationCallback::b_generate_twiddle_tables((nRows << 1),
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
      // Arguments    : const ::coder::array<double, 1U> &x
      //                ::coder::array<creal_T, 1U> &y
      //                int unsigned_nRows
      //                const ::coder::array<double, 2U> &costab
      //                const ::coder::array<double, 2U> &sintab
      // Return Type  : void
      //
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
        double temp_im;
        double temp_re;
        double z;
        int hszCostab;
        int i;
        int istart;
        int ix;
        int j;
        int k;
        int nRows;
        int nRowsD2;
        boolean_T nxeven;
        nRows = unsigned_nRows / 2;
        istart = nRows - 2;
        nRowsD2 = nRows / 2;
        k = nRowsD2 / 2;
        hszCostab = costab.size(1) / 2;
        hcostab.set_size(1, hszCostab);
        hsintab.set_size(1, hszCostab);
        for (i = 0; i < hszCostab; i++) {
          ix = ((i + 1) << 1) - 2;
          hcostab[i] = costab[ix];
          hsintab[i] = sintab[ix];
        }

        reconVar1.set_size(nRows);
        reconVar2.set_size(nRows);
        wrapIndex.set_size(1, nRows);
        for (i = 0; i < nRows; i++) {
          temp_im = sintab[i];
          temp_re = costab[i];
          reconVar1[i].re = temp_im + 1.0;
          reconVar1[i].im = -temp_re;
          reconVar2[i].re = 1.0 - temp_im;
          reconVar2[i].im = temp_re;
          if (i + 1 != 1) {
            wrapIndex[i] = (nRows - i) + 1;
          } else {
            wrapIndex[0] = 1;
          }
        }

        z = static_cast<double>(unsigned_nRows) / 2.0;
        hszCostab = y.size(0);
        if (hszCostab >= nRows) {
          hszCostab = nRows;
        }

        FFTImplementationCallback::get_bitrevIndex((hszCostab - 1), (
          static_cast<int>(z)), (bitrevIndex));
        if ((x.size(0) & 1) == 0) {
          nxeven = true;
          hszCostab = x.size(0);
        } else if (x.size(0) >= unsigned_nRows) {
          nxeven = true;
          hszCostab = unsigned_nRows;
        } else {
          nxeven = false;
          hszCostab = x.size(0) - 1;
        }

        ix = 0;
        if (hszCostab >= unsigned_nRows) {
          hszCostab = unsigned_nRows;
        }

        temp_im = static_cast<double>(hszCostab) / 2.0;
        hszCostab = static_cast<int>(temp_im);
        for (i = 0; i < hszCostab; i++) {
          y[bitrevIndex[i] - 1].re = x[ix];
          y[bitrevIndex[i] - 1].im = x[ix + 1];
          ix += 2;
        }

        if (!nxeven) {
          hszCostab = bitrevIndex[static_cast<int>(temp_im)] - 1;
          y[hszCostab].re = x[ix];
          y[hszCostab].im = 0.0;
        }

        if (nRows > 1) {
          for (i = 0; i <= istart; i += 2) {
            temp_re = y[i + 1].re;
            temp_im = y[i + 1].im;
            y[i + 1].re = y[i].re - y[i + 1].re;
            y[i + 1].im = y[i].im - y[i + 1].im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }
        }

        hszCostab = 2;
        ix = 4;
        nRows = ((k - 1) << 2) + 1;
        while (k > 0) {
          int temp_re_tmp;
          for (i = 0; i < nRows; i += ix) {
            temp_re_tmp = i + hszCostab;
            temp_re = y[temp_re_tmp].re;
            temp_im = y[temp_re_tmp].im;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }

          istart = 1;
          for (j = k; j < nRowsD2; j += k) {
            double twid_im;
            double twid_re;
            int ihi;
            twid_re = hcostab[j];
            twid_im = hsintab[j];
            i = istart;
            ihi = istart + nRows;
            while (i < ihi) {
              temp_re_tmp = i + hszCostab;
              temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].
                im;
              temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].
                re;
              y[temp_re_tmp].re = y[i].re - temp_re;
              y[temp_re_tmp].im = y[i].im - temp_im;
              y[i].re = y[i].re + temp_re;
              y[i].im = y[i].im + temp_im;
              i += ix;
            }

            istart++;
          }

          k /= 2;
          hszCostab = ix;
          ix += ix;
          nRows -= hszCostab;
        }

        FFTImplementationCallback::getback_radix2_fft((y), (reconVar1),
          (reconVar2), (wrapIndex), (static_cast<int>(z)));
      }

      //
      // Arguments    : const ::coder::array<double, 2U> &x
      //                ::coder::array<creal_T, 1U> &y
      //                int unsigned_nRows
      //                const ::coder::array<double, 2U> &costab
      //                const ::coder::array<double, 2U> &sintab
      // Return Type  : void
      //
      void FFTImplementationCallback::doHalfLengthRadix2(const ::coder::array<
        double, 2U> &x, ::coder::array<creal_T, 1U> &y, int unsigned_nRows,
        const ::coder::array<double, 2U> &costab, const ::coder::array<double,
        2U> &sintab)
      {
        ::coder::array<creal_T, 1U> reconVar1;
        ::coder::array<creal_T, 1U> reconVar2;
        ::coder::array<double, 2U> hcostab;
        ::coder::array<double, 2U> hsintab;
        ::coder::array<int, 2U> wrapIndex;
        ::coder::array<int, 1U> bitrevIndex;
        double temp_im;
        double temp_re;
        double z;
        int hszCostab;
        int i;
        int istart;
        int ix;
        int j;
        int k;
        int nRows;
        int nRowsD2;
        boolean_T nxeven;
        nRows = unsigned_nRows / 2;
        istart = nRows - 2;
        nRowsD2 = nRows / 2;
        k = nRowsD2 / 2;
        hszCostab = costab.size(1) / 2;
        hcostab.set_size(1, hszCostab);
        hsintab.set_size(1, hszCostab);
        for (i = 0; i < hszCostab; i++) {
          ix = ((i + 1) << 1) - 2;
          hcostab[i] = costab[ix];
          hsintab[i] = sintab[ix];
        }

        reconVar1.set_size(nRows);
        reconVar2.set_size(nRows);
        wrapIndex.set_size(1, nRows);
        for (i = 0; i < nRows; i++) {
          temp_im = sintab[i];
          temp_re = costab[i];
          reconVar1[i].re = temp_im + 1.0;
          reconVar1[i].im = -temp_re;
          reconVar2[i].re = 1.0 - temp_im;
          reconVar2[i].im = temp_re;
          if (i + 1 != 1) {
            wrapIndex[i] = (nRows - i) + 1;
          } else {
            wrapIndex[0] = 1;
          }
        }

        z = static_cast<double>(unsigned_nRows) / 2.0;
        hszCostab = y.size(0);
        if (hszCostab >= nRows) {
          hszCostab = nRows;
        }

        FFTImplementationCallback::get_bitrevIndex((hszCostab - 1), (
          static_cast<int>(z)), (bitrevIndex));
        if ((x.size(0) & 1) == 0) {
          nxeven = true;
          hszCostab = x.size(0);
        } else if (x.size(0) >= unsigned_nRows) {
          nxeven = true;
          hszCostab = unsigned_nRows;
        } else {
          nxeven = false;
          hszCostab = x.size(0) - 1;
        }

        ix = 0;
        if (hszCostab >= unsigned_nRows) {
          hszCostab = unsigned_nRows;
        }

        temp_im = static_cast<double>(hszCostab) / 2.0;
        hszCostab = static_cast<int>(temp_im);
        for (i = 0; i < hszCostab; i++) {
          y[bitrevIndex[i] - 1].re = x[ix];
          y[bitrevIndex[i] - 1].im = x[ix + 1];
          ix += 2;
        }

        if (!nxeven) {
          hszCostab = bitrevIndex[static_cast<int>(temp_im)] - 1;
          y[hszCostab].re = x[ix];
          y[hszCostab].im = 0.0;
        }

        if (nRows > 1) {
          for (i = 0; i <= istart; i += 2) {
            temp_re = y[i + 1].re;
            temp_im = y[i + 1].im;
            y[i + 1].re = y[i].re - y[i + 1].re;
            y[i + 1].im = y[i].im - y[i + 1].im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }
        }

        hszCostab = 2;
        ix = 4;
        nRows = ((k - 1) << 2) + 1;
        while (k > 0) {
          int temp_re_tmp;
          for (i = 0; i < nRows; i += ix) {
            temp_re_tmp = i + hszCostab;
            temp_re = y[temp_re_tmp].re;
            temp_im = y[temp_re_tmp].im;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
          }

          istart = 1;
          for (j = k; j < nRowsD2; j += k) {
            double twid_im;
            double twid_re;
            int ihi;
            twid_re = hcostab[j];
            twid_im = hsintab[j];
            i = istart;
            ihi = istart + nRows;
            while (i < ihi) {
              temp_re_tmp = i + hszCostab;
              temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].
                im;
              temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].
                re;
              y[temp_re_tmp].re = y[i].re - temp_re;
              y[temp_re_tmp].im = y[i].im - temp_im;
              y[i].re = y[i].re + temp_re;
              y[i].im = y[i].im + temp_im;
              i += ix;
            }

            istart++;
          }

          k /= 2;
          hszCostab = ix;
          ix += ix;
          nRows -= hszCostab;
        }

        FFTImplementationCallback::getback_radix2_fft((y), (reconVar1),
          (reconVar2), (wrapIndex), (static_cast<int>(z)));
      }

      //
      // Arguments    : int nRows
      //                boolean_T useRadix2
      //                ::coder::array<double, 2U> &costab
      //                ::coder::array<double, 2U> &sintab
      //                ::coder::array<double, 2U> &sintabinv
      // Return Type  : void
      //
      void FFTImplementationCallback::generate_twiddle_tables(int nRows,
        boolean_T useRadix2, ::coder::array<double, 2U> &costab, ::coder::array<
        double, 2U> &sintab, ::coder::array<double, 2U> &sintabinv)
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
        if (!useRadix2) {
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
        } else {
          n = costab1q.size(1) - 1;
          nd2 = (costab1q.size(1) - 1) << 1;
          costab.set_size(1, (nd2 + 1));
          sintab.set_size(1, (nd2 + 1));
          costab[0] = 1.0;
          sintab[0] = 0.0;
          for (k = 0; k < n; k++) {
            costab[k + 1] = costab1q[k + 1];
            sintab[k + 1] = -costab1q[(n - k) - 1];
          }

          i = costab1q.size(1);
          for (k = i; k <= nd2; k++) {
            costab[k] = -costab1q[nd2 - k];
            sintab[k] = -costab1q[k - n];
          }

          sintabinv.set_size(1, 0);
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
          int n;
          int pmax;
          int pmin;
          boolean_T exitg1;
          n = (nfft + nfft) - 1;
          pmax = 31;
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

          *n2blue = 1 << pmax;
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
