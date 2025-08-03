//
// File: cpsd_analysis_terminate.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

// Include Files
#include "cpsd_analysis_terminate.h"
#include "cpsd_analysis_data.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void cpsd_analysis_terminate()
{
  omp_destroy_nest_lock(&cpsd_analysis_nestLockGlobal);
  isInitialized_cpsd_analysis = false;
}

//
// File trailer for cpsd_analysis_terminate.cpp
//
// [EOF]
//
