/*
 * WtDataStore.cpp
 *
 *  Created on: Aug 12, 2008
 *      Author: saumil
 */

#include "StdAfx.h"

#include "WtDataStore.h"

#include "RelationManager.h"
#include "WtObject.h"
#include "WtObjectDefs.h"
#include "WtLogger.h"
#include "WtObjectRegistrar.h"

using namespace wt::framework;

DEFINE_STATIC_LOGGER("framework.WtDataStore", devLogger)

CWtDataStore::CWtDataStore()
{


}

CWtDataStore::~CWtDataStore()
{

}

CWtDataStore& CWtDataStore::Instance()
{
	static CWtDataStore _ds;
	return _ds;
}


/*Add New Object to the DataStore*/
WtoHandle CWtDataStore::AddObject(uint32_t dstClassId,
							 CWtObject* src,
							 RelationType relId)
{

	if (NULL == src)
	{
		return WTOBJECT_HND_NULL;
	}

	CWtObjectRegistrar& wtoReg = CWtObjectRegistrar::Instance();

	CWtObject* wto = wtoReg.CreateWtObject(dstClassId);

	if (NULL == wto)
	{
    	std::stringstream ss;
    	ss 	<< "Registrar could not create object with ID : "
    		<< dstClassId ;
		LOG_ERROR(devLogger(), ss.str())

		return WTOBJECT_HND_NULL;
	}

	WtoHandle wtoHnd = GetNextObjHandle();
	wto->SetWtoHandle(wtoHnd);
	AddWtObjectToDb(wtoHnd, wto);

	CRelationManager& rm = CRelationManager::Instance();

	//TODO: Decide if we should all wto -> src reverse Dir, maybe not
	rm.AddRelation(src, wto, relId);

	return wtoHnd;
}

/*Remove Object from the DataStore*/
bool CWtDataStore::RemoveObject(CWtObject* obj)
{
	return false;
}

/*Add new relationship between two objects*/
bool CWtDataStore::AddRelationship(CWtObject* src,
						CWtObject* dst,
						RelationType relId)
{
	if (NULL == src || NULL == dst)
	{
		return false;
	}

	CRelationManager& rm = CRelationManager::Instance();

	//TODO: Decide if we should all wto -> src reverse Dir, maybe not
	rm.AddRelation(src, dst, relId);

	return true;
}

/*Remove relationship between two objects*/
bool CWtDataStore::RemoveRelationship(CWtObject* src,
						   CWtObject* dst,
						   RelationType relId)
{
	return false;
}


/*Get the parent for given child*/
CWtObject* 	CWtDataStore::GetParent(CWtObject* child)
{
	CRelationManager& rm = CRelationManager::Instance();
	WtoHandle prn = rm.GetParent(child->GetWtoHandle());

	return GetObjectFromHnd(prn);
}

/*Get the parent for given child*/
CWtObject* 	CWtDataStore::GetParent(WtoHandle child)
{
	return GetParent(GetObjectFromHnd(child));
}

/*Get the given class id object type for given obj*/
CWtObject* 	CWtDataStore::GetObject(WtoHandle src, uint32_t wtoClassId, RelationType rel)
{
	CRelationManager& rm = CRelationManager::Instance();
	WtoHandle wto = rm.GetObject(src,wtoClassId, rel);

	return GetObjectFromHnd(wto);

}

/*Get all objects of type classId under the given obj*/
void CWtDataStore::GetObjects(WtoHandle src, WtoVec& wtv,
							  uint32_t wtoClassId, RelationType rel)
{
	WtoHndVec wVec;
	CRelationManager& rm = CRelationManager::Instance();

	rm.GetObjects(wVec, src, wtoClassId, rel);

	WtoHndVec::const_iterator wit = wVec.begin();

	while (wit != wVec.end())
	{
		wtv.push_back(GetObjectFromHnd(*wit));
		++wit;
	}

}

/*Get all objects of type classId under the given obj*/
void CWtDataStore::GetObjects(CWtObject* src, WtoVec& wtv,
							  uint32_t wtoClassId, RelationType rel)
{
	if (NULL == src)
	{
		return;
	}

	GetObjects(src->GetWtoHandle(), wtv, wtoClassId, rel);
}







//Private


WtoHandle CWtDataStore::GetNextObjHandle()
{
	static WtoHandle _objHnd = 100;
	++_objHnd;

	if (_objHnd == 0)
		_objHnd = 101;

	do
	{
		if (_wtObjs.find(_objHnd) == _wtObjs.end())
		{
			//Hnd not in Db. Can be used.
			break;
		}
		else
		{
			++_objHnd;
		}
	} while (1);

	return _objHnd;
}

bool CWtDataStore::AddWtObjectToDb(WtoHandle wtoHnd, CWtObject* wto)
{
	_wtObjs.insert(std::make_pair(wtoHnd, wto));
	return true;
}

CWtObject* CWtDataStore::GetObjectFromHnd(WtoHandle wto)
{
	WtObjectsMap::const_iterator wit = _wtObjs.find(wto);

	if (wit != _wtObjs.end())
	{
		return wit->second;
	}

	return NULL;

}
