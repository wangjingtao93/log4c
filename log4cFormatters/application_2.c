/*
* This is one of the log4c example programs.
*
* In this example we link against a shared library that has
* additional formatters and appenders.  This shows how easy it is to
* add in more appenders and formatters to the log4c framework.
*
* With gcc this file is in fact exactly the same as application_1.c--
* only at link time it is linked with a new library.
* With other compilers using explicit initialization, this program needs
* to explicitly tell the custom appender/formatter lib to initialize
* itself and it's appenders and formatters.
*
* 这是log4c示例程序之一。
* 在本例中，我们链接到一个共享库,该库有附加格式化程序和附加程序。他将为我们展示向
* log4c框架中增加更多的Appender和formatters是很容易的。
*
* 对于gcc，这个文件实际上与application_1.c完全相同，只有在链接时，它才与一个新库链接
* 与其他使用显式初始化的编译器一起使用时，要显式地告诉自定义 appenders/formatters
* 程序库初始化自身,以及appenders/formatters
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
#include <winsock.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "log4c.h"

extern int init_examples_lib(void);

#ifdef _WIN32
#if !defined(__MINGW32__) && !defined(__MINGW64__)
int gettimeofday(struct timeval* tp, void* tzp) {
  DWORD t;
  t = timeGetTime();
  tp->tv_sec = t / 1000;
  tp->tv_usec = t % 1000;
  /* 0 indicates that the call succeeded. */
  return 0;
}
#endif

#if !defined(HAVE_SLEEP) || !HAVE_DECL_SLEEP
#define sleep(x) Sleep(x*1000)
#endif

#endif /* _WIN32 */


int main(int argc, char** argv)
{
  struct timeval start_time;
  struct timeval now_time;
  int looptime = 0;
  log4c_category_t* mycat = NULL;

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

  /*
  * Here, if using explicit initialization (as opposed to implicit via the
    * init phase of the library) it's important to initialize the custom appenders
  * and layouts before calling log4c_init().
  * This is because when log4c_init() parses the config file it looks for the
  * types mentioned in the file to set up the relations between categories,
  * appenders and layouts.  If it does not find a coresponding type in the
  * internal hash tables, it creates one with that type name, but the function
  * table is not set up--so that at log time nothing happens.
  *
  * 这里，如果使用显式初始化(而不是通过库的init阶段隐式地执行),在调用log4c init()之前
  * 初始化自定义的appenders和 layouts非常重要。
  * 这是因为当log4c_init()解析配置文件时，它寻找文件中提到的类型来建立categories,
  * appenders and layouts之间的关系，如果在内部哈希表中没有找到相应的类型，它创建
  * 一个具有该类型名称的，但函数表没有设置，所以在log时间什么都没有发生。
  */

  init_examples_lib();

  log4c_init();

  /*
  * You could choose to wrap the log4c_category_log with some macro
  * that then calls an accessor to get your pre-created category
  * mycat and then logs to it.  But for now we just focus on the fact
  * that we are using log4crc to have this application use the new
  * formatters and appenders we wrote as examples
  *
  * 您可以选择用一些宏封装log4c_category_log然后调用一个访问器来获得预先创建
  * category mycat然后对其进行日志记录。但现在我们只关注，我们使用log4crc
  * 让这个应用程序使用使用我们作为示例编写新的formatters and appenders
  */
  mycat = log4c_category_get("six13log.log.app.application2");

  gettimeofday(&start_time, NULL);
  gettimeofday(&now_time, NULL);

  while ( (now_time.tv_sec - start_time.tv_sec) < looptime)
  {
    log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "Debugging app 2");
    log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
      "some error from app2 at line %d in file %s",
      __LINE__, __FILE__);
    sleep(3);

    gettimeofday(&now_time, NULL);
  }

  /* Explicitly call the log4c cleanup routine */
  if ( log4c_fini()){
    printf("log4c_fini() failed");
  }

  return 0;
}
