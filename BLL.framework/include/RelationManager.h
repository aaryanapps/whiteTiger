#ifndef _WT_RELATIONMANAGER_H__
#define _WT_RELATIONMANAGER_H__

#include "BllFrameworkExport.h"

//#include "WtObject.h"
#include "Globals.h"
#include "WtObjectDefs.h"
#include "RelationInfo.h"
#include "Poco/Data/Session.h"

namespace wt {
namespace framework {

class FRAMEWORK_EXPORT CRelationManager {

public:
	CRelationManager();
	~CRelationManager();

	static CRelationManager& Instance();

	bool AddRelation(CWtObject* from, CWtObject* to,
			   		 RelationType relId = ParentChild(),
					 WtoType sType = WTOBJECT_CLASSID_NULL,
					 WtoType dType = WTOBJECT_CLASSID_NULL);

	bool RemoveRelation(CWtObject* from, CWtObject* to, RelationType relId = ParentChild());
	WtoHandle GetParent(CWtObject* child);

	void GetObjects(WtoHndVec& wtv, CWtObject* to, uint32_t toClassType, RelationType relId = ParentChild());

	WtoHandle GetObject( CWtObject* to,
						  uint32_t  from,
						  RelationType relId = ParentChild());
private:
	void Init();

	bool 					m_init;
	Poco::Data::Session* 	_mdbSession;

};

}
}

#endif /*RELATIONMANAGER_H_*/
