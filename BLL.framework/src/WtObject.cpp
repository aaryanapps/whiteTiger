#include "StdAfx.h"

#include "WtObject.h"
#include "WtDataStore.h"
#include "WtLogger.h"

DEFINE_STATIC_LOGGER("framework.WtObject", devLogger)

using namespace wt::framework;

CWtObject::CWtObject()
{
}

CWtObject::~CWtObject()
{
}

/*Add the class ID to the list of derived classes*/
void CWtObject::AddAsDerivedClassId(WtoType classId)
{
	if ( !IsInstanceOf(classId) )
	{
		m_derivedClassIds.insert(classId);
	}
}

/*Add the class ID to the list of derived classes*/
bool CWtObject::IsInstanceOf(WtoType classId)
{
	WtoTypeIdsSet::const_iterator wit = m_derivedClassIds.find(classId);

	if (wit != m_derivedClassIds.end())
	{
		return true;
	}

	return false;
}

/*Calls the base class GetInheritedClassIds and get the classId*/
void CWtObject::GetInheritedTypes(WtoTypeIdsSet& typeIdSet)
{
	typeIdSet = m_derivedClassIds;
}

CWtObject* 	CWtObject::GetParent()
{
	CWtDataStore &ds = CWtDataStore::Instance();
	CWtObject* wto = ds.GetParent(GetWtoHandle());

	if (!wto)
	{
		std::stringstream ss;
		ss << "AAAAAAAAhhhhhh, No Parent!!!!!!!. Check ASAP";
		LOG_ERROR(devLogger(), ss.str()) ;
		return NULL;
	}

	return wto;
}

void CWtObject::GetObjects(WtoVec& wtv, uint32_t classId, RelationType rel)
{
	CWtDataStore &ds = CWtDataStore::Instance();
	ds.GetObjects(GetWtoHandle(), wtv, classId, rel);
}

CWtObject* CWtObject::GetObject(uint32_t classId, RelationType rel)
{
	CWtDataStore &ds = CWtDataStore::Instance();
	return ds.GetObject(GetWtoHandle(), classId, rel);
}
