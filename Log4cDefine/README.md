利用宏定义，简化函数'log4c_category_log(,,)'
```C
//原来函数的调用是这种格式，例如：log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "hello debug");修改成LOG_DEBUG(mycat, "Hello debug!")
//define里的\是宏换行符，##是宏合并符，...是可变参数宏。
