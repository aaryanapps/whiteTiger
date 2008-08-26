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

class FRAMEWORK_EXPORT CWtDataStore {

public:
	static CWtDataStore& Instance();

	/*Add New Object to the DataStore*/
	WtoHandle	AddObject(uint32_t dstClassId,
					  CWtObject* src,
					  RelationType relId = ParentChild());

	/*Create Object with the specified ID.*/
	WtoHandle	CreateObject(uint32_t dstClassId);

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

	/*Add new relationship between two objects*/
	bool	AddRelationship(WtoHandle src,
							WtoHandle dst,
							RelationType relId);

	/*Remove relationship between two objects*/
	bool	RemoveRelationship(WtoHandle src,
							   WtoHandle dst,
							   RelationType relId);


	/*Get the parent for given child*/
	CWtObject* 	GetParent(CWtObject* child);

	/*Get the parent for given child*/
	CWtObject* 	GetParent(WtoHandle child);

	/*Get the given class id object type for given obj*/
	CWtObject* 	GetObject(WtoHandle src, uint32_t dstClassId, RelationType rel);

	/*Get all objects of type classId under the given obj*/
	void GetObjects(WtoHandle src, WtoVec& wtv, uint32_t dstClassId, RelationType rel);

	/*Get all objects of type classId under the given obj*/
	void GetObjects(CWtObject* src, WtoVec& wtv, uint32_t dstClassId, RelationType rel);

	/*Get the object from hnd*/
	CWtObject* GetObjectFromHnd(WtoHandle wto);

private:
	CWtDataStore();
	~CWtDataStore();

	/*Returns the next available Wto Hnd*/
	WtoHandle GetNextObjHandle();

	/*Add the WtoHandle to internal Db*/
	bool AddWtObjectToDb(WtoHandle wtoHnd, CWtObject* wto);

	WtObjectsMap _wtObjs;

};

}
}


#endif /* _WT_WTDATASTORE_H_ */
