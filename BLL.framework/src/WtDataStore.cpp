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

	WtoHandle wHnd = CreateObject(dstClassId);

	if (WTOBJECT_HND_NULL == wHnd)
	{
		return WTOBJECT_HND_NULL;
	}

	if (!AddRelationship(src, GetObjectFromHnd(wHnd), relId))
	{
    	std::stringstream ss;
    	ss 	<< "Could not add relationship between: "
    		<< dstClassId << "and src: " << src->GetClassId() ;
		LOG_ERROR(devLogger(), ss.str())
		//TODO: Fix Memory Leak, delete newly create object
		return WTOBJECT_HND_NULL;
	}

	return wHnd;
}

WtoHandle CWtDataStore::CreateObject(uint32_t dstClassId)
{
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

	//TODO: Decide if we should all wto -> src reverse Dir, maybe not

	CRelationManager& rm = CRelationManager::Instance();

	WtoTypeIdsSet inhtIds;
	dst->GetInheritedTypes(inhtIds);

	WtoTypeIdsSet::const_iterator iit = inhtIds.begin();

	for(; iit != inhtIds.end(); iit++)
	{
		rm.AddRelation(src, dst, relId, WTOBJECT_CLASSID_NULL,*iit);
	}

	return true;
}


/*Add new relationship between two objects*/
bool CWtDataStore::AddRelationship(WtoHandle src,
						WtoHandle dst,
						RelationType relId)
{
	CWtObject* pSrc = GetObjectFromHnd(src);
	CWtObject* pDst = GetObjectFromHnd(dst);

	if (NULL == pSrc || NULL == pDst)
	{
		return false;
	}

	return AddRelationship(pSrc, pDst, relId);

}


/*Remove relationship between two objects*/
bool CWtDataStore::RemoveRelationship(CWtObject* src,
						   CWtObject* dst,
						   RelationType relId)
{
	return false;
}

/*Remove relationship between two objects*/
bool CWtDataStore::RemoveRelationship(WtoHandle src,
						   WtoHandle dst,
						   RelationType relId)
{
	return false;
}


/*Get the parent for given child*/
CWtObject* 	CWtDataStore::GetParent(CWtObject* child)
{
	CRelationManager& rm = CRelationManager::Instance();
	WtoHandle prn = rm.GetParent(child);

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
	WtoHandle wto = rm.GetObject(GetObjectFromHnd(src),wtoClassId, rel);

	return GetObjectFromHnd(wto);

}

/*Get all objects of type classId under the given obj*/
void CWtDataStore::GetObjects(WtoHandle src, WtoVec& wtv,
							  uint32_t wtoClassId, RelationType rel)
{
	if (WTOBJECT_HND_NULL == src)
	{
		return;
	}
	GetObjects(GetObjectFromHnd(src), wtv, wtoClassId, rel);
}

/*Get all objects of type classId under the given obj*/
void CWtDataStore::GetObjects(CWtObject* src, WtoVec& wtv,
							  uint32_t wtoClassId, RelationType rel)
{
	if (NULL == src)
	{
		return;
	}

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


CWtObject* CWtDataStore::GetObjectFromHnd(WtoHandle wto)
{
	WtObjectsMap::const_iterator wit = _wtObjs.find(wto);

	if (wit != _wtObjs.end())
	{
		return wit->second;
	}

	return NULL;

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
	if (WTOBJECT_HND_NULL == wtoHnd || WTOBJECT_NULL == wto)
	{
		return false;
	}

	_wtObjs.insert(std::make_pair(wtoHnd, wto));
	return true;
}

