#include "headers.h"
#include "declaration.h"
void echo(char *command[])
{
	int i=1;
	for(i=1; command[i]!= NULL;i++)
	{
		printf("%s ",command[i]);
	}
	printf("\n");
}