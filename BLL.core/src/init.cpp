#include "StdAfx.h"
#include "BllCoreExport.h"
///////////////////////////////////////////////////////////////////////////////
#ifdef WIN32

#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

#endif


#ifdef __cplusplus
extern "C" {
#endif

void CORE_EXPORT InitCore()
{

}

#ifdef __cplusplus
}
#endif

