#ifndef _WT_GLOBALS_H__
#define _WT_GLOBALS_H__

#include "DataTypes.h"
#include <iostream>
#include <sstream>
#include <cctype>

//#include <algorithm>

// A utility functor to compare any two values. Will work for any
// type that support "==" operator

template <typename T>
struct ValueCompareFunctor : public std::unary_function<T, bool>
{
  bool operator()(const T &other)
  {
      if (m_val == other)
        return true ;
      return false ;
  }
  ValueCompareFunctor(const T& thisVal)
  {
      m_val = thisVal ;
  }
  T m_val ;
} ;


#define REGISTER_CREATOR(id,fname) \
	wt::framework::CWtObjectRegistrar::Instance().RegisterCreator(id , fname)


#endif //_WT_GLOBALS_H__
