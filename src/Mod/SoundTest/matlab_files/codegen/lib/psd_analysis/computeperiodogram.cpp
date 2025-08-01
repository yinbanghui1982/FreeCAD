//
// File: computeperiodogram.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

// Include Files
#include "computeperiodogram.h"
#include "bsxfun.h"
#include "computeDFT.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                const ::coder::array<double, 1U> &win
//                double nfft
//                double Fs
//                ::coder::array<double, 1U> &Pxx
//                ::coder::array<double, 1U> &F
//                ::coder::array<creal_T, 1U> &RPxx
//                ::coder::array<double, 2U> &Fc
// Return Type  : void
//
namespace coder {
void computeperiodogram(const ::coder::array<double, 2U> &x,
                        const ::coder::array<double, 1U> &win, double nfft,
                        double Fs, ::coder::array<double, 1U> &Pxx,
                        ::coder::array<double, 1U> &F,
                        ::coder::array<creal_T, 1U> &RPxx,
                        ::coder::array<double, 2U> &Fc)
{
  array<creal_T, 1U> Xx;
  array<double, 1U> b_Fc;
  array<double, 1U> c_x;
  double b_win;
  int b_x;
  if (std::isnan(Fs)) {
    Fs = 6.2831853071795862;
  }
  b_x = x.size(1);
  c_x = x.reshape(b_x);
  bsxfun(c_x, win, b_Fc);
  computeDFT(b_Fc, nfft, Fs, Xx, F);
  Fc.set_size(0, 0);
  b_win = 0.0;
  b_x = win.size(0);
  for (int i{0}; i < b_x; i++) {
    b_win += win[i] * win[i];
  }
  Pxx.set_size(Xx.size(0));
  b_x = Xx.size(0);
  for (int i{0}; i < b_x; i++) {
    double Xx_im_tmp;
    double Xx_re;
    double Xx_re_tmp;
    Xx_re_tmp = Xx[i].re;
    Xx_im_tmp = Xx[i].im;
    Xx_re = Xx_re_tmp * Xx_re_tmp - Xx_im_tmp * -Xx_im_tmp;
    if (Xx_re_tmp * -Xx_im_tmp + Xx_im_tmp * Xx_re_tmp == 0.0) {
      Xx_re /= b_win;
    } else if (Xx_re == 0.0) {
      Xx_re = 0.0;
    } else {
      Xx_re /= b_win;
    }
    Pxx[i] = Xx_re;
  }
  RPxx.set_size(0);
  Fc.set_size(0, 0);
}

} // namespace coder

//
// File trailer for computeperiodogram.cpp
//
// [EOF]
//
