//
// File: main.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2025 15:18:11
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "main.h"
#include "cpsd_analysis.h"
#include "cpsd_analysis_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Declarations
static coder::array<double, 2U> argInit_1xUnbounded_real_T();
static double argInit_real_T();
static void main_cpsd_analysis();

// Function Definitions
//
// Arguments    : void
// Return Type  : coder::array<double, 2U>
//
static coder::array<double, 2U> argInit_1xUnbounded_real_T()
{
  coder::array<double, 2U> result;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(1, 2);

  // Loop over the array to initialize each element.
  for (int idx0 = 0; idx0 < 1; idx0++) {
    for (int idx1 = 0; idx1 < result.size(1); idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx1] = argInit_real_T();
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_cpsd_analysis()
{
  coder::array<double, 2U> Pxy2;
  coder::array<double, 2U> arg2;
  coder::array<double, 2U> x_tmp;
  coder::array<double, 1U> f;

  // Initialize function 'cpsd_analysis' input arguments.
  // Initialize function input argument 'x'.
  x_tmp = argInit_1xUnbounded_real_T();

  // Initialize function input argument 'y'.
  // Call the entry-point 'cpsd_analysis'.
  cpsd::cpsd_analysis(x_tmp, x_tmp, argInit_real_T(), Pxy2, arg2, f);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. 
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_cpsd_analysis();

  // Terminate the application.
  // You do not need to do this more than one time.
  cpsd::cpsd_analysis_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
