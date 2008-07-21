#ifndef _WT_RELATIONMANAGER_H__
#define _WT_RELATIONMANAGER_H__

#include "BllFrameworkExport.h"

//#include "WtObject.h"
#include "Globals.h"
#include "WtObjectDb.h"
#include "RelationInfo.h"
#include "Poco/Data/Session.h"

namespace wt {
namespace framework {

class FRAMEWORK_EXPORT CRelationManager {

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
	
	bool 					m_init;
	Poco::Data::Session* 	_mdbSession;
	
};

}
}

#endif /*RELATIONMANAGER_H_*/
