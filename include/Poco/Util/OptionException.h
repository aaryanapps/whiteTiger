//
// OptionException.h
//
// $Id: //poco/svn/Util/include/Poco/Util/OptionException.h#1 $
//
// Library: Util
// Package: Options
// Module:  OptionException
//
// Definition of the OptionException class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Util_OptionException_INCLUDED
#define Util_OptionException_INCLUDED


#include "Poco/Util/Util.h"
#include "Poco/Exception.h"


namespace Poco {
namespace Util {


POCO_DECLARE_EXCEPTION(Util_API, OptionException, Poco::DataException)
POCO_DECLARE_EXCEPTION(Util_API, UnknownOptionException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, AmbiguousOptionException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, MissingOptionException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, MissingArgumentException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, InvalidArgumentException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, UnexpectedArgumentException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, IncompatibleOptionsException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, DuplicateOptionException, OptionException)
POCO_DECLARE_EXCEPTION(Util_API, EmptyOptionException, OptionException)


} } // namespace Poco::Util


#endif // Util_OptionException_INCLUDED
