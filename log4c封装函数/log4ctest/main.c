#include <stdio.h>
#include "mylog.h"
#include "other.h"

int main(int argv, char **argc) {
  int i;
	if ( mylog_init() == 1 )
	{
		printf("mylog_init() failed!\n");
	}
	
	printf("*****start Write logs**************");

    for(i=0;i<20;i++)
    {

    	LOG_WARN("%s%d","Hello Warn!-",i);
    	LOG_DEBUG("%s%d","Hello Debug!-",i);
      LOG_ERROR("%s%d","Hello Error!-",i);
      LOG_NOTICE("%s%d","Hello Notice!-",i);
      LOG_TRACE("%s%d","Hello Trace!-",i);

    	otherFunc();
    }
    if(mylog_fini() == 1)
    {
    	printf("mylog_fini() failed!\n");
    }
    
         return 0;
}
