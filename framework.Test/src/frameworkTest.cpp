
#include <iostream>

#include "CommandA.h"
#include "Poco/TaskManager.h"
#include "TaskManager.h"

int main(int argc, const char* argv[])
{
	
	CommandA* aCmd1 = new CommandA("A command 1");
	CommandA* aCmd2 = new CommandA("A command 2");
	CommandA* aCmd3 = new CommandA("A command 3");
	CommandA* aCmd4 = new CommandA("A command 4");
	CommandA* aCmd5 = new CommandA("A command 5");
	CommandA* aCmd6 = new CommandA("A command 6");
	CommandA* aCmd7 = new CommandA("A command 7");
	
	
	aCmd1->Execute();
	aCmd2->Execute();
	aCmd3->Execute();
	aCmd4->Execute();
	aCmd5->Execute();
	aCmd6->Execute();
	aCmd7->Execute();
	
	wt::framework::CTaskManager& tm =  wt::framework::CTaskManager::Instance();

	std::cout << "Total Task in TaskList: " << tm.count() << std::endl;
	
	tm.joinAll();
	
	std::cout << "All threads executed completely!!" << std::endl;
	
	return 0;
	
}
