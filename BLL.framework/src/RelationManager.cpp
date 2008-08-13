#include "StdAfx.h"

#include "RelationManager.h"
#include "RelationInfo.h"
#include "WtObject.h"
#include "WtLogger.h"

#include "Poco/Data/RecordSet.h"

using namespace wt::framework;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;

DEFINE_STATIC_LOGGER("framework.RelationManager", devLogger)

CRelationManager::CRelationManager() :
	m_init(false)
{

}

CRelationManager::~CRelationManager()
{

}

CRelationManager& CRelationManager::Instance()
{
	static CRelationManager* _rm = NULL;
	if (!_rm)
	{
		_rm = new CRelationManager();
		_rm->Init();
	}

	return *_rm;

}

bool CRelationManager::AddRelation(CWtObject* pObj,
								   CWtObject* cObj,
								   RelationType relId)
{
	if (!pObj || !cObj)
	{
		return false;
	}

    uint32_t fromType = pObj->GetClassId();
    uint32_t toType = cObj->GetClassId();
    uint32_t rel = relId.m_relId.AsInt();

    uint32_t pObjHnd = pObj->GetWtoHandle();
    uint32_t cObjHnd = cObj->GetWtoHandle();

    Statement stmt(*_mdbSession);
    stmt << "Insert into ExistingRelations values(:from,:to,:fromType,:totype,:rel)" , use(pObjHnd) , use(cObjHnd), use(fromType), use(toType), use(rel) ;
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
								  WtoHandle from,
								  uint32_t toClassType,
								  RelationType relId)
{

	Statement stmt(*_mdbSession);
	uint32_t rel = relId.m_relId.AsInt();
	stmt << "SELECT toWt FROM ExistingRelations where fromWt=:frmWt AND toWtType=:toWt AND relId=:rel" , use(from) , use(toClassType), use(rel) ;
	stmt.execute();

	RecordSet rs(stmt);

	bool more = rs.moveFirst();

	while ( more )
	{
		std::stringstream ss;
		std::size_t cols = rs.columnCount();
		for (std::size_t col = 0; col < cols; ++col ) /*Will run one time for one column*/
		{
			/*Get tht object pointer froWtoHandlem map in WtObjectDb*/

			int32_t hnd = rs[col].convert<int>();
			ss << "Column:" << col << "=" <<  hnd;
			ss << "   ," ;
			wtv.push_back(hnd);
		}
		LOG_DEBUG( devLogger(), ss.str())
		more = rs.moveNext();
	}

}

WtoHandle CRelationManager::GetParent(WtoHandle to)
{
	RelationType rel = ParentChild();
	uint32_t re = rel.Id();
	Statement stmt(*_mdbSession);
	stmt << "select fromWt from ExistingRelations where toWt=:to AND relId=:r" , use(to) , use(re) ;
	stmt.execute();

	RecordSet rs(stmt);
	bool more = rs.moveFirst();

	int32_t hnd = WTOBJECT_HND_NULL;
	while ( more ) /*Should run one or zero time*/
	{
		std::size_t cols = rs.columnCount();
		for (std::size_t col = 0; col < cols; ++cols ) /*Will run one time one column*/
		{
			/*Get tht object pointer froWtoHandlem map in WtObjectDb*/
			hnd = rs[col].convert<int>();
		}

		more = rs.moveNext();
	}

	if (WTOBJECT_HND_NULL == hnd)
	{
		std::stringstream ss;
		ss << "Cound not find Parent for WTO " << to << " In Db. Check ASAP!!!";
		LOG_ERROR(devLogger(), ss.str()) ;
	}

	return hnd;
}

WtoHandle CRelationManager::GetObject(WtoHandle from,
								  	   uint32_t  to,
								  	   RelationType relId)
{
	return WTOBJECT_HND_NULL;
}


void CRelationManager::Init()
{

	_mdbSession = new Session("SQLite", ":memory:");

	*_mdbSession << "CREATE TABLE ExistingRelations (fromWt INT(4), toWt INT(4), fromWtType INT(4), toWtType INT(4), relId INT(4))" , now;

	m_init = true;

}
