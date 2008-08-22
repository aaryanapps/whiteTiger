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

	/*Add relation between the src,dst objects.*/
	bool AddRelation(CWtObject* src, CWtObject* dst,
			   		 RelationType relId = ParentChild(),
					 WtoType sType = WTOBJECT_CLASSID_NULL,
					 WtoType dType = WTOBJECT_CLASSID_NULL);

	/*Removes the specified relation between the src and dst*/
	bool RemoveRelation(CWtObject* src, CWtObject* dst, RelationType relId = ParentChild());

	/*Return the parent handle*/
	WtoHandle GetParent(CWtObject* child);

	/*Get all objects of type dstClassType */
	void GetObjects(WtoHndVec& wtv, CWtObject* src, uint32_t dstClassType, RelationType relId = ParentChild());

	/*Get Objet of type dstClassID*/
	WtoHandle GetObject( CWtObject* src,
						  uint32_t  dstClassId,
						  RelationType relId = ParentChild());
private:
	void Init();

	bool 					m_init;
	Poco::Data::Session* 	_mdbSession;

};

}
}

#endif /*RELATIONMANAGER_H_*/
