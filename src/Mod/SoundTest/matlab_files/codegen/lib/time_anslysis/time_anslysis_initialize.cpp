//
// File: time_anslysis_initialize.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:59:39
//

// Include Files
#include "time_anslysis_initialize.h"
#include "rt_nonfinite.h"
#include "time_anslysis_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void time_anslysis_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_time_anslysis = true;
}

//
// File trailer for time_anslysis_initialize.cpp
//
// [EOF]
//
