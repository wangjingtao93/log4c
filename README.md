
可以直接打开文件夹‘log4c封装函数’，里面有封装好的函数可以使用，调用方式为：LOG_DEBUG("%d,%s",i,"hello Debug")，打印Debug日志，同样可以打印notice，Error,trace，warn这几种（目前函数只封装了这几种类型，也可以用宏定义将所有的类型按照相同的方式封装）。