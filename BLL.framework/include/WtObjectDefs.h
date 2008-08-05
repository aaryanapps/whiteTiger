#ifndef _WTOBJECTDEFS_H__
#define _WTOBJECTDEFS_H__

#include "Globals.h"

namespace wt {
namespace framework {
	class CWtObject;
}
}

typedef uint32_t WtoHandle;
typedef std::map<WtoHandle, wt::framework::CWtObject*> WtObjectsMap;
typedef std::vector<wt::framework::CWtObject*> WtoVec;
#define WTOBJECT_HND_NULL 0



#endif /*_WTOBJECTDEFS_H__*/
