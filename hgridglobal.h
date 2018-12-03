#ifndef HGRIDCTRLGLOBAL_H
#define HGRIDCTRLGLOBAL_H
#include <qglobal.h>

#if defined(WIN32) || defined(_WIN32)
    #if defined (GRIDCTRL_DLL)
        #define GRIDCTRL_EXPORT __declspec(dllexport)
    #else
        #define GRIDCTRL_EXPORT __declspec(dllimport)
    #endif
#else
    #define GRIDCTRL_EXPORT
#endif

#endif // SARIBBONGLOBAL_H
