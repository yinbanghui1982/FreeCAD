//
// File: main.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:03:39
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "rt_nonfinite.h"
#include "time_anslysis.h"
#include "time_anslysis_terminate.h"
#include "coder_array.h"

// Function Declarations
static coder::array<double, 2U> argInit_1xUnbounded_real_T();

static double argInit_real_T();

static void main_time_anslysis();

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
  for (int idx0{0}; idx0 < 1; idx0++) {
    for (int idx1{0}; idx1 < result.size(1); idx1++) {
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
static void main_time_anslysis()
{
  coder::array<double, 2U> sig;
  double max_abs;
  double mean2;
  double mean_abs;
  double ppv;
  double rms2;
  double rms_abs;
  double spl;
  double std2;
  double var2;
  // Initialize function 'time_anslysis' input arguments.
  // Initialize function input argument 'sig'.
  sig = argInit_1xUnbounded_real_T();
  // Call the entry-point 'time_anslysis'.
  time_anslysis(sig, &rms2, &mean2, &max_abs, &mean_abs, &rms_abs, &var2, &std2,
                &spl, &ppv);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_time_anslysis();
  // Terminate the application.
  // You do not need to do this more than one time.
  time_anslysis_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
