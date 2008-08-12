#ifndef WT_CWTOBJECT_H__
#define WT_CWTOBJECT_H__

#include "BllFrameworkExport.h"

#include "WtObjectDefs.h"
#include "RelationInfo.h"

namespace wt {
namespace framework {

class FRAMEWORK_EXPORT CWtObject {
public:
	CWtObject();
	virtual ~CWtObject();

	WtoHandle GetWtoHandle() {return m_wtoHnd;}
	void SetWtoHandle(WtoHandle hnd) {m_wtoHnd = hnd;}

	WtoHandle GetWtoType() {return m_wtoType;}
	void SetWtoType(WtoType type) {m_wtoType = type;}

	void SetWtoName(std::string& name) {m_wtoName = name;}
	std::string GetWtoName() {return m_wtoName;}

	//virtual void InitWto() = 0;

	/*Calls the base class GetInheritedClassIds and get the classId*/
	virtual void GetInheritedTypes(WtoTypeIdsVec& typeIdVec) = 0;

	virtual uint32_t GetTypeId() = 0;

	CWtObject* 	GetParent();

	void 		GetObjects(WtoVec& wtv, WtoType type,
										RelationType rel = ParentChild());

	CWtObject*	GetObject(WtoType type, RelationType rel = ParentChild());

private:
	WtoHandle m_wtoHnd;
	WtoType   m_wtoType;
	std::string m_wtoName;
};

}
}

#endif /*WT_CWTOBJECT_H__*/
