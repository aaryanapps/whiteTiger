#ifndef _WT_COMMAND_H__
#define _WT_COMMAND_H__

#include <string>

//Poco
#include "Poco/Task.h"
#include "Poco/TaskNotification.h"


using Poco::TaskStartedNotification;
using Poco::TaskCancelledNotification;
using Poco::TaskFinishedNotification;
using Poco::TaskFailedNotification;
using Poco::TaskProgressNotification;

namespace wt {
namespace framework {

class CCommand : public Poco::Task {
public:
	CCommand(const std::string& strImage = "Base Command");
	virtual ~CCommand();
	
	void Execute();
		
	virtual void Reset() = 0;
	
	void runTask() = 0;	
	
	bool GetAutoDestroy() {return _mbAutoDestroy;}

	void SetAutoDestroy(bool autoDest) {_mbAutoDestroy = autoDest;}

	

private:
	CCommand();
	
	bool 		_mbAutoDestroy;
    bool       	_mbStarted;
    bool       	_mbCancelled;
    bool       	_mbFinished;
    float      	_mfProgress;
	
};
}
}

#endif //_WT_COMMAND_H__

