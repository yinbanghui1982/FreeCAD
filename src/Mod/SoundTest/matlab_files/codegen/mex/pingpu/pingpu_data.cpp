//
// pingpu_data.cpp
//
// Code generation for function 'pingpu_data'
//

// Include files
#include "pingpu_data.h"
#include "rt_nonfinite.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                // bFirstTime
    false,                                               // bInitialized
    131627U,                                             // fVersionInfo
    nullptr,                                             // fErrorFunction
    "pingpu",                                            // fFunctionName
    nullptr,                                             // fRTCallStack
    false,                                               // bDebugMode
    {497312255U, 2566552405U, 2553285182U, 2715458501U}, // fSigWrd
    nullptr                                              // fSigMem
};

emlrtRSInfo o_emlrtRSI{
    33,                           // lineNo
    "applyScalarFunctionInPlace", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunctionInPlace.m" // pathName
};

emlrtRSInfo p_emlrtRSI{
    20,                               // lineNo
    "eml_int_forloop_overflow_check", // fcnName
    "D:\\Program "
    "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_"
    "overflow_check.m" // pathName
};

emlrtRTEInfo
    h_emlrtRTEI{
        28,      // lineNo
        9,       // colNo
        "colon", // fName
        "D:\\Program "
        "Files\\MATLAB\\R2022b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" // pName
    };

covrtInstance emlrtCoverageInstance;

// End of code generation (pingpu_data.cpp)
