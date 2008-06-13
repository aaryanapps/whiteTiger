#ifndef _WTOBJECTDEFS_H__
#define _WTOBJECTDEFS_H__

#include "Globals.h"

class CWtObject;

typedef uint32_t WtoHandle;
typedef std::map<WtoHandle, CWtObject*> WtObjectsMap;
typedef std::vector<CWtObject*> WtoVec;
#define WTOBJECT_HND_NULL 0



#endif /*_WTOBJECTDEFS_H__*/
