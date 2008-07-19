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
	
	virtual void runTask() = 0;	
	
	
	/* Getters - Setters */
	
	bool GetAutoDestroy() {return _mbAutoDestroy;}

	void SetAutoDestroy(bool autoDest) {_mbAutoDestroy = autoDest;}

	bool GetRunInBg() {return _mbRunInBg;}

	void SetRunInBg(bool runBg) {_mbRunInBg = runBg;}
	
	
	/*Handle Notifications*/
	void commandStarted(TaskStartedNotification* pNf);
	
	void commandCancelled(TaskCancelledNotification* pNf);
	
	void commandFinished(TaskFinishedNotification* pNf);
	
	void commandFailed(TaskFailedNotification* pNf);
	
	void commandProgress(TaskProgressNotification* pNf);
	
	
private:
	CCommand();
	
	bool 		_mbAutoDestroy;
	bool		_mbRunInBg;
	bool       	_mbStarted;
    bool       	_mbCancelled;
    bool       	_mbFinished;
    float      	_mfProgress;
	
};
}
}

#endif //_WT_COMMAND_H__

