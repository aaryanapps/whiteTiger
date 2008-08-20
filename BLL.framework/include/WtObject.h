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

	//virtual void InitWto() = 0;

	/*Calls the base class GetInheritedClassIds and get the classId*/
	void GetInheritedTypes(WtoTypeIdsSet& typeIdVec);

	/*Get the classId of the current object*/
	virtual uint32_t GetClassId() = 0;

	/*Add the class ID to the list of derived classes*/
	void AddAsDerivedClassId(WtoType classId);

	/*Add the class ID to the list of derived classes*/
	bool IsInstanceOf(WtoType classId);

	/*Returns the parent of the object*/
	CWtObject* 	GetParent();

	/*Returns all the objects of given type and relation*/
	void 		GetObjects(WtoVec& wtv, WtoType type,
										RelationType rel = ParentChild());

	/*Returns one object of given type and relation. Order is not maintained.*/
	CWtObject*	GetObject(WtoType type, RelationType rel = ParentChild());


	//Getters-Setters

	WtoHandle GetWtoHandle() {return m_wtoHnd;}
	void SetWtoHandle(WtoHandle hnd) {m_wtoHnd = hnd;}

	WtoHandle GetWtoType() {return m_wtoType;}
	void SetWtoType(WtoType type) {m_wtoType = type;}

	void SetWtoName(std::string& name) {m_wtoName = name;}
	std::string GetWtoName() {return m_wtoName;}


private:
	WtoHandle m_wtoHnd;
	WtoType   m_wtoType;
	std::string m_wtoName;
	WtoTypeIdsSet	m_derivedClassIds;

};

}
}

#endif /*WT_CWTOBJECT_H__*/
