#include <list>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/loggingmacros.h>
#include "log4cplus/consoleappender.h"
#include <log4cplus/fileappender.h>
#include <log4cplus/spi/filter.h>
#include <thread>
#include <chrono>

using namespace log4cplus;
using namespace log4cplus::spi;
using namespace log4cplus::helpers;

enum class LogLevels{
  kNotSet = NOT_SET_LOG_LEVEL,
  kTrace  = TRACE_LOG_LEVEL,
  kDebug  = DEBUG_LOG_LEVEL,
  kInfo   = INFO_LOG_LEVEL,
  kWarn   = WARN_LOG_LEVEL,
  kError  = ERROR_LOG_LEVEL,
  kFatal  = FATAL_LOG_LEVEL,
  kOff	 = OFF_LOG_LEVEL
};
  
struct LogConfigure
{
  LogConfigure():console(true),
		file_path(LOG4CPLUS_TEXT("")),
		max_size(0),
		min_level(LogLevels::kNotSet),
		max_level(LogLevels::kNotSet),
		match_string(LOG4CPLUS_TEXT("")),
		match_string_accept(true),
		modules_accept(true){
      
  }
  bool console;
  tstring file_path;
  int max_size;
  //filter
  LogLevels min_level;
  LogLevels max_level;
  tstring match_string;
  std::vector<tstring> modules;
  bool match_string_accept;
  bool modules_accept;
};

bool InitLog(const LogConfigure& config);
bool InitLog(bool console = true,
	       const tstring& file_path=LOG4CPLUS_TEXT(""),
	       LogLevels min_level=LogLevels::kNotSet,
	       LogLevels max_level=LogLevels::kNotSet,
	       const tstring& match_string=LOG4CPLUS_TEXT("")
	      ){
    LogConfigure config;
    config.console = console;
    config.file_path = file_path;
    config.min_level = min_level;
    config.max_level = max_level;
    config.match_string = match_string;
    return InitLog(config);
}

bool AddAppender(Logger log,const LogConfigure& config){
    if(!log.getAllAppenders().empty()){
        log.removeAllAppenders();
    }
    if(config.console){
        SharedAppenderPtr append(new ConsoleAppender());
        log.addAppender(append);
    }

    if(!config.file_path.empty()){
        SharedAppenderPtr append(new RollingFileAppender(config.file_path));
        log.addAppender(append);
    }
    //layout ,we doesn't support custom layout
    //PatternLayout Detailed Description http://log4cplus.sourceforge.net/docs/html/classlog4cplus_1_1PatternLayout.html
    for(log4cplus::SharedAppenderPtr appender:log.getAllAppenders()){
        log4cplus::tstring pattern = LOG4CPLUS_TEXT("%d{%y/%m/%d %H:%M:%S,%Q} [%t][%i] %-5p %m [%c:%L]%n");
        appender->setLayout( std::auto_ptr<Layout>(new PatternLayout(pattern)) );
    }

    if(log.getAllAppenders().empty()){
        return false;
    }
    return true;
}

