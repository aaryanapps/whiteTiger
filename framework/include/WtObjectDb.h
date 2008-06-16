#ifndef _WT_WTOBJECTDB_H__
#define _WT_WTOBJECTDB_H__

#include "Globals.h"
#include "WtObjectDefs.h"

class CWtObject;

class CWtObjectDb
{
public:
	CWtObjectDb();
	~CWtObjectDb();
	
	static CWtObjectDb& Instance();
	WtoHandle AddObject(CWtObject* obj);
	void RemoveObject(WtoHandle hnd);
	CWtObject* GetObject(WtoHandle hnd);
	
private:
	WtObjectsMap m_wtObjs;
	
	WtoHandle GetNextObjHandle();
};

#endif /*_WT_WTOBJECTDB_H__*/