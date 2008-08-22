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
								   WtoType fromType,
								   WtoType toType)
{
	if (!sObj || !dObj)
	{
		return false;
	}

    uint32_t rel = relId.m_relId.AsInt();


	if (fromType == WTOBJECT_CLASSID_NULL)
	{
		fromType = sObj->GetClassId();
	}

	if (toType == WTOBJECT_CLASSID_NULL)
	{
		toType = dObj->GetClassId();
	}

    uint32_t sObjHnd = sObj->GetWtoHandle();
    uint32_t dObjHnd = dObj->GetWtoHandle();

    Statement stmt(*_mdbSession);
    stmt << "Insert into ExistingRelations values(:from,:to,:fromType,:totype,:rel)" , use(sObjHnd) , use(dObjHnd), use(fromType), use(toType), use(rel) ;
    stmt.execute();

    return true;
}

bool CRelationManager::RemoveRelation(CWtObject* from,
									  CWtObject* to,
		   							  RelationType relId)
{
	if (!from || !to)
	{
		return false;
	}

	uint32_t src = from->GetWtoHandle();
	uint32_t dst = to->GetWtoHandle();
	uint32_t rel = relId.m_relId.AsInt();

	Statement stmt(*_mdbSession);
	stmt << "Delete From ExistingRelations Where fromWt=:frm AND toWt=:to AND relId=:rel" , use(src), use(dst), use(rel) ;

	stmt.execute();
    return true;

}

void CRelationManager::GetObjects(WtoHndVec& wtv,
								  CWtObject* to,
								  uint32_t fromClassType,
								  RelationType relId)
{

	Statement stmt(*_mdbSession);

	uint32_t rel = relId.m_relId.AsInt();
	uint32_t toType = to->GetClassId();
	uint32_t toHnd  = to->GetWtoHandle();

	stmt << "SELECT fromWt FROM ExistingRelations where toWt=:toHnd AND toWtType=:toType AND fromWtType=:fromClassType AND relId=:rel" , use(toHnd) , use(toType), use(fromClassType), use(rel) ;
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
	stmt << "select toWt from ExistingRelations where fromWt=:to AND fromWtType=:childType AND relId=:r" , use(childHnd) , use(childType), use(re) ;
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

	*_mdbSession << "CREATE TABLE ExistingRelations (fromWt INTEGER(4), toWt INTEGER(4), fromWtType INTEGER(4), toWtType INTEGER(4), relId INTEGER(4))", now;

	m_init = true;

}