FilterPtr CreateFilter(const LogConfigure& config){
    // filter Accept levelmin ~ levelmax
    LogLevelManager& llm = getLogLevelManager();
    Properties properties;
    if(config.min_level != LogLevels::kNotSet){
      properties.setProperty(LOG4CPLUS_TEXT("LogLevelMin"), llm.toString(static_cast<LogLevel>(config.min_level)));
    }
    if(config.max_level != LogLevels::kNotSet){
      properties.setProperty(LOG4CPLUS_TEXT("LogLevelMax"), llm.toString(static_cast<LogLevel>(config.max_level)));
    }
    properties.setProperty(LOG4CPLUS_TEXT("AcceptOnMatch"), LOG4CPLUS_TEXT("false"));
    FilterPtr filter_level(new LogLevelRangeFilter(properties));
    FilterPtr filter_deny(new DenyAllFilter());
    if(!config.match_string.empty()){
    properties.setProperty(LOG4CPLUS_TEXT("StringToMatch"), config.match_string.c_str());
    if(config.match_string_accept){
	properties.setProperty(LOG4CPLUS_TEXT("AcceptOnMatch"), LOG4CPLUS_TEXT("true"));
	FilterPtr filter_string(new StringMatchFilter(properties));
	filter_level->appendFilter(filter_string);
	filter_string->appendFilter(filter_deny);
      }else{
	properties.setProperty(LOG4CPLUS_TEXT("AcceptOnMatch"), LOG4CPLUS_TEXT("false"));
	FilterPtr filter_string(new StringMatchFilter(properties));
	filter_level->appendFilter(filter_string);
      }
    }
    return filter_level;
}
bool InitLog(const LogConfigure& config){
    // default log init
    Logger root = Logger::getRoot();
    if(!AddAppender(root,config)){
	return false;
    }
    FilterPtr filter = CreateFilter(config);
    if(filter == nullptr){
	return false;
    }
    if(config.modules.empty()){
        for(log4cplus::SharedAppenderPtr appender:Logger::getRoot().getAllAppenders()){
	    appender->setFilter(filter);
	}
    }else{
	if(config.modules_accept){
	    // drop all logs first
	    FilterPtr filter_deny(new DenyAllFilter());
	    for(log4cplus::SharedAppenderPtr appender:Logger::getRoot().getAllAppenders()){
		appender->setFilter(filter_deny);
	    }
	    for(tstring logname:config.modules){
		Logger log = Logger::getInstance(logname.c_str());
		if(!AddAppender(log,config)){
		    return false;
		}
		for(log4cplus::SharedAppenderPtr appender:log.getAllAppenders()){
		  appender->setFilter(filter);
		}
	    }
	}else{
	    for(log4cplus::SharedAppenderPtr appender:Logger::getRoot().getAllAppenders()){
		appender->setFilter(filter);
	    }
	    FilterPtr filter_deny(new DenyAllFilter());
	    for(tstring logname:config.modules){
		Logger log = Logger::getInstance(logname.c_str());
		log.setAdditivity(false);
		if(!AddAppender(log,config)){
		    return false;
		}
		for(log4cplus::SharedAppenderPtr appender:log.getAllAppenders()){
		    appender->setFilter(filter_deny);
		}
	    }
	}
      
    }
    return true;
}

int main()
{
    Logger root = Logger::getRoot();
    //InitLog(true,"test.log",TRACE_LOG_LEVEL,WARN_LOG_LEVEL,"N");
    LogConfigure config;
    config.file_path = LOG4CPLUS_TEXT("test");
    config.modules_accept = true;
    InitLog(config);
    LOG4CPLUS_DEBUG(root, LOG4CPLUS_TEXT("This is a DEBUG message"));
    LOG4CPLUS_INFO(root, LOG4CPLUS_TEXT("This is a INFO message"));
    LOG4CPLUS_WARN(root, LOG4CPLUS_TEXT("This is a WARN message"));
    LOG4CPLUS_ERROR(root, LOG4CPLUS_TEXT("This is a ERROR message"));
    LOG4CPLUS_FATAL(root, LOG4CPLUS_TEXT("This is a FATAL message"));
    
    std::thread t([]{
    for(int i=0;i<100;i++){
      Logger test = Logger::getInstance(LOG4CPLUS_TEXT("test"));
      LOG4CPLUS_DEBUG(test, LOG4CPLUS_TEXT("This is a child DEBUG message"));
      LOG4CPLUS_INFO(test, LOG4CPLUS_TEXT("This is a child INFO message"));
      LOG4CPLUS_WARN(test, LOG4CPLUS_TEXT("This is a child WARN message"));
      LOG4CPLUS_ERROR(test, LOG4CPLUS_TEXT("This is a child ERROR message"));
      LOG4CPLUS_FATAL(test, LOG4CPLUS_TEXT("This is a child FATAL message"));
    }
    });
    
    std::thread t2([]{
    for(int i=0;i<100;i++){
      Logger test2 = Logger::getInstance(LOG4CPLUS_TEXT("test2"));
      LOG4CPLUS_DEBUG(test2, "This is a child2 DEBUG message");
      LOG4CPLUS_INFO(test2, "This is a child2 INFO message");
      LOG4CPLUS_WARN(test2, "This is a child2 WARN message");
      LOG4CPLUS_ERROR(test2, "This is a child2 ERROR message");
      LOG4CPLUS_FATAL(test2, "This is a child2 FATAL message");
      
    }
    });
    
    t.join();
    t2.join();
    return 0;
}

