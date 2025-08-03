//
// File: pingpu_spec.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Aug-2025 02:00:28
//

#ifndef PINGPU_SPEC_H
#define PINGPU_SPEC_H

// Include Files
#ifdef PINGPU_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define PINGPU_DLL_EXPORT __declspec(dllimport)
#else
#define PINGPU_DLL_EXPORT __attribute__((visibility("default")))
#endif
#elif defined(BUILDING_PINGPU)
#if defined(_MSC_VER) || defined(__LCC__)
#define PINGPU_DLL_EXPORT __declspec(dllexport)
#else
#define PINGPU_DLL_EXPORT __attribute__((visibility("default")))
#endif
#else
#define PINGPU_DLL_EXPORT
#endif

#endif
//
// File trailer for pingpu_spec.h
//
// [EOF]
//
