
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

struct LogConfigure
{
  LogConfigure():console(true),
		file_path(""),
		max_size(0),
		daily_roll((DailyRollingFileSchedule)-1),
		min_level(TRACE_LOG_LEVEL),
		max_level(FATAL_LOG_LEVEL),
		match_string(""),
		match_string_accept(true),
		modules_accept(true){
      
  }
  bool console;
  std::string file_path;
  int max_size;
  DailyRollingFileSchedule daily_roll;
  //filter
  LogLevel min_level;
  LogLevel max_level;
  std::string match_string;
  std::list<std::string> modules;
  bool match_string_accept;
  bool modules_accept;
};

bool InitLog(const LogConfigure& config);
bool InitLog(bool console = true,
	       const std::string& file_path="",
	       LogLevel min_level=NOT_SET_LOG_LEVEL,
	       LogLevel max_level=NOT_SET_LOG_LEVEL,
	       const std::string& match_string=""
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
    if(config.console){
	SharedAppenderPtr append(new ConsoleAppender());
	append->setName("CONSOLE");
	log.addAppender(append);
    }
    
    if(!config.file_path.empty()){
	SharedAppenderPtr append(new RollingFileAppender(config.file_path.c_str()));
	append->setName("ROLL");
	log.addAppender(append);
    }
    
    if(config.daily_roll != -1){
	SharedAppenderPtr append(new DailyRollingFileAppender(config.file_path.c_str(),config.daily_roll));
	append->setName("DAILYROLL");
	log.addAppender(append);
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
    if(config.min_level != NOT_SET_LOG_LEVEL){
      properties.setProperty("LogLevelMin", llm.toString(config.min_level));
    }
    if(config.max_level != NOT_SET_LOG_LEVEL){
      properties.setProperty("LogLevelMax", llm.toString(config.max_level));
    }
    properties.setProperty("AcceptOnMatch", "false");
    FilterPtr filter_level(new LogLevelRangeFilter(properties));
    FilterPtr filter_deny(new DenyAllFilter());
    if(!config.match_string.empty()){
    properties.setProperty("StringToMatch",config.match_string.c_str());
    if(config.match_string_accept){
	properties.setProperty("AcceptOnMatch", "true");
	FilterPtr filter_string(new StringMatchFilter(properties));
	filter_level->appendFilter(filter_string);
	filter_string->appendFilter(filter_deny);
      }else{
	properties.setProperty("AcceptOnMatch", "false");
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
    if(config.modules_accept){
	// drop all logs first
	FilterPtr filter_deny(new DenyAllFilter());
	for(log4cplus::SharedAppenderPtr appender:Logger::getRoot().getAllAppenders()){
	    appender->setFilter(filter_deny);
	}
	for(std::string logname:config.modules){
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
	for(std::string logname:config.modules){
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
    return true;
}

int main()
{
    Logger root = Logger::getRoot();
    //InitLog(true,"test.log",TRACE_LOG_LEVEL,WARN_LOG_LEVEL,"N");
    LogConfigure config;
    config.modules_accept = true;
    config.modules.push_back("test");
    config.modules.push_back("test2");
    InitLog(config);
    LOG4CPLUS_DEBUG(root, "This is a DEBUG message");
    LOG4CPLUS_INFO(root, "This is a INFO message");
    LOG4CPLUS_WARN(root, "This is a WARN message");
    LOG4CPLUS_ERROR(root, "This is a ERROR message");
    LOG4CPLUS_FATAL(root, "This is a FATAL message");
    
    std::thread t([]{
    for(int i=0;i<100;i++){
      Logger test = Logger::getInstance("test");
      LOG4CPLUS_DEBUG(test, "This is a child DEBUG message");
      LOG4CPLUS_INFO(test, "This is a child INFO message");
      LOG4CPLUS_WARN(test, "This is a child WARN message");
      LOG4CPLUS_ERROR(test, "This is a child ERROR message");
      LOG4CPLUS_FATAL(test, "This is a child FATAL message");
    }
    });
    
    std::thread t2([]{
    for(int i=0;i<100;i++){
      Logger test2 = Logger::getInstance("test2");
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

