//
// File: minOrMax.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

// Include Files
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
namespace coder {
namespace internal {
double maximum(const ::coder::array<double, 2U> &x)
{
  double ex;
  int last;
  last = x.size(1);
  if (x.size(1) <= 2) {
    if (x.size(1) == 1) {
      ex = x[0];
    } else if ((x[0] < x[x.size(1) - 1]) ||
               (std::isnan(x[0]) && (!std::isnan(x[x.size(1) - 1])))) {
      ex = x[x.size(1) - 1];
    } else {
      ex = x[0];
    }
  } else {
    int idx;
    int k;
    if (!std::isnan(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x[0];
    } else {
      ex = x[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

} // namespace internal
} // namespace coder

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
