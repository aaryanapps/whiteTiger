/*
 * WtDataStore.h
 *
 *  Created on: Aug 12, 2008
 *      Author: saumil
 */

#ifndef _WT_WTDATASTORE_H_
#define _WT_WTDATASTORE_H_

#include "BllFrameworkExport.h"

#include "Globals.h"
#include "WtObjectDefs.h"
#include "RelationInfo.h"

namespace wt {
namespace framework {

class CWtObject;

class FRAMEWORK_EXPORT CWtDataStore {

public:
	static CWtDataStore& Instance();

	/*Add New Object to the DataStore*/
	WtoHandle	AddObject(uint32_t srcClassId,
					  CWtObject* dst,
					  RelationType relId = ParentChild());

	/*Remove Object from the DataStore*/
	bool 	RemoveObject(CWtObject* obj);

	/*Add new relationship between two objects*/
	bool	AddRelationship(CWtObject* src,
							CWtObject* dst,
							RelationType relId);

	/*Remove relationship between two objects*/
	bool	RemoveRelationship(CWtObject* src,
							   CWtObject* dst,
							   RelationType relId);


	/*Get the parent for given child*/
	CWtObject* 	GetParent(CWtObject* child);

	/*Get the parent for given child*/
	CWtObject* 	GetParent(WtoHandle child);

	/*Get the given class id object type for given obj*/
	CWtObject* 	GetObject(WtoHandle src, uint32_t wtoClassId, RelationType rel);

	/*Get all objects of type classId under the given obj*/
	void GetObjects(WtoHandle src, WtoVec& wtv, uint32_t wtoClassId, RelationType rel);

	/*Get all objects of type classId under the given obj*/
	void GetObjects(CWtObject* src, WtoVec& wtv, uint32_t wtoClassId, RelationType rel);


private:
	CWtDataStore();
	~CWtDataStore();

	/*Returns the next available Wto Hnd*/
	WtoHandle GetNextObjHandle();

	/*Add the WtoHandle to internal Db*/
	bool AddWtObjectToDb(WtoHandle wtoHnd, CWtObject* wto);

	/*Get the object from hnd*/
	CWtObject* GetObjectFromHnd(WtoHandle wto);

	WtObjectsMap _wtObjs;

};

}
}


#endif /* _WT_WTDATASTORE_H_ */
