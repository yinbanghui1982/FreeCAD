/*
 * File: _coder_time_anslysis_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 22-Jul-2025 15:59:39
 */

#ifndef _CODER_TIME_ANSLYSIS_API_H
#define _CODER_TIME_ANSLYSIS_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void time_anslysis(emxArray_real_T *sig, real_T *rms2, real_T *mean2, real_T
                     *max_abs, real_T *mean_abs, real_T *rms_abs, real_T *var2,
                     real_T *std2, real_T *spl, real_T *ppv);
  void time_anslysis_api(const mxArray * const prhs[1], int32_T nlhs, const
    mxArray *plhs[9]);
  void time_anslysis_atexit(void);
  void time_anslysis_initialize(void);
  void time_anslysis_terminate(void);
  void time_anslysis_xil_shutdown(void);
  void time_anslysis_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_time_anslysis_api.h
 *
 * [EOF]
 */
