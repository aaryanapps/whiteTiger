
#include "RelationManager.h"
//#include "Globals.h"
#include "sqlite3x.hpp"
#include "RelationInfo.h"
#include "WtObjectDb.h"
#include "WtObject.h"
#include "WtLogger.h"

//using namespace sqlite3x;
DEFINE_STATIC_LOGGER("bll.RelationManager", devLogger);

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
	
    sqlite3x::sqlite3_command cmd(*m_dbCon, "Insert into ExistingRelations values(?,?,?,?,?);");
    cmd.bind(1, (int32_t)from);
    cmd.bind(2, (int32_t)to);
    cmd.bind(3, (int32_t)fromType);
    cmd.bind(4, (int32_t)toType);    
    cmd.bind(5, (int32_t)relId.m_relId.AsInt());
    cmd.executenonquery();
    
    return true;
}

bool CRelationManager::RemoveRelation(WtoHandle from, 
		   							  WtoHandle to, 
		   							  RelationType relId)
{
	std::stringstream s;
	s << "Delete From ExistingRelations " ;
	s << "Where " ;
	s << " fromWt=" << from << " AND ";
	s << " toWt=" << to << " AND ";
	s << " relId=" << relId.m_relId.AsInt() << " ;";
	
	sqlite3x::sqlite3_command cmd(*m_dbCon, s.str());
    cmd.executenonquery();
    
    return true;
	
}

void CRelationManager::GetObjects(WtoVec& wtv, 
								  WtoHandle from, 
								  uint32_t toType, 
								  RelationType relId)
{
	
	std::stringstream s;
	s << "select toWt ExistingRelations where ";
	s << "fromWt=" << from << " AND ";
	s << "toWtType=" << toType << " AND ";
	s << "relId=" << relId.m_relId.AsInt() << " ;";
	
	sqlite3x::sqlite3_command cmd(*m_dbCon, s.str());
	sqlite3x::sqlite3_cursor reader=cmd.executecursor();
	const int colcount = reader.colcount();
	CWtObjectDb& wtoDb = CWtObjectDb::Instance();
	while (reader.step() ) 
	{
		std::stringstream ss;
		for (int i = 0; i < colcount; ++i ) /*Will run one time one column*/
		{
			/*Get tht object pointer froWtoHandlem map in WtObjectDb*/
			int32_t hnd = reader.getint(i);
			ss << "Column:" << i << "=" <<  hnd;
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
	}
	
}

CWtObject* CRelationManager::GetParent(WtoHandle to)
{
	RelationType rel = ParentChild();
	std::stringstream s;
	s << "select fromWt from ExistingRelations where ";
	s << "toWt=" << to << " AND ";
	s << "relId=" << rel.Id() << " ;";
	
	sqlite3x::sqlite3_command cmd(*m_dbCon, s.str());
	sqlite3x::sqlite3_cursor reader=cmd.executecursor();
	const int colcount = reader.colcount();
	CWtObjectDb& wtoDb = CWtObjectDb::Instance();
	CWtObject* pObj = NULL;
	while (reader.step() ) /*Should run one or zero time*/
	{
		for (int i = 0; i < colcount; ++i ) /*Will run one time one column*/
		{
			/*Get tht object pointer froWtoHandlem map in WtObjectDb*/
			int32_t hnd = reader.getint(i);
			pObj = wtoDb.GetObject((WtoHandle)hnd);
		}
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
    m_db = NULL;
    sqlite3_open( ":memory:", &m_db );
	m_dbCon = new sqlite3x::sqlite3_connection(m_db);
	std::stringstream s;
	s << "CREATE TABLE " ;
	s << "ExistingRelations (" ;
	s << "fromWt INT(4), " ;
	s << "toWt INT(4), " ;
	s << "fromWtType INT(4), " ;
	s << "toWtType INT(4), " ;
	s << "relId INT(4));";
	
	m_dbCon->executenonquery(s.str());
	sqlite3x::sqlite3_command st(*m_dbCon, "select * from sqlite_master where type='ExistingRelations'");
	m_init = true;
	
}
