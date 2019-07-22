/*
* 这个例子将使用宏定义简化函数log4c_category_log的使用
*
* This is one of log4c example programs.
*
* Notice how no relationships between the category and a certain
* priority, appender, or formatter are coded here.  These are all left
* to the log4crc config file so they can be chaned without recompiling
*
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "log4c.h"

//使用宏定义简化调用，这里只列举了DEBUG和INFO两种，
//可以继续用同样的方式，封装其他的日志类型
#define LOG_INFO(category, msg, args...) \
{ \
	const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL); \
	log4c_category_log_locinfo(mycat, &locinfo, LOG4C_PRIORITY_INFO, msg, ##args); \
}

#define LOG_DEBUG(category, msg, args...) \
{ \
	const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL); \
       	log4c_category_log_locinfo(mycat, &locinfo, LOG4C_PRIORITY_DEBUG, msg, ##args); \
}

#define LOG_ERROR(category, msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    log4c_category_log_locinfo(mycat, &locinfo, LOG4C_PRIORITY_ERROR, msg, ##args); \
    }

#define LOG_WARN(category, msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    log4c_category_log_locinfo(mycat, &locinfo, LOG4C_PRIORITY_WARN, msg, ##args); \
    }


#define LOG_TRACE(category, msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    log4c_category_log_locinfo(mycat, &locinfo, LOG4C_PRIORITY_TRACE, msg, ##args); \
    }


int main(int argc, char** argv)
{
  struct timeval start_time;
  struct timeval now_time;
  int looptime = 0;
  log4c_category_t* mycat = NULL;
  int i = 0;

  if (argc < 2)
  {
    printf("usage: %s loop_time_in_seconds\n",argv[0]);
    exit (1);
  }
  if (sscanf(argv[1],"%d",&looptime) != 1)
  {
    printf("could not convert %s to number of seconds to loop\n",argv[1]);
    exit(1);
  }

  /* You could put your category class into a file with a wrapper macro
  * to make calling it easier and more consistent
  */

  log4c_init();
  mycat = log4c_category_get("six13log.log.app.application1");

  gettimeofday(&start_time, NULL);
  gettimeofday(&now_time, NULL);
  i = 0;
  while ( (now_time.tv_sec - start_time.tv_sec) < looptime)
  {
    log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "Debugging app 1 - loop %d", i);
    log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
      "some error from app1 at line %d in file %s - loop %d",
      __LINE__, __FILE__, i);


    LOG_INFO(mycat, "hello info");    //直接使用宏定义调用
    LOG_DEBUG(mycat, "Hello World!"); //直接使用宏定义调用

    LOG_DEBUG(mycat,"Debugging app 1 - loop %d",i);//直接使用宏定义调用

    sleep(3);

    gettimeofday(&now_time, NULL);
    i++;
  }

  /* Explicitly call the log4c cleanup routine */
  if ( log4c_fini()){
    printf("log4c_fini() failed");
  }

  return 0;
}
