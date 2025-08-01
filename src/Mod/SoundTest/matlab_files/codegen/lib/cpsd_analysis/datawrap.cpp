//
// File: datawrap.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "datawrap.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Declarations
namespace cpsd
{
  static int div_s32(int numerator, int denominator);
}

// Function Definitions
//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
namespace cpsd
{
  static int div_s32(int numerator, int denominator)
  {
    unsigned int b_numerator;
    int quotient;
    if (denominator == 0) {
      if (numerator >= 0) {
        quotient = MAX_int32_T;
      } else {
        quotient = MIN_int32_T;
      }
    } else {
      unsigned int b_denominator;
      if (numerator < 0) {
        b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
      } else {
        b_numerator = static_cast<unsigned int>(numerator);
      }

      if (denominator < 0) {
        b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
      } else {
        b_denominator = static_cast<unsigned int>(denominator);
      }

      b_numerator /= b_denominator;
      if ((numerator < 0) != (denominator < 0)) {
        quotient = -static_cast<int>(b_numerator);
      } else {
        quotient = static_cast<int>(b_numerator);
      }
    }

    return quotient;
  }

  //
  // Arguments    : const ::coder::array<double, 1U> &x
  //                double nfft
  //                ::coder::array<double, 2U> &y
  // Return Type  : void
  //
  void datawrap(const ::coder::array<double, 1U> &x, double nfft, ::coder::array<
                double, 2U> &y)
  {
    int b_remainder;
    int k;
    int nFullPasses;
    int ny;
    int offset;
    ny = static_cast<int>(nfft);
    if (x.size(0) == 1) {
      y.set_size(1, (static_cast<int>(nfft)));
      offset = static_cast<int>(nfft);
      for (b_remainder = 0; b_remainder < offset; b_remainder++) {
        y[b_remainder] = 0.0;
      }
    } else {
      y.set_size((static_cast<int>(nfft)), 1);
      offset = static_cast<int>(nfft);
      for (b_remainder = 0; b_remainder < offset; b_remainder++) {
        y[b_remainder] = 0.0;
      }
    }

    nFullPasses = div_s32(x.size(0), static_cast<int>(nfft));
    offset = nFullPasses * static_cast<int>(nfft);
    b_remainder = (x.size(0) - offset) - 1;
    for (k = 0; k <= b_remainder; k++) {
      y[k] = x[offset + k];
    }

    b_remainder += 2;
    for (k = b_remainder; k <= ny; k++) {
      y[k - 1] = 0.0;
    }

    for (b_remainder = 0; b_remainder < nFullPasses; b_remainder++) {
      offset = b_remainder * static_cast<int>(nfft);
      for (k = 0; k < ny; k++) {
        y[k] = y[k] + x[offset + k];
      }
    }
  }
}

//
// File trailer for datawrap.cpp
//
// [EOF]
//
