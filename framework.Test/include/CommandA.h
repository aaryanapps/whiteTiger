#ifndef _WT_COMMANDA_H__
#define _WT_COMMANDA_H__

#include <string>
#include "Command.h"

#include "Poco/Event.h"

class CommandA : public wt::framework::CCommand {
	
public:
	CommandA(const std::string& cName);
	virtual ~CommandA();
	
	void Reset();
	
	void runTask();		
	
	void SetSleepDuration(int dur) {_sleepDuration = dur ;}
	
	int GetSleepDuration(){return _sleepDuration;}
	
private:
	CommandA();
	
	Poco::Event _event;
	bool  		_fail;
	int			_sleepDuration;
	
};




#endif //_WT_COMMANDA_H__
