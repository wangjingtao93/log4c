#ifndef _MYLOG_H_
#define _MYLOG_H_

#include <string.h>
#include <stdlib.h>
#include "log4c.h"
#include <log4c/defs.h>

#define MYLOG_CATEGORY_NAME "log4ctest"       //category name
//#define MYLOG_PRIORITY LOG4C_PRIORITY_WARN

//1.LOG4C_PRIORITY_ERROR
//2.LOG4C_PRIORITY_WARN
//3.LOG4C_PRIORITY_NOTICE
//4.LOG4C_PRIORITY_DEBUG
//5.LOG4C_PRIORITY_TRACE

extern int mylog_init();                     //初始化
extern void log_message(char* file, int line, const char* func,const char* a_format, log4c_priority_level_t MYLOG_PRIORITY,...);//封装函数
extern int mylog_fini();
#define LOG_WARN(fmt,args...) log_message(__FILE__, __LINE__, __FUNCTION__, fmt, LOG4C_PRIORITY_WARN,## args);     //宏定义简化调用
#define LOG_DEBUG(fmt,args...) log_message(__FILE__, __LINE__, __FUNCTION__, fmt, LOG4C_PRIORITY_DEBUG,## args);
#define LOG_NOTICE(fmt,args...) log_message(__FILE__, __LINE__, __FUNCTION__, fmt, LOG4C_PRIORITY_NOTICE,## args);
#define LOG_ERROR(fmt,args...) log_message(__FILE__, __LINE__, __FUNCTION__, fmt, LOG4C_PRIORITY_ERROR,## args);
#define LOG_TRACE(fmt,args...) log_message(__FILE__, __LINE__, __FUNCTION__, fmt, LOG4C_PRIORITY_TRACE,## args);
#endif
