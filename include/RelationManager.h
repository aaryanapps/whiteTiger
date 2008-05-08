#ifndef _WT_RELATIONMANAGER_H__
#define _WT_RELATIONMANAGER_H__

//#include "WtObject.h"
#include "Globals.h"
#include "sqlite3x.hpp"
#include "WtObjectDb.h"
#include "RelationInfo.h"

class CRelationManager {

public:
	CRelationManager();
	~CRelationManager();
	
	static CRelationManager* Instance();
	
	bool AddRelation(WtoHandle from, WtoHandle to,
			   		 RelationType relId = ParentChild());
	
	bool RemoveRelation(WtoHandle from, WtoHandle to, RelationType relId = ParentChild());
	
	CWtObject* GetParent(WtoHandle to);

	void GetObjects(WtoVec& wtv, WtoHandle from, uint32_t toType, RelationType relId = ParentChild());
	
	CWtObject* GetObject( WtoHandle from, 
						  uint32_t  to, 
						  RelationType relId = ParentChild());
private:
	void Init();
	
	bool m_init;
	sqlite3 * m_db;
	sqlite3x::sqlite3_connection * m_dbCon;
	
};

#endif /*RELATIONMANAGER_H_*/
