//
// File: main.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Nov-2023 22:00:14
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
#include "fft_test_fun.h"
#include "fft_test_fun_terminate.h"

// Function Declarations
static void argInit_1x1000_real32_T(float result[1000]);

static float argInit_real32_T();

static void main_fft_test_fun();

// Function Definitions
//
// Arguments    : float result[1000]
// Return Type  : void
//
static void argInit_1x1000_real32_T(float result[1000])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 1000; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_fft_test_fun()
{
  float b_fv[1000];
  float y[1000];
  // Initialize function 'fft_test_fun' input arguments.
  // Initialize function input argument 'x'.
  // Call the entry-point 'fft_test_fun'.
  argInit_1x1000_real32_T(b_fv);
  fft_test_fun(b_fv, y);
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
  main_fft_test_fun();
  // Terminate the application.
  // You do not need to do this more than one time.
  fft_test_fun_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
