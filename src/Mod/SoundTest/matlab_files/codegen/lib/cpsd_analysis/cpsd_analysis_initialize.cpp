//
// File: cpsd_analysis_initialize.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

// Include Files
#include "cpsd_analysis_initialize.h"
#include "cpsd_analysis_data.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace cpsd
{
  void cpsd_analysis_initialize()
  {
    rt_InitInfAndNaN();
    isInitialized_cpsd_analysis = true;
  }
}

//
// File trailer for cpsd_analysis_initialize.cpp
//
// [EOF]
//
