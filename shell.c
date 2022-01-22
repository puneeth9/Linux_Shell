#include "headers.h"
#include "declaration.h"
//int set=0;
void handler()
{
	int ret,nouse;
	while(1)
	{
		ret=waitpid((pid_t)-1,&nouse,WNOHANG);
		if(ret>0)
		{
			int i=0;
			struct job* curr=head;
			while(curr!=NULL)
			{
				if(ret==curr->pid)
				{
					//job[i]=0;
					//deletejob(ret);
					backgroundcount--;
					break;
				}
				curr=curr->next;
			}
			fprintf(stderr,"\n%s with pid %d exited \n",firstpart(curr->name),curr->pid);
			deletejob(ret);
		}
		else
			break;
	}
}
void controlc()
{
	if(fpid!=0)
	{
		if(kill(fpid,SIGINT)<0)
			perror("Kill error");
		fpid=0;
	}
	signal(SIGINT,controlc);
}
void controlz()
{
	if(fpid!=0)
	{
		if(kill(fpid,SIGTTIN)<0)
		{
			perror("Error in converting to background");
			return;
		}
		if(kill(fpid,SIGTSTP)<0)
		{
			perror("Error in changing the process from running to stopped");
			return;
		}
		addjob(fpid,fname);
	}
}
int main()
{
	set=0,cdcount=0,runningfg=0;
	backgroundcount=0;
	getcwd(home,1024);
	/*setsid();
	char* terminal=malloc(1000);
	ctermid(terminal);
	//printf("%s\n",terminal);
	int fd=open(terminal,O_RDWR);
	tcsetpgrp(fd,getpid());*/

	while(1)
	{
		signal(SIGCHLD,handler);
		signal(SIGINT,controlc);
		signal(SIGTSTP,controlz);
		//signal(SIGINT,controlc);
		//printf("%d\n",getpid());
		prompt(set);
		int inp=input();
		if(inp==0)
			break;
	}
}