#ifndef WT_CWTOBJECT_H__
#define WT_CWTOBJECT_H__

#include "WtObjectDefs.h"
#include "RelationInfo.h"

typedef uint32_t WtoType;

class CWtObject
{
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

#endif /*WT_CWTOBJECT_H__*/
