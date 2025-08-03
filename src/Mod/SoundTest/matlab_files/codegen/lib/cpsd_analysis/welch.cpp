//
// File: welch.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Dec-2023 07:28:04
//

// Include Files
#include "welch.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : coder::array<creal_T, 2U> &in1
//                const coder::array<double, 1U> &in2
// Return Type  : void
//
void binary_expand_op(coder::array<creal_T, 2U> &in1,
                      const coder::array<double, 1U> &in2)
{
  coder::array<creal_T, 2U> b_in1;
  int in2_idx_0;
  int loop_ub;
  int stride_0_0;
  in2_idx_0 = in2.size(0);
  b_in1.set_size(in2_idx_0, in1.size(1));
  stride_0_0 = (in1.size(0) != 1);
  loop_ub = in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    for (int i1{0}; i1 < in2_idx_0; i1++) {
      int i2;
      i2 = i1 * stride_0_0;
      b_in1[i1].re = in1[i2].re + in2[i1];
      b_in1[i1].im = in1[i2].im;
    }
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in2_idx_0 = b_in1.size(0);
    for (int i1{0}; i1 < in2_idx_0; i1++) {
      in1[i1] = b_in1[i1];
    }
  }
}

//
// Arguments    : coder::array<creal_T, 2U> &in1
//                const coder::array<creal_T, 1U> &in2
// Return Type  : void
//
void binary_expand_op(coder::array<creal_T, 2U> &in1,
                      const coder::array<creal_T, 1U> &in2)
{
  coder::array<creal_T, 2U> b_in1;
  int in2_idx_0;
  int loop_ub;
  int stride_0_0;
  in2_idx_0 = in2.size(0);
  b_in1.set_size(in2_idx_0, in1.size(1));
  stride_0_0 = (in1.size(0) != 1);
  loop_ub = in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    for (int i1{0}; i1 < in2_idx_0; i1++) {
      int i2;
      i2 = i1 * stride_0_0;
      b_in1[i1].re = in1[i2].re + in2[i1].re;
      b_in1[i1].im = in1[i2].im + in2[i1].im;
    }
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in2_idx_0 = b_in1.size(0);
    for (int i1{0}; i1 < in2_idx_0; i1++) {
      in1[i1] = b_in1[i1];
    }
  }
}

//
// File trailer for welch.cpp
//
// [EOF]
//
