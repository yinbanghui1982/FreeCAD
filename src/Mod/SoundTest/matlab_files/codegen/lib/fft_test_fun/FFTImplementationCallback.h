//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Nov-2023 22:00:14
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class FFTImplementationCallback {
public:
  static void doHalfLengthBluestein(const float x[1000], creal32_T y[1000],
                                    const creal32_T wwc[999],
                                    const float costabinv[1025],
                                    const float sintabinv[1025]);
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
