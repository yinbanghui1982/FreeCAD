//
// File: auto_corr_analysis_initialize.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:06:11
//

// Include Files
#include "auto_corr_analysis_initialize.h"
#include "auto_corr_analysis_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace corr
{
  void auto_corr_analysis_initialize()
  {
    rt_InitInfAndNaN();
    isInitialized_auto_corr_analysis = true;
  }
}

//
// File trailer for auto_corr_analysis_initialize.cpp
//
// [EOF]
//
