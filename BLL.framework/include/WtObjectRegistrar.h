/*
 * WtObjectRegistrar.h
 *
 *  Created on: Aug 12, 2008
 *      Author: saumil
 */

#ifndef _WT_WTOBJECTREGISTRAR_H_
#define _WT_WTOBJECTREGISTRAR_H_

#include "BllFrameworkExport.h"
#include "WtObjectDefs.h"
#include "Globals.h"

namespace wt {
namespace framework {

typedef std::map<uint32_t,WtObjCreator> WtoRegistry ;

class FRAMEWORK_EXPORT CWtObjectRegistrar {

public:
	static 	CWtObjectRegistrar& Instance();

	uint32_t 	RegisterCreator(uint32_t classId, WtObjCreator wtCrt);

	bool 		IsValidClassId(uint32_t id);

	CWtObject*	CreateWtObject(uint32_t classId);

private:
	CWtObjectRegistrar();
	~CWtObjectRegistrar();

	WtoRegistry*	GetRegistry();

};

}
}


#endif /* _WT_WTOBJECTREGISTRAR_H_ */
