#include "StdAfx.h"

#include "WtLogger.h"
#include "Globals.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"


using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;

CWtLoggerFactory::CWtLoggerFactory(std::string& name, Poco::Channel* pCha, int level) :
			Logger(name, pCha, level), m_init(false)
{
	
}

CWtLoggerFactory::~CWtLoggerFactory()
{
	
}

CWtLoggerFactory& CWtLoggerFactory::Instance()
{
	static CWtLoggerFactory* ll = NULL;
	
	if (!ll)
	{

		FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S.%i [%P]:%s:%p: %t"));
	    pFCFile->setChannel(new FileChannel("wtOutput.log"));
	    pFCFile->open();
/*
	    FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%s: %p: %t"));
	    pFCConsole->setChannel(new ConsoleChannel);
	    pFCConsole->open();
*/	    
		std::string tmp("bll");
		ll = new CWtLoggerFactory(tmp,pFCFile, Poco::Message::PRIO_DEBUG);
		//ll->Init();
	}
	
	return *ll;
	
}


bool CWtLoggerFactory::IsLevelSet(uint32_t level)
{
	
	return Logger::get("FileLogger").is(level);
	
}

void CWtLoggerFactory::LogMessage(std::string& logMsg,
						   std::string& src,
						   Poco::Message::Priority level)
{
	Logger& fl = Logger::get("FileLogger");
	if (!fl.is(level))
	{
		return;
	}

	Message msg(src, logMsg, level);
	fl.log(msg);

}

void CWtLoggerFactory::LogMessage(Message& msg)
{
	Logger& fl = Logger::get("FileLogger");
	fl.log(msg);
}


Poco::Logger& CWtLoggerFactory::GetLogger(std::string& logger)
{
	Poco::Logger * l = find(logger);
	if (!l)
	{
		Poco::Logger& ll = Logger::create(logger, getChannel(), getLevel());
		return ll;
	}
	
	return *l;
}

////Private Methods


void CWtLoggerFactory::Init()
{

	if (m_init)
		return;
	
	// set up two channel chains - one to the
    // console and the other one to a log file.
    FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%s: %p: %t"));
    pFCConsole->setChannel(new ConsoleChannel);
    pFCConsole->open();
/*
    FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
    pFCFile->setChannel(new FileChannel("wtOutput.log"));
    pFCFile->open();
*/
    // create two Logger objects - one for
    // each channel chain.
    //Logger::create("", pFCFile, Message::PRIO_INFORMATION);

/*
    Logger& consoleLogger = Logger::create("ConsoleLogger", pFCConsole, Message::PRIO_INFORMATION);
    Logger& fileLogger    = Logger::create("FileLogger", pFCFile, Message::PRIO_WARNING);

    
    // log some messages
    consoleLogger.error("An error message");
    fileLogger.error("An error message");

    consoleLogger.warning("A warning message");
    fileLogger.error("A warning message");

    consoleLogger.information("An information message");
    fileLogger.information("An information message");

    Logger::get("ConsoleLogger").error("Another error message");
*/
    m_init = true;
}
