//
// File: welchparse.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//
#ifndef WELCHPARSE_H
#define WELCHPARSE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace cpsd
{
  struct cell_wrap_1;
  struct struct_T;
}

// Function Declarations
namespace cpsd
{
  namespace signal
  {
    namespace internal
    {
      namespace spectral
      {
        void welchparse(const cell_wrap_1 x1[2], double varargin_4, ::coder::
                        array<double, 1U> &x, double *M, boolean_T *isreal_x, ::
                        coder::array<double, 1U> &y, double *Ly, ::coder::array<
                        double, 1U> &win, double *noverlap, double *k, double *L,
                        struct_T *options);
      }
    }
  }
}

#endif

//
// File trailer for welchparse.h
//
// [EOF]
//
