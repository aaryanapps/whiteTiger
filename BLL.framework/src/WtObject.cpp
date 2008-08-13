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
