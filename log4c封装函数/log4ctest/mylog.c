
/*
 *  mylog.c
 *   封装函数，简化调用
 *  Created on: 2019-4-14
 *      Author: root
 */


#include "mylog.h"

const char *format = "[%10s][%4d][%10s()]: ";//日志输出格式，用于拼串

log4c_category_t* mycat = NULL;

/***************************************************************************************************
 *函数名称： int mylog_init()
 *功能描述： log4c初始化
 *输入参数： 无
 *输出参数： 无
 *返 回 值： 0
 ***************************************************************************************************/
int mylog_init()
{
	if (log4c_init() == 1)
	{
		printf("log4c_init() faild");

		return 1;
	}
	mycat = log4c_category_get(MYLOG_CATEGORY_NAME);
	return 0 ;
}

/***************************************************************************************************
 *函数名称： void log_message()
 *功能描述： 封装日志输出函数，简化log4c_category_vlog函数地用
 *输入参数： char* file, int line, const char* func, const char* a_format,  log4c_priority_level_t MYLOG_PRIORITY,...
 *            文件名       ，      行号，  函数名   ， message格式，如“%d%s”,    日志级别priority                  ,可变参数
 *输出参数： 无
 *返 回 值： void
 ***************************************************************************************************/
void log_message(char* file, int line, const char* func, const char* a_format,  log4c_priority_level_t MYLOG_PRIORITY,...)
{
	char *file_info;
	char *new_format;
	size_t info_len;       //long unsigned int
	size_t new_format_len;
	va_list va;            //定义VA_LIST型的变量

	info_len = strlen(format) + 50;             //
	file_info = (char *) malloc(info_len);      //文件信息，函数结尾释放
	sprintf(file_info, format,file, line,func );//格式化字符串（拼串），文件信息包括：文件名+行号+函数名字

	new_format_len = strlen(file_info) + strlen(a_format) + 2;
	new_format = (char *) malloc(new_format_len);
	sprintf(new_format, "%s%s", file_info, a_format);//拼串，将message的格式如“%s,%d”拼在file_info后面，得到新的格式

	va_start(va, a_format);                                     //初始化VA_LIST变量，va指向第一个变参的位置
	log4c_category_vlog(mycat, MYLOG_PRIORITY, new_format, va); //函数调用，写log
	va_end(va);                                                 //防止出现野指针。有始有终，配合va_start使用

	free(file_info);//释放内存
	free(new_format);
}

/***************************************************************************************************
 *函数名称： int mylog_fini()
 *功能描述： log4c释放
 *输入参数： 无
 *输出参数： 无
 *返 回 值： 0
 ***************************************************************************************************/

int mylog_fini()
{
	return(log4c_fini());
}
