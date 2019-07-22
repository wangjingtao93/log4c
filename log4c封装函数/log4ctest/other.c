/*
 *  other.c
  *    示例函数，调用封装的打印日志函数
 *  Created on: 2019-4-14
 *      Author: root
 */

#include "mylog.h"
#include "other.h"




void otherFunc(void)
{
	LOG_WARN("%s","Enter Warn");
	LOG_DEBUG("%s","Enter Debug");
}

