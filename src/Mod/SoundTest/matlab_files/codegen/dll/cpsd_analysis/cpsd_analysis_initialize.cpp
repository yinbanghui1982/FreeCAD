//
// File: cpsd_analysis_initialize.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:52:41
//

// Include Files
#include "cpsd_analysis_initialize.h"
#include "cpsd_analysis_data.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void cpsd_analysis_initialize()
{
  omp_init_nest_lock(&cpsd_analysis_nestLockGlobal);
  isInitialized_cpsd_analysis = true;
}

//
// File trailer for cpsd_analysis_initialize.cpp
//
// [EOF]
//
