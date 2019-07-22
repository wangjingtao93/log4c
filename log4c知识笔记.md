#log4c知识笔记

##暂未排版

目前找到了log4c有三个版本，github上下载的master版本咱不会安装，还找到了1.2.1和1.2.4两个版本。

首先我先尝试1.2.1版本，参考[log4c日志库在Linux中的使用](https://www.linuxidc.com/Linux/2011-02/32560p2.htm)

##问题汇总

*第一次安装编译失败*，可能原因：./configure时没有指定--prefix。make & make install之后,在/usr/local/lib没有下看到liblog4cplus.a，在/usr/local/include下有个liblog4cplus文件夹---最后否定不是此原因

*第二次安装编译成功，但是跑example时初始化失败*。

*历经艰险，终于成功了*，<font color='red'>错误原因</font>：log4crx配置错误，有一行的Category的name修改对。

*这是一个巨坑*，一定要make install之后，apt install ...
，apt install先安装会出现初始化失败，如果make install之后没有执行apt install，虽然可以编译成功，但执行程序时会出现`./application_c: error while loading shared libraries: liblog4c.so.3: cannot open shared object file: No such file or directory`没有库的问题。
##安装的是1.2.4版本

1. ubuntu系统

*首先安装log4c*

*下载源码*

[源码的网址](https://sourceforge.net/projects/log4c/files/log4c/1.2.4/log4c-1.2.4.tar.gz/download?use_mirror=jaist)，这里下载的是log4c-1.2.4版本。

*编译*
  - ./configure   #有的版本说执行命令./configure --prefix=/usr/local/log4c，个人认为没必要在configure加--prefix参数
  - make   #编译即可，make install安装

*make install只后要apt install安装*
  -  apt search log4c- ####搜索log4c的安装包，比如此时搜索出的是liblog4c-dev、liblog4c-doc

  - apt install liblog4c-dev   ####安装其中一个就好
*跑example*

-  里面的例子可以直接执行，之前已经make编译过。
-  注意修改log4crc里的参数，要匹配执行的例子





##log4c概述

下面的笔记参见[Log4c学习笔记](https://blog.csdn.net/kingsong0816/article/details/6029863
)以及[google网址](https://www.cnblogs.com/jyli/archive/2010/02/11/1660606.html)

log4cpp&log4Cplus C++ 移植性差些

log4C是C的日志库，基本都是C的，纯粹，移植性好

注意三个重要的概念：**Category,Appender,Loyout**.

*Category*用来区分不同的日志，在一个程序中，我们可以通过Category指定很多不同的日志

*Appender*可以用来描述输出流，通过Category来指定一个Appender，可以指定讲log信息输出到什么地方去，比如：stdout、stderr、rollingfile等等

Layout用来指定日志信息的格式，通过为Appender指定一个Layout可以决定决定log信息以何种格式输出，比如是否带时间戳、是否带位置信息，以及他们在log信息的输出格式。

<font color='red'>三者的关系</font>：一个category需要为其指定一个Appender，一个Appender需要为其指定一个Layout。

另外*文件的输出策略*rollingpolice，用于描述文件文件输出的配置策略。

##关于配置

例如一个配置文件[log4c配置文件](log4c配置文件.md)
```C
<!DOCTYPE log4c SYSTEM "">
<log4c version="1.2.0">
　　<config>
　　　　<bufsize>0</bufsize>
　　　　<debug level="0"/>
　　　　<nocleanup>0</nocleanup>
　　</config>
　　
　　<layout name="dated" type="dated_l"/>
　　
　　<!-- appenders ===================================== -->
　　　　<appender name="LoadBusinessLog" type="rollingfile" logdir="../etc/log"
　　　　　　　prefix="LoadBusiness-" layout="dated_l"　rollingpolicy="Policy1" />
　
　　　 <appender name="CataRollingFileAppender" type="rollingfile" logdir="../etc/log/"
　　　　　　 prefix="testLog"　layout="dated"　rollingpolicy="RollingPolicy" />

　　　　<!-- category ========================================= -->
　　　　<category name="root" priority="notice"/>
　　　　<category name="framework" priority="info" appender="FrameLog" />
　　　　<category name="test.log" priority="trace" appender="CataRollingFileAppender" />

　　　　<!-- policy ======================================= -->
　　　　<rollingpolicy name="Policy1" type="timewin" timetype="1" maxnum="10" />
　　　　<rollingpolicy name="RollingPolicy" type="sizewin" maxsize="102400" maxnum="10" />
</log4c>

---------------------
```
*category、Appender、layout三者之间的关系*：一个category需要为其指定一个Appender,一个Appender需要为其指定一个Layout。Log4crc中提供了集中默认类型的appender和layout。


###Category

name:日志名称

priority:日志优先级，共有fatal、alrt、crit、error、warn、notice、info、debug、和unknown共11个级别，其级别逐渐递增，记录在日志中的数据为小于等于指定级别的数据。

appender:输出流类型名称，为appender节点的name属性的值。

###appender
name: 输出流名称

type:输出流类型，共有stream、syslog、rollingfile三大类。

layout:输出日志的格式名称，为layout节点的names属性的值。

rolligpolicy:输出日志文件配置策略名称，为rollingpolicy节点的name属性的值。rollingpolicy的timewin类型的日志为自定义类型。

###layout

name:输出日志的格式名称

type:输出日志格式的类型，共有base 、dated、dated_l等格式类型，对于自定义类型也有配置在这里，否则不能够加载。
```C
base：%P %c - %m/n
　　　　 "%P" 日志信息的优先级
　　　　 "%c" 日志的名称
　　　　 "%m" 日志信息内容
dated：%d %P %c - %m/n
　　　　　"%d" 日志信息产生的时间，UTC格式yyyymmdd hh:mm:ss.mis
　　　　 "%P" 日志信息的优先级
　　　　 "%c" 日志的名称
　　　　 "%m" 日志信息内容
dated_l：%d %P %c - %m/n　（源代码里面没有，自己增加的）
　　　　 "%d" 日志信息产生的时间，本地时间格式yyyymmdd hh:mm:ss
　　　　 "%P" 日志信息的优先级
　　　　 "%c" 日志的名称
　　　　 "%m"日志信息内容
```

###rolligpolicy
name:日志我呢见输出的配置策略名称.

type：日子文件输出的配置策略类型，有sizewen一种类型

maxsize:输出文件的最大值，默认值为20kb.

maxnum:保存的历史日志文件总数。默认值为5。

###<font color='red'>配置文件的路径</font>

${ LOG4C_RCPATH }/log4crc　　//环境变量中设置的配置文件夹下log4crc

${HOME}/.log4crc　　　　　　 //HOME文件夹下log4crc

/log4crc　　　　　　　　　　//当前可执行文件夹下log4crc

##log4c基本使用

**头文件**（直接引用log4c.h程序编译出错，因此只引用需要的头文件）

```C
#include <log4c/init.h>
#include <log4c/category.h>
```

cpp文件
//初始化
log4c_init();
//获取一个已有的category
`log4c_category_t* mycat = log4c_category_get("cata.log ");`
//用该category进行日志输出，优先级为DEBUG，输出信息为 "Hello World!"
`log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "Hello World!");`
//析构
log4c_fini();

//在日志输出过程中可以进行格式化输出：
`log4c_category_log(mycat, LOG4C_PRIORITY_ERROR, "Error code = %d", 12345);`
//对于格式化输出也可以有如下写法：
```C
void CLog::Trace(const char * format, ... )
{
　　 if (log4c_category_is_priority_enabled(mycat, LOG4C_PRIORITY_TRACE))
　　 {
　　　　a_list argptr;
　　　　va_start(argptr, format);

　　　　log4c_category_vlog(mycat, LOG4C_PRIORITY_TRACE, format, argptr);

　　　　va_end(argptr);
　　 }
}
```


###总结几条，包括其优化策略

appender一般不需要自己来扩展，够用，一般就是file,stderr，stdout三个，这三个Log4c都提供了。

<font color='red'>layout有必要扩展</font>，Log4c提供的集中layout类型都不够丰富。譬如默认的Loyout类型中没有提供记录Log事件发生的位置（如文件，行，函数）的格式。所以*自己需要按照喜好定义格式*

另外，每一条*记录日志语句太长*如：
log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "Hello World!");  log4cpp或者log4cxx就相对简单。

首先是因为log4c是纯c的东西，不能以面向对象的方式来调用，在他的函数中必须指定一个category为参数（**不理解这句话**）。

*其次是log level参数太长*，如：LOG4C_PRIORITY_DEBUG，LOG4C_PRIORITY_ERROR

**通过宏的扩展**，可以让log4c更简单

###下面将做这几个工作

####1. 简化优先级定义

利用宏定义，简化函数'log4c_category_log(,,)'
```C
//原来函数的调用是这种格式，例如：log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "hello debug");修改成LOG_DEBUG(mycat, "Hello debug!")
//define里的\是宏换行符，##是宏合并符，...是可变参数宏。

#define LOG_DEBUG(category,msg,args...)\
{\
  const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\

}

```

####2. 定义loyout格式

<font color='red'>layout有必要扩展</font>，

####3. 封装成一个函数
