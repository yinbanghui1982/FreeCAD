//
// File: psd_analysis_terminate.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Dec-2023 12:30:03
//

// Include Files
#include "psd_analysis_terminate.h"
#include "psd_analysis_data.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void psd_analysis_terminate()
{
  omp_destroy_nest_lock(&psd_analysis_nestLockGlobal);
  isInitialized_psd_analysis = false;
}

//
// File trailer for psd_analysis_terminate.cpp
//
// [EOF]
//
