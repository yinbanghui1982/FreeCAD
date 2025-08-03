//
// File: psdfreqvec.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

// Include Files
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cfloat>
#include <cmath>
#include <string.h>

// Function Declarations
static double rt_remd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

//
// Arguments    : double varargin_2
//                double varargin_4
//                ::coder::array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void psdfreqvec(double varargin_2, double varargin_4,
                ::coder::array<double, 1U> &w)
{
  array<double, 2U> w1;
  double Fs1;
  double Nyq;
  double freq_res;
  double half_res;
  int loop_ub;
  if (std::isnan(varargin_4)) {
    Fs1 = 6.2831853071795862;
  } else {
    Fs1 = varargin_4;
  }
  freq_res = Fs1 / varargin_2;
  if (std::isnan(varargin_2 - 1.0)) {
    w1.set_size(1, 1);
    w1[0] = rtNaN;
  } else {
    w1.set_size(1, static_cast<int>(varargin_2 - 1.0) + 1);
    loop_ub = static_cast<int>(varargin_2 - 1.0);
    for (int i{0}; i <= loop_ub; i++) {
      w1[i] = i;
    }
  }
  w1.set_size(1, w1.size(1));
  loop_ub = w1.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
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
  for (int i{0}; i < loop_ub; i++) {
    w[i] = w1[i];
  }
}

} // namespace coder

//
// File trailer for psdfreqvec.cpp
//
// [EOF]
//
