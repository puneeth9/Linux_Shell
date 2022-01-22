#include "headers.h"
#include "declaration.h"
void pinfo(char *command[])
{
	int currentpid=0;
	if( command[1] == NULL)
	{
		currentpid=getpid();
	}
	else
	{
		int power=1;
		for(int i=strlen(command[1])-1;i>=0;i--)
		{
			int x=command[1][i]-'0';
			x=x*power;
			currentpid+=x;
			power=power*10;
		}
	}
		FILE * file;
		char status[100];
		char memory[100];
		char process_status[100];
		char path[50];
		sprintf(path,"/proc/%d/status",currentpid);
		file = fopen (path, "r");
		if(file==NULL)
			perror("Error");
		else
		{
			char act_mem[100];
			int temp = 0;
			while(temp != 2)
			{
				fgets(status,100,file);
				temp++;
			}
			fscanf(file,"%s %s",status,process_status);
			while(1)
			{
				fgets(memory,100,file);
				if(strstr(memory,"VmPeak") != NULL)
				{
					break;
				}
			}
			char exepath[2000];
			fscanf(file, "%s %s",memory,act_mem);
			printf("Pid -- %d\n", currentpid);
			printf("Process Status -- %s\n", process_status);
			printf("memory -- %s\n", act_mem);
			sprintf(path,"/proc/%d/exe",currentpid);
	   		readlink(path,exepath,sizeof(exepath));
	   		if(strncmp(home,exepath,strlen(home))==0)
	   		{
	   			printf("Executable path -- ~%s\n",exepath+strlen(home));
	   		}
	   		else
	   			printf("Executable path -- %s\n",exepath);
   		}
}