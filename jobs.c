#include "declaration.h"
#include "headers.h"
struct job* newjob(int pid,char* cmd)
{
	totalnodes++;
	struct job* temp = (struct job*)malloc(sizeof(struct job));
	temp->next = NULL;
	temp->name=malloc(10000);
	strcpy(temp->name, cmd);
    temp->pid = pid;
    temp->state=1;
    return temp;
}
char* firstpart(char* cmd)
{
	char* temp=strtok(cmd," ");
	return temp;
}
struct job* kthnode(int jobnumber)
{
	struct job* curr=head;
	int count=0;
	for(int i=0;i<totalnodes;i++)
	{
		if(curr->state==1)
			count++;
		if(count==jobnumber)
			break;
		curr=curr->next;
	}
	return curr;
}
void addjob(int pid,char* cmd)
{
	struct job* add=newjob(pid,cmd);
	struct job* curr=head;
	if(curr==NULL)
		head=add;
	else
	{
		while(curr->next!=NULL)
		{
			if(curr->pid==pid)
				return;
			curr=curr->next;
		}
		curr->next=add;
		curr->next->state=1;
	}
}
void deletejob(int pid)
{
	struct job* curr=head;
	while(curr!=NULL)
	{
		if(curr->pid==pid)
			curr->state=0;
		curr=curr->next;
	}
}
void displayjobs()
{
	int count=1;
	struct job* curr=head;
	while(curr!=NULL)
	{
		if(curr->state==1)
		{
			char path[500];
			sprintf(path,"/proc/%d/status",curr->pid);
			FILE * file ;
			file = fopen (path, "r");
			if(file==NULL)
				perror("File error");
			char status[1000];
			char process_status[100];
			int temp = 0;
			while(temp != 2)
			{
				fgets(status,100,file);
				temp++;
			}
			fscanf(file,"%s %s",status,process_status);
			if(strcmp(process_status,"R")==0 || strcmp(process_status,"S")==0)
				strcpy(status,"Running");
			if(strcmp(process_status,"T")==0)
				strcpy(status,"Stopped");
			char* name=malloc(10000);
			name=firstpart(curr->name);
			printf("[%d] %s %s [%d]\n",count,status,name,curr->pid);
			count++;
		}
		curr=curr->next;
	}
}
void killjob(char *jobstring,char* signalstring)
{
	int jobnumber=0,signalnumber=0;
	int power=1;
	for(int i=strlen(jobstring)-1;i>=0;i--)
	{
		int x=jobstring[i]-'0';
		x=x*power;
		jobnumber+=x;
		power=power*10;
	}
	power=1;
	for(int i=strlen(signalstring)-1;i>=0;i--)
	{
		int x=signalstring[i]-'0';
		x=x*power;
		signalnumber+=x;
		power=power*10;
	}
	kill(kthnode(jobnumber)->pid,signalnumber);
		//perror("kill error");
}
void overkill()
{
	struct job* curr=head;
	while(curr!=NULL)
	{
		if(curr->state==1)
		{
			signal(SIGCHLD,SIG_IGN);
			if(kill(curr->pid,SIGKILL)<0)
				perror("kill error");
			deletejob(curr->pid);
		}
		curr=curr->next;
	}
}
void setenviron(char* variable,char* value,int num)
{
	if(num==3)
	{
		if(setenv(variable,value,1)<0)
			perror("setenv error");
	}
	if(num==2)
	{
		if(setenv(variable,"",1)<0)
			perror("setenv error");
	}
	if(num==1)
		perror("Too few arguements");
	if(num>3)
		perror("Too many arguements");
}
void unset(char* variable,int num)
{
	if(num==1)
		perror("Too few arguements");
	if(num > 2)
		perror("Too many arguements");
	if(unsetenv(variable)<0)
		perror("unsetenv error");
}
void fg(char* jobstring)
{
	int jobnumber=0;
	int power=1;
	for(int i=strlen(jobstring)-1;i>=0;i--)
	{
		int x=jobstring[i]-'0';
		x=x*power;
		jobnumber+=x;
		power=power*10;
	}
	struct job* fgjob=kthnode(jobnumber);
	if(fgjob==NULL)
	{
		perror("fg error");
		return;
	}
	signal(SIGCHLD, SIG_IGN);
	int killtemp;
    killtemp=kill((fgjob->pid), SIGCONT);
    if(killtemp<0)
    	perror("error kill");
    fpid = fgjob->pid;
    fname = fgjob->name; 
    deletejob(fgjob->pid);
    int status;
    waitpid(fpid, &status,WUNTRACED);
    fpid = 0;
    signal(SIGCHLD,handler);
    if(WIFSTOPPED(status))
        addjob(fgjob->pid,fgjob->name);
}
void bg(char* jobstring)
{
	int jobnumber=0;
	int power=1;
	for(int i=strlen(jobstring)-1;i>=0;i--)
	{
		int x=jobstring[i]-'0';
		x=x*power;
		jobnumber+=x;
		power=power*10;
	}
	struct job* bgjob=kthnode(jobnumber);
	if(bgjob==NULL)
	{
		perror("bg error");
		return;
	}
	if(kill(bgjob->pid,SIGCONT)<0)
	{
		perror("bg kill error");
		return;
	}
}