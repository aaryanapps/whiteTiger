#ifndef _WTLOGGERFACTORY_H__
#define _WTLOGGERFACTORY_H__

#include "BllFrameworkExport.h"

#include "Globals.h"
#include "Poco/Message.h"
#include "Poco/Logger.h"

class FRAMEWORK_EXPORT CWtLoggerFactory : public Poco::Logger {

public:
	CWtLoggerFactory(std::string& name, Poco::Channel* pCha, int level);
	~CWtLoggerFactory();

	static CWtLoggerFactory& Instance();

	bool IsLevelSet(uint32_t level);

	void LogMessage(std::string& logMsg, std::string& src, Poco::Message::Priority level);

	void LogMessage(Poco::Message& msg);

	Poco::Logger& GetLogger(std::string& logger);
private:
	CWtLoggerFactory();
	bool m_init;
	void Init();

};

// Create a static logger function (fnName) for the specified logger/category name (loggerName)
#define DEFINE_STATIC_LOGGER(loggerName, fnName) \
 static Poco::Logger& fnName() \
 { \
	std::stringstream ss ; \
	ss << loggerName ; \
	std::string _n = ss.str() ;\
    return CWtLoggerFactory::Instance().GetLogger(_n); \
 }


// Log at ERROR level for the specified logger object
#define LOG_ERROR(logger, logEvent) \
if (logger.error()) \
{ \
	std::ostringstream str; \
	str << logEvent; \
	logger.error(str.str()); \
}

// Log at WARN level for the specified logger object
#define LOG_WARN(logger, logEvent) \
if (logger.warning()) \
{ \
	std::ostringstream str; \
	str << logEvent; \
	logger.warning(str.str()); \
}

// Log at DEBUG level for the specified logger object
#define LOG_DEBUG(logger, logEvent) \
if (logger.debug()) \
{ \
	std::ostringstream str; \
	str << logEvent; \
	logger.debug(str.str()); \
}

// Log at INFO level for the specified logger object
#define LOG_INFO(logger, logEvent) \
if (logger.information()) \
{ \
	std::ostringstream str; \
	str << logEvent; \
	logger.information(str.str()); \
}


#endif /*_WTLOGGERFACTORY_H__*/
