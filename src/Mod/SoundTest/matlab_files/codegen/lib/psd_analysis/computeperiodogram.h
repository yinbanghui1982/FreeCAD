//
// File: computeperiodogram.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

#ifndef COMPUTEPERIODOGRAM_H
#define COMPUTEPERIODOGRAM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void computeperiodogram(const ::coder::array<double, 2U> &x,
                        const ::coder::array<double, 1U> &win, double nfft,
                        double Fs, ::coder::array<double, 1U> &Pxx,
                        ::coder::array<double, 1U> &F,
                        ::coder::array<creal_T, 1U> &RPxx,
                        ::coder::array<double, 2U> &Fc);

}

#endif
//
// File trailer for computeperiodogram.h
//
// [EOF]
//
