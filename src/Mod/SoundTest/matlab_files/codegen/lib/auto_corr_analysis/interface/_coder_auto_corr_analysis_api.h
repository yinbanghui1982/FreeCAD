/*
 * File: _coder_auto_corr_analysis_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 22-Jul-2025 15:06:11
 */

#ifndef _CODER_AUTO_CORR_ANALYSIS_API_H
#define _CODER_AUTO_CORR_ANALYSIS_API_H

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
  void auto_corr_analysis(emxArray_real_T *x, real_T dt, emxArray_real_T *c,
    emxArray_real_T *lags2);
  void auto_corr_analysis_api(const mxArray * const prhs[2], int32_T nlhs, const
    mxArray *plhs[2]);
  void auto_corr_analysis_atexit(void);
  void auto_corr_analysis_initialize(void);
  void auto_corr_analysis_terminate(void);
  void auto_corr_analysis_xil_shutdown(void);
  void auto_corr_analysis_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_auto_corr_analysis_api.h
 *
 * [EOF]
 */
