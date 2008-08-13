#ifndef _WT_WTOBJECTDB_H__
#define _WT_WTOBJECTDB_H__

#include "BllFrameworkExport.h"

#include "Globals.h"
#include "WtObjectDefs.h"

namespace wt {
namespace framework {

class CWtObject;

class FRAMEWORK_EXPORT CWtObjectDb
{
public:

	static CWtObjectDb& Instance();

	WtoHandle AddObject(CWtObject* obj);

	void RemoveObject(WtoHandle hnd);

	CWtObject* GetObject(WtoHandle hnd);

private:
	CWtObjectDb();
	~CWtObjectDb();

	WtObjectsMap m_wtObjs;

	WtoHandle GetNextObjHandle();
};
}
}

#endif /*_WT_WTOBJECTDB_H__*/
