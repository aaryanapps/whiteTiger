//
// PrivateKeyFactoryMgr.h
//
// $Id: //poco/svn/NetSSL_OpenSSL/include/Poco/Net/PrivateKeyFactoryMgr.h#1 $
//
// Library: NetSSL_OpenSSL
// Package: SSLCore
// Module:  PrivateKeyFactoryMgr
//
// Definition of the PrivateKeyFactoryMgr class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef NetSSL_PrivateKeyFactoryMgr_INCLUDED
#define NetSSL_PrivateKeyFactoryMgr_INCLUDED


#include "Poco/Net/NetSSL.h"
#include "Poco/Net/PrivateKeyFactory.h"
#include "Poco/SharedPtr.h"
#include <map>


namespace Poco {
namespace Net {


class NetSSL_API PrivateKeyFactoryMgr
	/// A PrivateKeyFactoryMgr manages all existing PrivateKeyFactories.
{
public:
	typedef std::map<std::string, Poco::SharedPtr<PrivateKeyFactory> > FactoriesMap;
	
	PrivateKeyFactoryMgr();
		/// Creates the PrivateKeyFactoryMgr.

	~PrivateKeyFactoryMgr();
		/// Destroys the PrivateKeyFactoryMgr.

	void setFactory(const std::string& name, PrivateKeyFactory* pFactory);
		/// Registers the factory. Class takes ownership of the pointer.
		/// If a factory with the same name already exists, an exception is thrown.

	bool hasFactory(const std::string& name) const;
		/// Returns true if for the given name a factory is already registered
	
	const PrivateKeyFactory* getFactory(const std::string& name) const;
		/// Returns NULL if for the given name a factory does not exist, otherwise the factory is returned

	void removeFactory(const std::string& name);
		/// Removes the factory from the manager. 

private:
	FactoriesMap _factories;
};


} } // namespace Poco::Net


#endif // NetSSL_PrivateKeyFactoryMgr_INCLUDED
