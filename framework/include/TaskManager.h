#ifndef _WT_TASKMANAGER_H__
#define _WT_TASKMANAGER_H__

//Poco
#include "Poco/TaskManager.h"


namespace wt {
namespace framework {

class CTaskManager : public Poco::TaskManager {
public:
	CTaskManager& Instance();
	
	
	
private:
	CTaskManager();
	~CTaskManager();
	
};


}
}

#endif //_WT_COMMAND_H__