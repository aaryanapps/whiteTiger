#ifndef _WT_TASKMANAGER_H__
#define _WT_TASKMANAGER_H__

#include "BllFrameworkExport.h"

//Poco
#include "Poco/TaskManager.h"

namespace wt {
namespace framework {

class FRAMEWORK_EXPORT CCommandManager : public Poco::TaskManager {
public:
	static CCommandManager& Instance();


private:
	CCommandManager();
	~CCommandManager();

};


}
}

#endif //_WT_COMMAND_H__
