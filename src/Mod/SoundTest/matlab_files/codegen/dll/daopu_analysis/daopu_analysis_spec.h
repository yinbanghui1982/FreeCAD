//
// File: daopu_analysis_spec.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 01:57:41
//

#ifndef DAOPU_ANALYSIS_SPEC_H
#define DAOPU_ANALYSIS_SPEC_H

// Include Files
#ifdef DAOPU_ANALYSIS_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define DAOPU_ANALYSIS_DLL_EXPORT __declspec(dllimport)
#else
#define DAOPU_ANALYSIS_DLL_EXPORT __attribute__((visibility("default")))
#endif
#elif defined(BUILDING_DAOPU_ANALYSIS)
#if defined(_MSC_VER) || defined(__LCC__)
#define DAOPU_ANALYSIS_DLL_EXPORT __declspec(dllexport)
#else
#define DAOPU_ANALYSIS_DLL_EXPORT __attribute__((visibility("default")))
#endif
#else
#define DAOPU_ANALYSIS_DLL_EXPORT
#endif

#endif
//
// File trailer for daopu_analysis_spec.h
//
// [EOF]
//
