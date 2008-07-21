#ifndef _WT_BLL_FRAMEWORK_EXPORT_H
#define _WT_BLL_FRAMEWORK_EXPORT_H

#ifdef FRAMEWORK_DLL
    #if defined WIN32
        #define FRAMEWORK_EXPORT __declspec(dllexport)
    #else
        #define FRAMEWORK_EXPORT
    #endif
#else
    #if defined WIN32
        #include "StdAfx.h"  // must be present to avoid inclusion order dependency in header files
        #include <windows.h>
        #define FRAMEWORK_EXPORT __declspec(dllimport)
    #else
        #define FRAMEWORK_EXPORT
    #endif
#endif


#endif //_WT_BLL_FRAMEWORK_EXPORT_H
