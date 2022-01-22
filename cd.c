#include "headers.h"
#include "declaration.h"
int cd(char *command[])
{
	int prompt;
	if(command[1]==NULL)
		command[1]="~";
	if(strcmp(command[1],"-")==0)
	{
		past[cdcount+1]=malloc(1000);
		getcwd(past[(cdcount)+1],1023);
		int status=chdir(past[cdcount]),i;
		if(status!=0)
		{
			getcwd(current,1023);
			perror("OLDPWD NOT SET");
		}
		else
		{
			printf("%s\n",past[cdcount]);
			getcwd(current,1023);
			current[1023]='\0';
			if(strlen(current)>=strlen(home))
			{
		 		for(i=0;i<strlen(home);i++)
			 	{
			 		if(current[i]==home[i])
			 			continue;
			 		else
			 			break;
			 	}
			 	if(i==strlen(home))
			 	{
			 		prompt=0;
			 	}
			 	else
			 		prompt=1;
		 	}
			if(strlen(current)<strlen(home))
			{
				prompt=1;
			}
			cdcount ++;
			return prompt;
		}
	}
	if(strcmp(command[1],"~")==0)
	{
		for(int z=0;z<strlen(home);z++)
			current[z]=home[z];
		current[strlen(home)]='\0';
		getcwd(past[cdcount],1023);
		chdir(home);
		prompt=0;
	}
	else
	{
		char temp[1023];
		getcwd(temp,1023);
		int status=chdir(command[1]),i;
		if(status != 0)
		{
			getcwd(current,1023);
			perror("Error");
		}
		else
		{
			past[cdcount]=malloc(1000);
			for(int j=0;j<strlen(temp);j++)
				past[cdcount][j]=temp[j];
			past[cdcount][strlen(temp)]='\0';
			getcwd(current,1023);
			current[1023]='\0';
			if(strlen(current)>=strlen(home))
			{
			 	for(i=0;i<strlen(home);i++)
			 	{
			 		if(current[i]==home[i])
			 			continue;
			 		else
			 			break;
			 	}
			 	if(i==strlen(home))
			 	{
			 		prompt=0;
			 	}
			 	else
			 		prompt=1;
			}
			if(strlen(current)<strlen(home))
			{
			 	prompt=1;
			}

		}
	}
	return prompt;
}