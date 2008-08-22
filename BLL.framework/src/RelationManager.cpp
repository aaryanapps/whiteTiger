#include "StdAfx.h"

#include "RelationManager.h"
#include "RelationInfo.h"
#include "WtObject.h"
#include "WtLogger.h"

#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/RecordSet.h"

using namespace wt::framework;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;


DEFINE_STATIC_LOGGER("framework.RelationManager", devLogger)

CRelationManager::CRelationManager() :
	m_init(false)
{
	Init();
}

CRelationManager::~CRelationManager()
{

}

CRelationManager& CRelationManager::Instance()
{
	static CRelationManager _rm;

	return _rm;

}

bool CRelationManager::AddRelation(CWtObject* sObj,
								   CWtObject* dObj,
								   RelationType relId,
								   WtoType srcType,
								   WtoType dstType)
{
	if (!sObj || !dObj)
	{
		return false;
	}

    uint32_t rel = relId.m_relId.AsInt();


	if (srcType == WTOBJECT_CLASSID_NULL)
	{
		srcType = sObj->GetClassId();
	}

	if (dstType == WTOBJECT_CLASSID_NULL)
	{
		dstType = dObj->GetClassId();
	}

    uint32_t sObjHnd = sObj->GetWtoHandle();
    uint32_t dObjHnd = dObj->GetWtoHandle();

    Statement stmt(*_mdbSession);
    stmt << "Insert into ExistingRelations values(:src,:dst,:srcType,:dsttype,:rel)" , use(sObjHnd) , use(dObjHnd), use(srcType), use(dstType), use(rel) ;
    stmt.execute();

    return true;
}

bool CRelationManager::RemoveRelation(CWtObject* src,
									  CWtObject* dst,
		   							  RelationType relId)
{
	if (!src || !dst)
	{
		return false;
	}

	uint32_t srcHnd = src->GetWtoHandle();
	uint32_t dstHnd = dst->GetWtoHandle();
	uint32_t rel = relId.m_relId.AsInt();

	//TODO: Add the classId to be checked for removal too.
	Statement stmt(*_mdbSession);
	stmt << "Delete From ExistingRelations Where srcClass=:src AND dstClass=:dst AND relId=:rel" , use(srcHnd), use(dstHnd), use(rel) ;

	stmt.execute();
    return true;

}

void CRelationManager::GetObjects(WtoHndVec& wtv,
								  CWtObject* src,
								  uint32_t dstClassType,
								  RelationType relId)
{

	Statement stmt(*_mdbSession);

	uint32_t rel = relId.m_relId.AsInt();
	uint32_t srcClassType = src->GetClassId();
	uint32_t srcHnd  = src->GetWtoHandle();

	stmt << "SELECT dstClass FROM ExistingRelations where srcClass=:srcHnd AND srcClassType=:srcType AND dstClassType=:srcClassType AND relId=:rel" , use(srcHnd) , use(srcClassType), use(dstClassType), use(rel) ;
	stmt.execute();

	RecordSet rs(stmt);

	bool more = rs.moveFirst();

	while ( more )
	{
		std::stringstream ss;
		std::size_t cols = rs.columnCount();
		for (std::size_t col = 0; col < cols; ++col ) /*Will run one time for one column*/
		{
			int32_t hnd = rs[col].convert<int>();
			ss << "Column:" << col << "=" <<  hnd;
			ss << "   ," ;
			wtv.push_back(hnd);
		}
		LOG_DEBUG( devLogger(), ss.str())
		more = rs.moveNext();
	}

}

WtoHandle CRelationManager::GetParent(CWtObject* child)
{
	RelationType rel = ParentChild();
	uint32_t re = rel.Id();
	uint32_t childHnd = child->GetWtoHandle();
	uint32_t childType = child->GetClassId();

	Statement stmt(*_mdbSession);
	stmt << "select srcClass from ExistingRelations where dstClass=:to AND dstClassType=:childType AND relId=:r" , use(childHnd) , use(childType), use(re) ;
	stmt.execute();

	RecordSet rs(stmt);
	bool more = rs.moveFirst();

	int32_t hnd = WTOBJECT_HND_NULL;
	while ( more ) /*Should run one time coz there has to be a parent*/
	{
		std::size_t cols = rs.columnCount();
		for (std::size_t col = 0; col < cols; ++col ) /*Will run one time one column*/
		{
			hnd = rs[col].convert<int>();
		}

		more = rs.moveNext();
	}

	if (WTOBJECT_HND_NULL == hnd)
	{
		std::stringstream ss;
		ss << "Could not find Parent for WTO " << child->GetWtoHandle() << " In Db. Check ASAP!!!";
		LOG_ERROR(devLogger(), ss.str()) ;
	}

	return hnd;
}

WtoHandle CRelationManager::GetObject(CWtObject* to,
								  	   uint32_t  from,
								  	   RelationType relId)
{
	WtoHndVec wtv;
	//Call GetObjects and return the first one.
	return WTOBJECT_HND_NULL;
}


void CRelationManager::Init()
{
	// register SQLite connector
	Poco::Data::SQLite::Connector::registerConnector();
	_mdbSession = new Session("SQLite", "temp.db");

	// drop sample table, if it exists
	*_mdbSession << "DROP TABLE IF EXISTS ExistingRelations", now;

	*_mdbSession << "CREATE TABLE ExistingRelations (srcClass INTEGER(4), dstClass INTEGER(4), srcClassType INTEGER(4), dstClassType INTEGER(4), relId INTEGER(4))", now;

	m_init = true;

}
