
#ifndef _WT_CORE_STDAFX_H
#define _WT_CORE_STDAFX_H
/*
#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>
*/

#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x400
#endif

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#undef GetObject
#pragma warning( disable: 4251 )
#endif

#endif
