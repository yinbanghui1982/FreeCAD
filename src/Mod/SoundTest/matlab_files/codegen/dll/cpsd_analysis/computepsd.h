//
// File: computepsd.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

#ifndef COMPUTEPSD_H
#define COMPUTEPSD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void computepsd(const ::coder::array<creal_T, 2U> &Sxx1,
                const ::coder::array<double, 2U> &w2, const char range[8],
                double nfft, double Fs,
                ::coder::array<creal_T, 2U> &varargout_1,
                ::coder::array<double, 1U> &varargout_2,
                char varargout_3_data[], int varargout_3_size[2]);

}

#endif
//
// File trailer for computepsd.h
//
// [EOF]
//
