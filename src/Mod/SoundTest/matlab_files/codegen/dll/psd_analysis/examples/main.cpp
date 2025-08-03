//
// File: main.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:01:53
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
#include "psd_analysis.h"
#include "psd_analysis_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Declarations
static coder::array<double, 1U> argInit_Unboundedx1_real_T();

static double argInit_real_T();

static void main_psd_analysis();

// Function Definitions
//
// Arguments    : void
// Return Type  : coder::array<double, 1U>
//
static coder::array<double, 1U> argInit_Unboundedx1_real_T()
{
  coder::array<double, 1U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(2);
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < result.size(0); idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
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
static void main_psd_analysis()
{
  coder::array<double, 2U> psdestx;
  coder::array<double, 1U> Fxx;
  coder::array<double, 1U> noise;
  double N_tmp;
  // Initialize function 'psd_analysis' input arguments.
  // Initialize function input argument 'noise'.
  noise = argInit_Unboundedx1_real_T();
  N_tmp = argInit_real_T();
  // Call the entry-point 'psd_analysis'.
  psd_analysis(noise, N_tmp, N_tmp, psdestx, Fxx);
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
  main_psd_analysis();
  // Terminate the application.
  // You do not need to do this more than one time.
  psd_analysis_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
