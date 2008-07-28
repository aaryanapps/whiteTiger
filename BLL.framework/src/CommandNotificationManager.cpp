#include "StdAfx.h"

#include "CommandNotificationManager.h"
#include "CommandManager.h"

#include "Poco/AutoPtr.h"
#include "Poco/NObserver.h"

using namespace wt::framework;

CCommandNotificationManager::CCommandNotificationManager()
{

}

CCommandNotificationManager::~CCommandNotificationManager()
{

}

CCommandNotificationManager&
CCommandNotificationManager::Instance()
{
	static CCommandNotificationManager* cnm;
	static bool _init = false;

	if (!_init)
	{
		cnm = new CCommandNotificationManager();

		//Register observers with Task Manager.
		wt::framework::CCommandManager& tm =  wt::framework::CCommandManager::Instance();
	    tm.addObserver(Poco::NObserver<CCommandNotificationManager, TaskStartedNotification>(*cnm, &CCommandNotificationManager::commandStarted));
	    tm.addObserver(Poco::NObserver<CCommandNotificationManager, TaskCancelledNotification>(*cnm, &CCommandNotificationManager::commandCancelled));
	    tm.addObserver(Poco::NObserver<CCommandNotificationManager, TaskFailedNotification>(*cnm, &CCommandNotificationManager::commandFailed));
	    tm.addObserver(Poco::NObserver<CCommandNotificationManager, TaskFinishedNotification>(*cnm, &CCommandNotificationManager::commandFinished));
	    tm.addObserver(Poco::NObserver<CCommandNotificationManager, TaskProgressNotification>(*cnm, &CCommandNotificationManager::commandProgress));

		_init = true;
	}

	return *cnm;
}

void CCommandNotificationManager::commandStarted(const Poco::AutoPtr<TaskStartedNotification>& pNf)
{
	//Read the Command(task) handle.
	//If any registered observers, fire delegates
}


void CCommandNotificationManager::commandCancelled(
		const Poco::AutoPtr<TaskCancelledNotification>& pNf
		)
{
	//Read the Command(task) handle.
	//If any registered observers, fire delegates
}


void CCommandNotificationManager::commandFinished(
		const Poco::AutoPtr<TaskFinishedNotification>& pNf
		)
{
	//Read the Command(task) handle.
	//If any registered observers, fire delegates
}


void CCommandNotificationManager::commandFailed(
		const Poco::AutoPtr<TaskFailedNotification>& pNf
		)
{
	//Read the Command(task) handle.
	//If any registered observers, fire delegates

}


void CCommandNotificationManager::commandProgress(
		const Poco::AutoPtr<TaskProgressNotification>& pNf
		)
{
	//Read the Command(task) handle.
	//If any registered observers, fire delegates
}

