//
// File: computepsd.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "computepsd.h"
#include "cpsd_analysis_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &Sxx1
//                const ::coder::array<double, 2U> &w2
//                const char range[8]
//                double nfft
//                double Fs
//                ::coder::array<creal_T, 2U> &varargout_1
//                ::coder::array<double, 1U> &varargout_2
//                char varargout_3_data[]
//                int varargout_3_size[2]
// Return Type  : void
//
namespace cpsd
{
  void computepsd(const ::coder::array<creal_T, 2U> &Sxx1, const ::coder::array<
                  double, 2U> &w2, const char range[8], double nfft, double Fs, ::
                  coder::array<creal_T, 2U> &varargout_1, ::coder::array<double,
                  1U> &varargout_2, char varargout_3_data[], int
                  varargout_3_size[2])
  {
    static const char cv[10] = { 'r', 'a', 'd', '/', 's', 'a', 'm', 'p', 'l',
      'e' };

    static const char b[8] = { 'o', 'n', 'e', 's', 'i', 'd', 'e', 'd' };

    ::coder::array<creal_T, 2U> Sxx;
    ::coder::array<creal_T, 2U> y;
    ::coder::array<double, 2U> b_select;
    creal_T Sxx_unscaled_data[1];
    creal_T b_Sxx_unscaled_data[1];
    double r;
    int i;
    int loop_ub;
    int ret;
    ret = memcmp(&range[0], &b[0], 8);
    if (ret == 0) {
      if (rtIsNaN(nfft) || rtIsInf(nfft)) {
        r = rtNaN;
      } else {
        r = fmod(nfft, 2.0);
        if (r == 0.0) {
          r = 0.0;
        }
      }

      if (r == 1.0) {
        int b_loop_ub;
        int i1;
        int sizes_idx_0;
        signed char b_input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = (nfft + 1.0) / 2.0;
        if (rtIsNaN(r)) {
          b_select.set_size(1, 1);
          b_select[0] = rtNaN;
        } else {
          loop_ub = static_cast<int>(floor(r - 1.0));
          b_select.set_size(1, (loop_ub + 1));
          for (i = 0; i <= loop_ub; i++) {
            b_select[i] = static_cast<double>(i) + 1.0;
          }
        }

        loop_ub = Sxx1.size(1);
        Sxx.set_size(b_select.size(1), Sxx1.size(1));
        for (i = 0; i < loop_ub; i++) {
          b_loop_ub = b_select.size(1);
          for (i1 = 0; i1 < b_loop_ub; i1++) {
            Sxx[i1 + Sxx.size(0) * i] = Sxx1[(static_cast<int>(b_select[i1]) +
              Sxx1.size(0) * i) - 1];
          }
        }

        if (2 > b_select.size(1)) {
          i = 0;
          i1 = 0;
        } else {
          i = 1;
          i1 = b_select.size(1);
        }

        loop_ub = Sxx1.size(1) - 1;
        b_loop_ub = i1 - i;
        y.set_size(b_loop_ub, Sxx1.size(1));
        for (i1 = 0; i1 <= loop_ub; i1++) {
          for (sizes_idx_0 = 0; sizes_idx_0 < b_loop_ub; sizes_idx_0++) {
            ret = i + sizes_idx_0;
            y[sizes_idx_0 + y.size(0) * i1].re = 2.0 * Sxx[ret + Sxx.size(0) *
              i1].re;
            y[sizes_idx_0 + y.size(0) * i1].im = 2.0 * Sxx[ret + Sxx.size(0) *
              i1].im;
          }
        }

        if (Sxx1.size(1) != 0) {
          ret = Sxx1.size(1);
        } else if ((y.size(0) != 0) && (y.size(1) != 0)) {
          ret = 1;
        } else {
          if (Sxx1.size(1) > 0) {
            ret = Sxx1.size(1);
          } else {
            ret = 0;
          }

          if (y.size(1) > ret) {
            ret = 1;
          }
        }

        empty_non_axis_sizes = (ret == 0);
        if (empty_non_axis_sizes || (Sxx1.size(1) != 0)) {
          b_input_sizes_idx_0 = 1;
        } else {
          b_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((y.size(0) != 0) && (y.size(1) != 0))) {
          sizes_idx_0 = y.size(0);
        } else {
          sizes_idx_0 = 0;
        }

        loop_ub = Sxx1.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
          Sxx_unscaled_data[i] = Sxx[Sxx.size(0) * i];
        }

        Sxx.set_size((b_input_sizes_idx_0 + sizes_idx_0), ret);
        for (i = 0; i < ret; i++) {
          loop_ub = b_input_sizes_idx_0;
          for (i1 = 0; i1 < loop_ub; i1++) {
            Sxx[Sxx.size(0) * i] = Sxx_unscaled_data[b_input_sizes_idx_0 * i];
          }
        }

        for (i = 0; i < ret; i++) {
          for (i1 = 0; i1 < sizes_idx_0; i1++) {
            Sxx[(i1 + b_input_sizes_idx_0) + Sxx.size(0) * i] = y[i1 + y.size(0)
              * i];
          }
        }
      } else {
        int b_loop_ub;
        int i1;
        int input_sizes_idx_0;
        int sizes_idx_0;
        signed char b_input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = nfft / 2.0 + 1.0;
        if (rtIsNaN(r)) {
          b_select.set_size(1, 1);
          b_select[0] = rtNaN;
        } else {
          loop_ub = static_cast<int>(floor(r - 1.0));
          b_select.set_size(1, (loop_ub + 1));
          for (i = 0; i <= loop_ub; i++) {
            b_select[i] = static_cast<double>(i) + 1.0;
          }
        }

        loop_ub = Sxx1.size(1);
        Sxx.set_size(b_select.size(1), Sxx1.size(1));
        for (i = 0; i < loop_ub; i++) {
          b_loop_ub = b_select.size(1);
          for (i1 = 0; i1 < b_loop_ub; i1++) {
            Sxx[i1 + Sxx.size(0) * i] = Sxx1[(static_cast<int>(b_select[i1]) +
              Sxx1.size(0) * i) - 1];
          }
        }

        if (2 > b_select.size(1) - 1) {
          i = -1;
          i1 = -1;
        } else {
          i = 0;
          i1 = b_select.size(1) - 2;
        }

        loop_ub = Sxx1.size(1) - 1;
        input_sizes_idx_0 = i1 - i;
        y.set_size(input_sizes_idx_0, Sxx1.size(1));
        for (i1 = 0; i1 <= loop_ub; i1++) {
          for (sizes_idx_0 = 0; sizes_idx_0 < input_sizes_idx_0; sizes_idx_0++)
          {
            ret = (i + sizes_idx_0) + 1;
            y[sizes_idx_0 + y.size(0) * i1].re = 2.0 * Sxx[ret + Sxx.size(0) *
              i1].re;
            y[sizes_idx_0 + y.size(0) * i1].im = 2.0 * Sxx[ret + Sxx.size(0) *
              i1].im;
          }
        }

        if (Sxx1.size(1) != 0) {
          ret = Sxx1.size(1);
        } else if ((input_sizes_idx_0 != 0) && (Sxx1.size(1) != 0)) {
          ret = y.size(1);
        } else if (Sxx1.size(1) != 0) {
          ret = Sxx1.size(1);
        } else {
          if (Sxx1.size(1) > 0) {
            ret = Sxx1.size(1);
          } else {
            ret = 0;
          }

          if (y.size(1) > ret) {
            ret = 1;
          }

          if (Sxx1.size(1) > ret) {
            ret = Sxx1.size(1);
          }
        }

        empty_non_axis_sizes = (ret == 0);
        if (empty_non_axis_sizes || (Sxx1.size(1) != 0)) {
          b_input_sizes_idx_0 = 1;
        } else {
          b_input_sizes_idx_0 = 0;
        }

        if ((!empty_non_axis_sizes) && ((input_sizes_idx_0 == 0) || (Sxx1.size(1)
              == 0))) {
          input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || (Sxx1.size(1) != 0)) {
          sizes_idx_0 = 1;
        } else {
          sizes_idx_0 = 0;
        }

        loop_ub = Sxx1.size(1) - 1;
        b_loop_ub = Sxx1.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
          Sxx_unscaled_data[i] = Sxx[Sxx.size(0) * i];
        }

        for (i = 0; i <= b_loop_ub; i++) {
          b_Sxx_unscaled_data[i] = Sxx[(b_select.size(1) + Sxx.size(0) * i) - 1];
        }

        Sxx.set_size(((b_input_sizes_idx_0 + input_sizes_idx_0) + sizes_idx_0),
                     ret);
        for (i = 0; i < ret; i++) {
          loop_ub = b_input_sizes_idx_0;
          for (i1 = 0; i1 < loop_ub; i1++) {
            Sxx[Sxx.size(0) * i] = Sxx_unscaled_data[b_input_sizes_idx_0 * i];
          }
        }

        for (i = 0; i < ret; i++) {
          for (i1 = 0; i1 < input_sizes_idx_0; i1++) {
            Sxx[(i1 + b_input_sizes_idx_0) + Sxx.size(0) * i] = y[i1 +
              input_sizes_idx_0 * i];
          }
        }

        for (i = 0; i < ret; i++) {
          for (i1 = 0; i1 < sizes_idx_0; i1++) {
            Sxx[(b_input_sizes_idx_0 + input_sizes_idx_0) + Sxx.size(0) * i] =
              b_Sxx_unscaled_data[sizes_idx_0 * i];
          }
        }
      }

