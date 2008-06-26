#ifndef _WT_COMMANDNOTIFICATIONMANAGER_H__
#define _WT_COMMANDNOTIFICATIONMANAGER_H__

//Poco
#include "Poco/Task.h"
#include "Poco/TaskNotification.h"
#include "Poco/AutoPtr.h"


using Poco::TaskStartedNotification;
using Poco::TaskCancelledNotification;
using Poco::TaskFinishedNotification;
using Poco::TaskFailedNotification;
using Poco::TaskProgressNotification;

namespace wt {
namespace framework {

enum NotificationType {
	CMD_START = 1,
	CMD_FINISHED,
	CMD_FAILED,
	CMD_CANCELLED,
	CMD_PROGRESS
};

class CCommandNotificationManager {

public:
	
	static CCommandNotificationManager& Instance();
	
	//bool RegisterNotification(NotificationType, );

	
	/*Handle Notifications*/
	void commandStarted(const Poco::AutoPtr<TaskStartedNotification>& pNf);
	
	void commandCancelled(const Poco::AutoPtr<TaskCancelledNotification>& pNf);
	
	void commandFinished(const Poco::AutoPtr<TaskFinishedNotification>& pNf);
	
	void commandFailed(const Poco::AutoPtr<TaskFailedNotification>& pNf);
	
	void commandProgress(const Poco::AutoPtr<TaskProgressNotification>& pNf);
	
	
private:
	CCommandNotificationManager();
	~CCommandNotificationManager();
};

}
}

#endif //_WT_COMMANDNOTIFICATIONMANAGER_H__
