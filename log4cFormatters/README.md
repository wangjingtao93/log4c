#自定义layout的格式，
即日志的输出格式。

##工作成果
1. application.c可以实现：增加了时间，并将category name放在了message的前面。默认的输出格式是：priorit + category name + message[消息+行号+filename],通过自定义现在的输出的格式是：时间+category name + a_event->evt_loc->loc_line + a_event->evt_loc->loc_file + a_event->evt_msg[消息 + 行号 + file nanme],但目前只能做到在屏幕上打印，在研究如何写入文件

2.
