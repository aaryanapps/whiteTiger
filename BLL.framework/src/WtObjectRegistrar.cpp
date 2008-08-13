/*
 * WtObjectRegistrar.cpp
 *
 *  Created on: Aug 12, 2008
 *      Author: saumil
 */

#include "StdAfx.h"
#include "WtObjectRegistrar.h"

using namespace wt::framework;

//DEFINE_STATIC_LOGGER("framework.WtObjectRegistrar", devLogger)
CWtObjectRegistrar::CWtObjectRegistrar()
{

}

CWtObjectRegistrar::~CWtObjectRegistrar()
{

}

CWtObjectRegistrar& CWtObjectRegistrar::Instance()
{
	static CWtObjectRegistrar _or;

	return _or;
}

uint32_t CWtObjectRegistrar::RegisterCreator(uint32_t classId, WtObjCreator wtCrt)
{
	if (IsValidClassId(classId))
	{
		//ID already registered. Should not happen
		return WTOBJECT_HND_NULL;
	}
	else
	{
		WtoRegistry* reg = GetRegistry();
		reg->insert(std::make_pair(classId, wtCrt));
		return classId;
	}

}

CWtObject*	CWtObjectRegistrar::CreateWtObject(uint32_t classId)
{
	WtoRegistry* reg = GetRegistry();
	WtoRegistry::const_iterator wit = reg->find(classId);

	if (wit != reg->end())
	{
		//ID already registered. Should not happen
		CWtObject* wto = (wit->second)();

		if (NULL == wto)
		{
			//Log Error. maybe throw exception
		}

		return wto;

	}
	else
	{
		return NULL;
	}

	return NULL;
}

bool CWtObjectRegistrar::IsValidClassId(uint32_t cid)
{
	WtoRegistry* reg = GetRegistry();
	WtoRegistry::const_iterator wit = reg->find(cid);

	if (wit != reg->end())
	{
		//ID already registered. Should not happen
		return true;
	}
	else
	{
		return false;
	}

}

WtoRegistry* CWtObjectRegistrar::GetRegistry()
{
	static WtoRegistry 	_wtoReg; 	/*Set to hold registered Ids*/
	return &_wtoReg;
}
