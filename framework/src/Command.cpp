
#include "Command.h"
#include "TaskManager.h"

using namespace wt::framework;

CCommand::CCommand(const std::string& cName) :
			Poco::Task(cName), 
			_mbAutoDestroy(true),
			_mbStarted(false),
			_mbCancelled(false),
			_mbFinished(false),
			_mfProgress(0.0)
{
	
}

CCommand::~CCommand()
{
	
}

void CCommand::Execute()
{
	//Execute the command
	if (!_mbAutoDestroy)
	{
		duplicate();
	}
	
	//Add the command to Task Manager Queue
	CTaskManager& tm = CTaskManager::Instance();
	
	tm.start((Poco::Task*)this);
	
	
	//Register callbacks for notifications
	
	
}

void CCommand::runTask()
{
	bool runCommand();
	return ;
}



void CCommand::commandStarted(TaskStartedNotification* pNf)
{
        _mbStarted = true;
        pNf->release();
}

void CCommand::commandCancelled(TaskCancelledNotification* pNf)
{
        _mbCancelled = true;
        pNf->release();
}

void CCommand::commandFinished(TaskFinishedNotification* pNf)
{
        _mbFinished = true;
        pNf->release();
}

void CCommand::commandFailed(TaskFailedNotification* pNf)
{
        //_pException = pNf->reason().clone();
        pNf->release();
}

void CCommand::commandProgress(TaskProgressNotification* pNf)
{
        _mfProgress = pNf->progress();
        pNf->release();
}