      varargout_2.set_size(b_select.size(1));
      loop_ub = b_select.size(1);
      for (i = 0; i < loop_ub; i++) {
        varargout_2[i] = w2[static_cast<int>(b_select[i]) - 1];
      }
    } else {
      Sxx.set_size(Sxx1.size(0), Sxx1.size(1));
      loop_ub = Sxx1.size(0) * Sxx1.size(1);
      for (i = 0; i < loop_ub; i++) {
        Sxx[i] = Sxx1[i];
      }

      varargout_2.set_size(w2.size(0));
      loop_ub = w2.size(0);
      for (i = 0; i < loop_ub; i++) {
        varargout_2[i] = w2[i];
      }
    }

    if (!rtIsNaN(Fs)) {
      varargout_1.set_size(Sxx.size(0), Sxx.size(1));
      loop_ub = Sxx.size(0) * Sxx.size(1);
      for (i = 0; i < loop_ub; i++) {
        double ai;
        r = Sxx[i].re;
        ai = Sxx[i].im;
        if (ai == 0.0) {
          varargout_1[i].re = r / Fs;
          varargout_1[i].im = 0.0;
        } else if (r == 0.0) {
          varargout_1[i].re = 0.0;
          varargout_1[i].im = ai / Fs;
        } else {
          varargout_1[i].re = r / Fs;
          varargout_1[i].im = ai / Fs;
        }
      }

      varargout_3_size[0] = 1;
      varargout_3_size[1] = 2;
      varargout_3_data[0] = 'H';
      varargout_3_data[1] = 'z';
    } else {
      varargout_1.set_size(Sxx.size(0), Sxx.size(1));
      loop_ub = Sxx.size(0) * Sxx.size(1);
      for (i = 0; i < loop_ub; i++) {
        double ai;
        r = Sxx[i].re;
        ai = Sxx[i].im;
        if (ai == 0.0) {
          varargout_1[i].re = r / 6.2831853071795862;
          varargout_1[i].im = 0.0;
        } else if (r == 0.0) {
          varargout_1[i].re = 0.0;
          varargout_1[i].im = ai / 6.2831853071795862;
        } else {
          varargout_1[i].re = r / 6.2831853071795862;
          varargout_1[i].im = ai / 6.2831853071795862;
        }
      }

      varargout_3_size[0] = 1;
      varargout_3_size[1] = 10;
      for (i = 0; i < 10; i++) {
        varargout_3_data[i] = cv[i];
      }
    }
  }
}

//
// File trailer for computepsd.cpp
//
// [EOF]
//
