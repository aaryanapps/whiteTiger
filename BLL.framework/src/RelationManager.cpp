#include "StdAfx.h"

#include "RelationManager.h"
#include "RelationInfo.h"
#include "WtObjectDb.h"
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
	
CRelationManager* CRelationManager::Instance()
{
	static CRelationManager* _rm = NULL;
	if (!_rm)
	{
		_rm = new CRelationManager();
		_rm->Init();
	}
	
	return _rm;
		
}

bool CRelationManager::AddRelation(WtoHandle from, 
								   WtoHandle to,
								   RelationType relId)
{
	CWtObjectDb& wtoDb = CWtObjectDb::Instance();
	CWtObject* pObj = wtoDb.GetObject(from);
	CWtObject* cObj = wtoDb.GetObject(to);
	if (!pObj || !cObj)
	{
		return false;
	}
    uint32_t fromType = pObj->GetTypeId();
    uint32_t toType = cObj->GetTypeId();
	
    uint32_t rel = relId.m_relId.AsInt();
    Statement stmt(*_mdbSession);
    stmt << "Insert into ExistingRelations values(:from,:to,:fromType,:totype,:rel)" , use(from) , use(to), use(fromType), use(toType), use(rel) ;
    stmt.execute();
    
    return true;
}

bool CRelationManager::RemoveRelation(WtoHandle from, 
		   							  WtoHandle to, 
		   							  RelationType relId)
{
	Statement stmt(*_mdbSession);
	uint32_t rel = relId.m_relId.AsInt();
	stmt << "Delete From ExistingRelations Where fromWt=:frm AND toWt=:to AND relId=:rel" , use(from), use(to), use(rel) ;
	
	stmt.execute();
    return true;
	
}

void CRelationManager::GetObjects(WtoVec& wtv, 
								  WtoHandle from, 
								  uint32_t toType, 
								  RelationType relId)
{

	Statement stmt(*_mdbSession);
	uint32_t rel = relId.m_relId.AsInt();
	stmt << "SELECT toWt FROM ExistingRelations where fromWt=:frmWt AND toWtType=:toWt AND relId=:rel" , use(from) , use(toType), use(rel) ;
	stmt.execute();
	
	RecordSet rs(stmt);
		
	bool more = rs.moveFirst();
	
	CWtObjectDb& wtoDb = CWtObjectDb::Instance();
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
			CWtObject* obj = wtoDb.GetObject((WtoHandle)hnd);
			if (obj)
			{
				wtv.push_back(obj);
			}
			else
			{
				std::stringstream ss;
				ss << "Cound not find WTO with Hnd " << hnd  << " In Db";
				LOG_ERROR(devLogger(), ss.str()) ;
			}
		}
		LOG_DEBUG( devLogger(), ss.str())
		more = rs.moveNext();
	}
	
}

CWtObject* CRelationManager::GetParent(WtoHandle to)
{
	RelationType rel = ParentChild();
	uint32_t re = rel.Id();
	Statement stmt(*_mdbSession);
	stmt << "select fromWt from ExistingRelations where toWt=:to AND relId=:r" , use(to) , use(re) ;
	stmt.execute();
	
	RecordSet rs(stmt);
	bool more = rs.moveFirst();
	
	CWtObjectDb& wtoDb = CWtObjectDb::Instance();
	CWtObject* pObj = NULL;
	while ( more ) /*Should run one or zero time*/
	{
		std::size_t cols = rs.columnCount();
		for (std::size_t col = 0; col < cols; ++cols ) /*Will run one time one column*/
		{
			/*Get tht object pointer froWtoHandlem map in WtObjectDb*/
			int32_t hnd = rs[col].convert<int>();
			pObj = wtoDb.GetObject((WtoHandle)hnd);
		}
		
		more = rs.moveNext();
	}
	
	if (!pObj)
	{
		std::stringstream ss;
		ss << "Cound not find Parent for WTO " << to << " In Db. Check ASAP!!!";
		LOG_ERROR(devLogger(), ss.str()) ;		
	}

	return pObj;
}

CWtObject* CRelationManager::GetObject(WtoHandle from, 
								  	   uint32_t  to, 
								  	   RelationType relId)
{
	return NULL;
}


void CRelationManager::Init()
{
	
	_mdbSession = new Session("SQLite", ":memory:");	
	
	*_mdbSession << "CREATE TABLE ExistingRelations (fromWt INT(4), toWt INT(4), fromWtType INT(4), toWtType INT(4), relId INT(4))" , now;
	
	m_init = true;
	
}
