#include "WtObject.h"
#include "RelationManager.h"
#include "WtLogger.h"

DEFINE_STATIC_LOGGER("bll.WtObject", devLogger);

using namespace wt::framework;

CWtObject::CWtObject()
{
}

CWtObject::~CWtObject()
{
}

CWtObject* 	CWtObject::GetParent()
{
	CRelationManager *rm = CRelationManager::Instance();
	CWtObject* wto = rm->GetParent(GetWtoHandle());
	
	if (!wto)
	{
		std::stringstream ss;
		ss << "AAAAAAAAhhhhhh, No Parent!!!!!!!. Check ASAP";
		LOG_ERROR(devLogger(), ss.str()) ;
		return NULL;
	}
	
	return wto;
}

void CWtObject::GetObjects(WtoVec& wtv, uint32_t type, RelationType rel)
{
	CRelationManager *rm = CRelationManager::Instance();
	rm->GetObjects(wtv, GetWtoHandle(), type, rel);
}

CWtObject* CWtObject::GetObject(uint32_t type, RelationType rel)
{
	CRelationManager *rm = CRelationManager::Instance();
	return rm->GetObject(GetWtoHandle(), type, rel);
}
