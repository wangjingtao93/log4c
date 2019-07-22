1. 将log4c调用封装成一个函数，并使用宏定义简化其调用方式，[参照笔记](https://www.linuxidc.com/Linux/2011-02/32560.htm)。

2. 目前例子log4ctest可以直接这样调用LOG_DEBUG("%d,%s",i,"hello Debug")打印Debug日志，同样可以打印notice，Error,trace，warn这几种（目前函数只封装了这几种类型，也可以用宏定义将所有的类型按照相同的方式封装）。

3. 打印的日志的内容如下：*时间+priority+category name+filenanme[行号][函数名] + message*，例如：20190424 06:17:41.611 DEBUG    log4ctest- [    main.c][  18][      main()]: Hello Debug!-0。[文件mylogfile.0](mylogfile.0)是执行示例生成的一个日志

4. 注意最新的日志是  .0结尾的。

5. 直接make可以直接生成执行文集log4ctest,或者使用命令gcc main.c mylog.c other.c -o log4ctest -L/usr/local/lib -llog4c也可以。

6. <font color="red">注意：</font>可能遇到的问题：
 * “log4c_priority_level_t未定义”，解决它需要在priority头文件的“typedef enum{};”加上log4c_priority_level_t：“typedef enum{}log4c_priority_level_t;”
