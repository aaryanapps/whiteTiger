#ifndef _WTOBJECTDEFS_H__
#define _WTOBJECTDEFS_H__

#include "Globals.h"
#include "FastDelegate.h"

namespace wt {
namespace framework {
	class CWtObject;

	typedef uint32_t WtoClassId;

	typedef uint32_t WtoType;

	typedef std::vector<WtoType> WtoTypeIdsVec;

	typedef std::set<WtoType> WtoTypeIdsSet;

	typedef uint32_t WtoHandle;

	typedef std::map<WtoHandle, CWtObject*> WtObjectsMap;

	typedef std::vector<CWtObject*> WtoVec;

	typedef std::vector<WtoHandle> WtoHndVec;

	typedef fastdelegate::FastDelegate0<CWtObject*> WtObjCreator;

}
}

#define WTOBJECT_HND_NULL 0

#define WTOBJECT_CLASSID_NULL 0


#endif /*_WTOBJECTDEFS_H__*/
