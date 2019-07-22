/******************************************************************************
 *
 * Part of the log4c examples.
 *
 * Along with example_appenders.c this file is used to create a small
 * library of custom appenders and formatters.
 *
 * This library is excercised using application_2 and a sample log4crc
 * config file.
 *
 * log4c examples的一部分
 *
 * 例子example_appenders.c可以用来创建一个自定义的appenders and formatters的小型库
 *
 * 这个库是使用application_2 和 a sample log4crc 运行
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <log4c.h>

/* Defined in example_appenders.c
*
* 在example_appenders.c定义
*/
extern int init_example_appenders(void);


/**********************************************************************
 *
 * Formatted to put [category] out at the front of the message
 *
 *格式化为将[类别]放在消息的前面
 **********************************************************************/
static const char* cat_format(
    const log4c_layout_t*       a_layout,
    const log4c_logging_event_t*a_event)
{

  /*
   * 获得当前时间，如2019-04-22 16:40:32
   */
    char BuffTime[1024];

  	time_t timep;
	  struct tm *p;
  	time(&timep);
  	p = gmtime(&timep);

	  int yearNow = 1900 + p->tm_year;
  	int monthNow = 1 + p->tm_mon;
  	int hourNow = 8 + p->tm_hour;

	  sprintf(BuffTime, "%d-%d-%d %d:%d:%d", yearNow, monthNow, p->tm_mday, hourNow, p->tm_min, p->tm_sec);

    static char buffer[4096];

    /*
     * For this formatter we put the category up front in the log message
     * 对于这个格式化程序，我们将类别放在日志消息的前面
     */
    sprintf(buffer, "[%s][%s][LINE:%d][FILE:%s] %s",BuffTime, a_event->evt_category,
    	a_event->evt_loc->loc_line, a_event->evt_loc->loc_file, a_event->evt_msg);

    return buffer;
}

const log4c_layout_type_t log4c_layout_type_cat  = {
   "s13_cat",
   cat_format,
};


static const char* none_format(
    const log4c_layout_t*       a_layout,
    const log4c_logging_event_t*a_event)
{
    static char buffer[4096];
    return buffer;
}

const log4c_layout_type_t log4c_layout_type_none  = {
  "s13_none",
  none_format,
};


/**********************************************************************/
/*
 * Formatted to mock up an xml format.
 *
 * 格式化为模拟xml格式。
 **********************************************************************/
static const char* xml_format(
    const log4c_layout_t*       a_layout,
    const log4c_logging_event_t*a_event)
{
    static char buffer[4096];

    /*
     * For this formatter we put the category up front in the log message
     */
    sprintf(buffer, "<logmessage><category>%s</category><message>%s</message></logmessage>", a_event->evt_category,  a_event->evt_msg);

    return buffer;
}

const log4c_layout_type_t log4c_layout_type_xml = {
    "s13_xml",
     xml_format,
};




/*****************************/
/*
 * Here provide an init routine for this lib
 *
 * 这里为这个库提供一个init例程
******************************/
static const log4c_layout_type_t * const layout_types[] = {
    &log4c_layout_type_xml,
    &log4c_layout_type_none,
    &log4c_layout_type_cat
};
static int nlayout_types =
	(int)(sizeof(layout_types) / sizeof(layout_types[0]));


int init_example_formatters(){

  int rc = 0; int i = 0;

  for (i = 0; i < nlayout_types; i++)
     log4c_layout_type_set(layout_types[i]);

  return(rc);

}


int init_examples_lib() {

	init_example_formatters();
	init_example_appenders();

  return(0);
}
