#ifndef __WT_BLL_CORE_EXPORT_H__
#define __WT_BLL_CORE_EXPORT_H__

#ifdef CORE_DLL
    #if defined WIN32
        #define CORE_EXPORT __declspec(dllexport)
    #else
        #define CORE_EXPORT
    #endif
#else
    #if defined WIN32
        #define CORE_EXPORT __declspec(dllimport)
    #else
        #define CORE_EXPORT
    #endif
#endif

#endif // __WT_BLL_CORE_EXPORT_H__