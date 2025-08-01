//
// File: psdfreqvec.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>
#include <string.h>

// Function Declarations
namespace cpsd
{
  static double rt_remd_snf(double u0, double u1);
}

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
namespace cpsd
{
  static double rt_remd_snf(double u0, double u1)
  {
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
      y = rtNaN;
    } else if (rtIsInf(u1)) {
      y = u0;
    } else {
      double b_u1;
      if (u1 < 0.0) {
        b_u1 = ceil(u1);
      } else {
        b_u1 = floor(u1);
      }

      if ((u1 != 0.0) && (u1 != b_u1)) {
        b_u1 = fabs(u0 / u1);
        if (!(fabs(b_u1 - floor(b_u1 + 0.5)) > DBL_EPSILON * b_u1)) {
          y = 0.0 * u0;
        } else {
          y = fmod(u0, u1);
        }
      } else {
        y = fmod(u0, u1);
      }
    }

    return y;
  }

  //
  // Arguments    : double varargin_2
  //                double varargin_4
  //                ::coder::array<double, 1U> &w
  // Return Type  : void
  //
  void psdfreqvec(double varargin_2, double varargin_4, ::coder::array<double,
                  1U> &w)
  {
    ::coder::array<double, 2U> w1;
    double Fs1;
    double Nyq;
    double freq_res;
    double half_res;
    int i;
    int loop_ub;
    if (rtIsNaN(varargin_4)) {
      Fs1 = 6.2831853071795862;
    } else {
      Fs1 = varargin_4;
    }

    freq_res = Fs1 / varargin_2;
    if (rtIsNaN(varargin_2 - 1.0)) {
      w1.set_size(1, 1);
      w1[0] = rtNaN;
    } else if (rtIsInf(varargin_2 - 1.0) && (0.0 == varargin_2 - 1.0)) {
      w1.set_size(1, 1);
      w1[0] = rtNaN;
    } else {
      loop_ub = static_cast<int>(floor(varargin_2 - 1.0));
      w1.set_size(1, (loop_ub + 1));
      for (i = 0; i <= loop_ub; i++) {
        w1[i] = i;
      }
    }

    i = w1.size(0) * w1.size(1);
    w1.set_size(1, w1.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      w1[i] = freq_res * w1[i];
    }

    Nyq = Fs1 / 2.0;
    half_res = freq_res / 2.0;
    if (rt_remd_snf(varargin_2, 2.0) != 0.0) {
      double halfNPTS;
      halfNPTS = (varargin_2 + 1.0) / 2.0;
      w1[static_cast<int>(halfNPTS) - 1] = Nyq - half_res;
      w1[static_cast<int>(static_cast<unsigned int>(halfNPTS))] = Nyq + half_res;
    } else {
      w1[static_cast<int>(varargin_2 / 2.0 + 1.0) - 1] = Nyq;
    }

    w1[static_cast<int>(varargin_2) - 1] = Fs1 - freq_res;
    w.set_size(w1.size(1));
    loop_ub = w1.size(1);
    for (i = 0; i < loop_ub; i++) {
      w[i] = w1[i];
    }
  }
}

//
// File trailer for psdfreqvec.cpp
//
// [EOF]
//
