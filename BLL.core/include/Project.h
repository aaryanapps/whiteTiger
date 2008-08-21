/*
 * Project.h
 *
 *  Created on: Aug 14, 2008
 *      Author: smehta
 */

#ifndef _WT_PROJECT_H_
#define _WT_PROJECT_H_

#include "Globals.h"
#include "WtObject.h"
#include "BllCoreExport.h"

namespace wt {
namespace core {

class CProject : public wt::framework::CWtObject {

public:
	static CProject& Instance();

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static CWtObject* Create();

private:
	CProject();
	~CProject();

	static uint32_t m_classId;

};

}
}

#endif /* _WT_PROJECT_H_ */
