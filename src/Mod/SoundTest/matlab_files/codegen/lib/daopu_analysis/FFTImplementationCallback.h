//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Dec-2023 13:53:49
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
class FFTImplementationCallback {
public:
  static void get_algo_sizes(int nfft, boolean_T useRadix2, int *n2blue,
                             int *nRows);
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
  static void doHalfLengthRadix2(const ::coder::array<double, 1U> &x,
                                 ::coder::array<creal_T, 1U> &y,
                                 int unsigned_nRows,
                                 const ::coder::array<double, 2U> &costab,
                                 const ::coder::array<double, 2U> &sintab);
  static void
  b_doHalfLengthBluestein(const ::coder::array<double, 1U> &x,
                          ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
                          int nfft, const ::coder::array<creal_T, 1U> &wwc,
                          const ::coder::array<double, 2U> &costab,
                          const ::coder::array<double, 2U> &sintab,
                          const ::coder::array<double, 2U> &costabinv,
                          const ::coder::array<double, 2U> &sintabinv);

protected:
  static void generate_twiddle_tables(int nRows,
                                      ::coder::array<double, 2U> &costab,
                                      ::coder::array<double, 2U> &sintab,
                                      ::coder::array<double, 2U> &sintabinv);
  static void
  get_half_twiddle_tables(const ::coder::array<double, 2U> &costab,
                          const ::coder::array<double, 2U> &sintab,
                          const ::coder::array<double, 2U> &costabinv,
                          const ::coder::array<double, 2U> &sintabinv,
                          ::coder::array<double, 2U> &hcostab,
                          ::coder::array<double, 2U> &hsintab,
                          ::coder::array<double, 2U> &hcostabinv,
                          ::coder::array<double, 2U> &hsintabinv);
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
