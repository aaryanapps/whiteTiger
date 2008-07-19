#ifndef _WT_DATATYPES_H__
#define _WT_DATATYPES_H__

#include <string>
#include <vector>
#include <map>

#if defined(__CYGWIN__) || defined (__sun__)
    typedef char int8_t;
#else
    typedef signed char int8_t;
#endif // __CYGWIN__ || __sun__

typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

/*
typedef char   char_t;
typedef short  short_t;
typedef long   long_t;
typedef int    int_t;

typedef unsigned char   uchar_t;
typedef unsigned short  ushort_t;
typedef unsigned long   ulong_t;
typedef unsigned int    uint_t;
*/

//typedef float   float_t;
//typedef double  double_t;

#if defined (__GNU__)
    #include <sys/types.h>
    typedef signed long long int64_t;
    typedef unsigned long long uint64_t;
#else
    typedef signed long long int64_t;
    typedef unsigned long long uint64_t;
#endif // __GNU__

#endif //_WT_DATATYPES_H__
