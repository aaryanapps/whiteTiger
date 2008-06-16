#ifndef _WT_COMMAND_H__
#define _WT_COMMAND_H__

//Poco
#include "Poco/Task.h"

//class Poco::Task;

namespace wt {
namespace framework {

class CCommand : public Poco::Task {
public:
	CCommand();
	virtual ~CCommand();
	
	void Execute();
	
	virtual void Reset() = 0;
	
	virtual void runCommand() = 0;

private:
//	Poco::Task*		_mpTask;
	
};
}
}

#endif //_WT_COMMAND_H__

