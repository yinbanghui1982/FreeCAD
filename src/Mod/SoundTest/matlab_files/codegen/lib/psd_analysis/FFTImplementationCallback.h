//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
namespace fft {
class FFTImplementationCallback {
public:
  static void dobluesteinfft(const ::coder::array<double, 1U> &x, int n2blue,
                             int nfft, const ::coder::array<double, 2U> &costab,
                             const ::coder::array<double, 2U> &sintab,
                             const ::coder::array<double, 2U> &sintabinv,
                             ::coder::array<creal_T, 1U> &y);
  static void doHalfLengthRadix2(const ::coder::array<double, 1U> &x,
                                 ::coder::array<creal_T, 1U> &y,
                                 int unsigned_nRows,
                                 const ::coder::array<double, 2U> &costab,
                                 const ::coder::array<double, 2U> &sintab);

protected:
  static void r2br_r2dit_trig_impl(const ::coder::array<creal_T, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<double, 2U> &costab,
                                   const ::coder::array<double, 2U> &sintab,
                                   ::coder::array<creal_T, 1U> &y);
  static void
  doHalfLengthBluestein(const ::coder::array<double, 1U> &x,
                        ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
                        int nfft, const ::coder::array<creal_T, 1U> &wwc,
                        const ::coder::array<double, 2U> &costab,
                        const ::coder::array<double, 2U> &sintab,
                        const ::coder::array<double, 2U> &costabinv,
                        const ::coder::array<double, 2U> &sintabinv);
};

} // namespace fft
} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
