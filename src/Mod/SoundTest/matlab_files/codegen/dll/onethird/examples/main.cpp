//
// File: main.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:59:06
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
#include "onethird.h"
#include "onethird_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Declarations
static coder::array<double, 2U> argInit_1xUnbounded_real_T();

static coder::array<double, 1U> argInit_Unboundedx1_real_T();

static double argInit_real_T();

static void main_onethird();

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
static void main_onethird()
{
  coder::array<double, 2U> f;
  coder::array<double, 2U> t;
  coder::array<double, 1U> Ya_1;
  coder::array<double, 1U> x;
  double Ya_2[30];
  double fc[30];
  double nc;
  double nfft;
  // Initialize function 'onethird' input arguments.
  // Initialize function input argument 't'.
  t = argInit_1xUnbounded_real_T();
  // Initialize function input argument 'x'.
  x = argInit_Unboundedx1_real_T();
  // Call the entry-point 'onethird'.
  onethird(t, x, Ya_1, Ya_2, f, fc, &nfft, &nc);
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
  main_onethird();
  // Terminate the application.
  // You do not need to do this more than one time.
  onethird_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
