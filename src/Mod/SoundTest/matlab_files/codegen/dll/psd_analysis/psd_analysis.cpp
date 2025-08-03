//
// File: psd_analysis.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:01:53
//

// Include Files
#include "psd_analysis.h"
#include "computeperiodogram.h"
#include "psd_analysis_data.h"
#include "psd_analysis_initialize.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const coder::array<double, 1U> &noise
//                double N
//                double Fs
//                coder::array<double, 2U> &psdestx
//                coder::array<double, 1U> &Fxx
// Return Type  : void
//
void psd_analysis(const coder::array<double, 1U> &noise, double N, double Fs,
                  coder::array<double, 2U> &psdestx,
                  coder::array<double, 1U> &Fxx)
{
  static const char b[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  static const char options_range[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  coder::array<creal_T, 1U> b_Sxx;
  coder::array<double, 2U> b_select;
  coder::array<double, 2U> wc;
  coder::array<double, 1U> Sxx;
  coder::array<double, 1U> win1;
  int eint;
  int i;
  int ret;
  if (!isInitialized_psd_analysis) {
    psd_analysis_initialize();
  }
  ret = noise.size(0);
  win1.set_size(noise.size(0));
  for (i = 0; i < ret; i++) {
    win1[i] = 1.0;
  }
  frexp(static_cast<double>(noise.size(0)), &eint);
  if (noise.size(0) == 0) {
    win1.set_size(0);
  }
  coder::computeperiodogram(noise, win1, N, Fs, Sxx, Fxx, b_Sxx, wc);
  ret = memcmp(&options_range[0], &b[0], 8);
  if (ret == 0) {
    double r;
    if (std::isnan(N) || std::isinf(N)) {
      r = rtNaN;
    } else if (N == 0.0) {
      r = 0.0;
    } else {
      r = std::fmod(N, 2.0);
      if (r == 0.0) {
        r = 0.0;
      } else if (N < 0.0) {
        r += 2.0;
      }
    }
    if (r == 1.0) {
      r = (N + 1.0) / 2.0;
      if (std::isnan(r)) {
        b_select.set_size(1, 1);
        b_select[0] = rtNaN;
      } else if (r < 1.0) {
        b_select.set_size(1, 0);
      } else {
        b_select.set_size(1, static_cast<int>(r - 1.0) + 1);
        ret = static_cast<int>(r - 1.0);
        for (i = 0; i <= ret; i++) {
          b_select[i] = static_cast<double>(i) + 1.0;
        }
      }
      win1.set_size(b_select.size(1));
      ret = b_select.size(1);
      for (i = 0; i < ret; i++) {
        win1[i] = Sxx[static_cast<int>(b_select[i]) - 1];
      }
      if (b_select.size(1) < 2) {
        i = 0;
        eint = 0;
      } else {
        i = 1;
        eint = b_select.size(1);
      }
      r = Sxx[static_cast<int>(b_select[0]) - 1];
      ret = eint - i;
      Sxx.set_size(ret + 1);
      Sxx[0] = r;
      for (eint = 0; eint < ret; eint++) {
        Sxx[eint + 1] = 2.0 * win1[i + eint];
      }
    } else {
      double c_Sxx;
      r = N / 2.0 + 1.0;
      if (std::isnan(r)) {
        b_select.set_size(1, 1);
        b_select[0] = rtNaN;
      } else if (r < 1.0) {
        b_select.set_size(1, 0);
      } else {
        b_select.set_size(1, static_cast<int>(r - 1.0) + 1);
        ret = static_cast<int>(r - 1.0);
        for (i = 0; i <= ret; i++) {
          b_select[i] = static_cast<double>(i) + 1.0;
        }
      }
      win1.set_size(b_select.size(1));
      ret = b_select.size(1);
      for (i = 0; i < ret; i++) {
        win1[i] = Sxx[static_cast<int>(b_select[i]) - 1];
      }
      if (b_select.size(1) - 1 < 2) {
        i = 0;
        eint = 1;
      } else {
        i = 1;
        eint = b_select.size(1);
      }
      r = Sxx[static_cast<int>(b_select[0]) - 1];
      c_Sxx = Sxx[static_cast<int>(b_select[b_select.size(1) - 1]) - 1];
      ret = eint - i;
      Sxx.set_size(ret + 1);
      Sxx[0] = r;
      for (eint = 0; eint <= ret - 2; eint++) {
        Sxx[eint + 1] = 2.0 * win1[i + eint];
      }
      Sxx[ret] = c_Sxx;
    }
    win1.set_size(b_select.size(1));
    ret = b_select.size(1);
    for (i = 0; i < ret; i++) {
      win1[i] = Fxx[static_cast<int>(b_select[i]) - 1];
    }
    Fxx.set_size(win1.size(0));
    ret = win1.size(0);
    for (i = 0; i < ret; i++) {
      Fxx[i] = win1[i];
    }
  }
  if (!std::isnan(Fs)) {
    ret = Sxx.size(0);
    for (i = 0; i < ret; i++) {
      Sxx[i] = Sxx[i] / Fs;
    }
  } else {
    ret = Sxx.size(0);
    for (i = 0; i < ret; i++) {
      Sxx[i] = Sxx[i] / 6.2831853071795862;
    }
  }
  psdestx.set_size(Sxx.size(0), 1);
  ret = Sxx.size(0);
  for (i = 0; i < ret; i++) {
    psdestx[i] = Sxx[i];
  }
  ret = psdestx.size(0);
  for (eint = 0; eint < ret; eint++) {
    psdestx[eint] = std::log10(psdestx[eint]);
  }
  ret = psdestx.size(0);
  for (i = 0; i < ret; i++) {
    psdestx[i] = (10.0 * psdestx[i] + 300.0) - 300.0;
  }
}

//
// File trailer for psd_analysis.cpp
//
// [EOF]
//
