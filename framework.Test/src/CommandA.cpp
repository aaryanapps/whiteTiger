
#include "CommandA.h"
#include <iostream>

using namespace wt::framework;

CommandA::CommandA(const std::string& cName) : 
					CCommand(cName)
{
	
}

CommandA::CommandA(): 
			CCommand("Command A")
{
	
}

CommandA::~CommandA()
{
	
}

void CommandA::Reset()
{
	return;
}

void CommandA::runTask()
{
	std::cout << "Started Command: " << this->name() << std::endl ;
    _event.wait();
    setProgress(0.5);
    _event.wait();
    if (isCancelled())
            return;
//    if (_fail)
//            throw SystemException("warp core breach detected");
    setProgress(1.0);
    _event.wait();
	std::cout << "Completed Command: " << this->name() << std::endl ;
	
	return;
}

