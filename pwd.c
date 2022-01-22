#include "headers.h"
#include "declaration.h"
void pwd()
{
	char *currentdir = NULL;
	currentdir = getcwd(currentdir, 300);
	printf("%s\n", currentdir);
}