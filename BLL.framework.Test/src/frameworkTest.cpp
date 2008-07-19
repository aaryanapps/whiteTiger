
#include <iostream>

#include "CommandA.h"
#include "TaskManager.h"

#include "Poco/TaskManager.h"
#include "Poco/Observer.h"

using Poco::TaskStartedNotification;
using Poco::TaskCancelledNotification;
using Poco::TaskFinishedNotification;
using Poco::TaskFailedNotification;
using Poco::TaskProgressNotification;

class CommandObserver
{
public:
	CommandObserver()
        {
        }
        
        ~CommandObserver()
        {
                //delete _pException;
        }
        
        void taskStarted(TaskStartedNotification* pNf)
        {
        	std::cout << "Notification -> Started Command: " << pNf->task()->name() << std::endl ;
            pNf->release();
        }
        
        void taskCancelled(TaskCancelledNotification* pNf)
        {
                pNf->release();
        }
        
        void taskFinished(TaskFinishedNotification* pNf)
        {
        	std::cout << "Notification Completed Command: " << pNf->task()->name() << std::endl ;    
                pNf->release();
        }
        
        void taskFailed(TaskFailedNotification* pNf)
        {
                //_pException = pNf->reason().clone();
                pNf->release();
        }

        void taskProgress(TaskProgressNotification* pNf)
        {
        	std::cout << "Notification: Progress of Command: " << pNf->task()->name() 
        			  << " is " 
        			  << pNf->progress() * 100 << "%"
        			  << std::endl ;
                pNf->release();
        }
        
};


int main(int argc, const char* argv[])
{

	
	wt::framework::CTaskManager& tm =  wt::framework::CTaskManager::Instance();
	CommandObserver to;
    tm.addObserver(Poco::Observer<CommandObserver, TaskStartedNotification>(to, &CommandObserver::taskStarted));
    tm.addObserver(Poco::Observer<CommandObserver, TaskCancelledNotification>(to, &CommandObserver::taskCancelled));
    tm.addObserver(Poco::Observer<CommandObserver, TaskFailedNotification>(to, &CommandObserver::taskFailed));
    tm.addObserver(Poco::Observer<CommandObserver, TaskFinishedNotification>(to, &CommandObserver::taskFinished));
    tm.addObserver(Poco::Observer<CommandObserver, TaskProgressNotification>(to, &CommandObserver::taskProgress));
	
	
	CommandA* aCmd1 = new CommandA("Command 1");
	CommandA* aCmd2 = new CommandA("Command 2");
	CommandA* aCmd3 = new CommandA("Command 3");
	CommandA* aCmd4 = new CommandA("Command 4");
	CommandA* aCmd5 = new CommandA("Command 5");
	CommandA* aCmd6 = new CommandA("Command 6");
	CommandA* aCmd7 = new CommandA("Command 7");
	
	aCmd5->SetSleepDuration(1000);
	
	aCmd1->Execute();
	aCmd2->Execute();
	aCmd3->Execute();
	aCmd4->Execute();
	aCmd5->Execute();
	aCmd6->Execute();
	aCmd7->Execute();
	
	std::cout << "Total Task in TaskList: " << tm.count() << std::endl;
	
	tm.joinAll();
	
	std::cout << "All threads executed completely!!" << std::endl;
	
	return 0;
	
}
