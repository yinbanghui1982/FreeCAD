//
// File: bsxfun.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

// Include Files
#include "bsxfun.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                const ::coder::array<double, 1U> &b
//                ::coder::array<double, 1U> &c
// Return Type  : void
//
namespace coder {
void bsxfun(const ::coder::array<double, 1U> &a,
            const ::coder::array<double, 1U> &b, ::coder::array<double, 1U> &c)
{
  int acoef;
  int csz_idx_0;
  int u0;
  u0 = b.size(0);
  acoef = a.size(0);
  if (u0 <= acoef) {
    acoef = u0;
  }
  if (b.size(0) == 1) {
    csz_idx_0 = a.size(0);
  } else if (a.size(0) == 1) {
    csz_idx_0 = b.size(0);
  } else if (a.size(0) == b.size(0)) {
    csz_idx_0 = a.size(0);
  } else {
    csz_idx_0 = acoef;
  }
  u0 = b.size(0);
  acoef = a.size(0);
  if (u0 <= acoef) {
    acoef = u0;
  }
  if (b.size(0) == 1) {
    acoef = a.size(0);
  } else if (a.size(0) == 1) {
    acoef = b.size(0);
  } else if (a.size(0) == b.size(0)) {
    acoef = a.size(0);
  }
  c.set_size(acoef);
  if (csz_idx_0 != 0) {
    int bcoef;
    acoef = (a.size(0) != 1);
    bcoef = (b.size(0) != 1);
    u0 = csz_idx_0 - 1;
    for (csz_idx_0 = 0; csz_idx_0 <= u0; csz_idx_0++) {
      c[csz_idx_0] = a[acoef * csz_idx_0] * b[bcoef * csz_idx_0];
    }
  }
}

} // namespace coder

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
