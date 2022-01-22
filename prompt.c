#include "headers.h"
#include "declaration.h"

void prompt(int set)
{
	//int set=0;
	user=getlogin();
	gethostname(host,1023);
	host[1023]='\0';
	//printf("%d",strlen(home));
	if(set==0)
		printf("%s@%s:~%s$", user,host,current+strlen(home));
	if(set==1)
		printf("%s@%s:%s$", user,host,current);
}