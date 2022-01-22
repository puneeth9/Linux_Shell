#include "headers.h"
#include "declaration.h"
int check(char *str)
{
	int i;
	for(i=0;i<strlen(str);i++)
	{
		if(str[i]!=' ')
			break;
	}
	if(i==strlen(str))
		return 1;
	return 0;
}
int check1(char *str)
{
	int i,ret;
	for(i=0;i<strlen(str)-1;i++)
	{
		if(str[0]==';')
			break;
		if(str[i]==';' && str[i+1]==';')
			break;
	}
	if(i==strlen(str)-1)
		ret=1;
	else
		ret=0;
	return ret;
}
int builtin(char *str[])
{
	if(strcmp(str[0],"echo")==0)
		return 1;
	if(strcmp(str[0],"pwd")==0)
		return 1;
	if(strcmp(str[0],"cd")==0)
		return 1;
	if(strcmp(str[0],"ls")==0)
		return 1;
	if(strcmp(str[0],"pinfo")==0)
		return 1;
	if(strcmp(str[0],"jobs")==0)
		return 1;
	if(strcmp(str[0],"kjob")==0)
		return 1;
	if(strcmp(str[0],"overkill")==0)
		return 1;
	if(strcmp(str[0],"setenv")==0)
		return 1;
	if(strcmp(str[0],"unsetenv")==0)
		return 1;
	if(strcmp(str[0],"quit")==0)
		return 1;
	if(strcmp(str[0],"fg")==0)
		return 1;
	if(strcmp(str[0],"bg")==0)
		return 1;
	return 0;
}
int checkIO(char *str)
{
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='>' || str[i]=='<')
			return 1;
	}
	return 0;
}
int checkpipe(char* str)
{
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='|')
			return 1;
	}
	return 0;
}
void history()
{
	FILE * fPtr;
    char ch;
    fPtr = fopen("history.txt", "r");
    do
    {
        ch = fgetc(fPtr);
        printf("%c",ch);

    } while(ch != EOF);  
    fclose(fPtr);
}
int input()
{
	char c;
	char input[500];
	int z=0,flag=0;
	bzero( input,sizeof( input));
	FILE* into;
	char new='\n';
	into=fopen("history.txt","a");
	while( ( c = getchar()))
	{
		if(c == EOF)
		{
			printf("\n");
			return 0;
		}
		if(c=='\n')
		{
			break;
		}
		strncat( input, &c, 1);
		//fputc(c,into);
		z++;
	}
	//fputc(new,into);
	//fclose(into);
	if(z>0)
	{
		if(check1(input)==0)
		{
			perror("Error");
			flag=1;
		}
	}
	char *temp[1000];
	char *string[1000];int j;
	if(z>0)
	{
		if(flag==0)
		{
			char *tolon;
			int tolcount=0;
			tolon=strtok(input,";");
			while(tolon!=NULL)
			{
				temp[tolcount]=tolon;
				tolon=strtok(NULL,";");
				tolcount++;
			}
			for(int comcount=0;comcount<tolcount;comcount++)
			{
				//temp[comcount]=addspace(temp[comcount]);
				//printf("%s\n",temp[comcount]);
				if(strcmp(temp[comcount],"quit")==0)
					return 0;
				if(checkpipe(temp[comcount])==1)
				{
						piping(temp[comcount]);
				}
				else if(checkIO(temp[comcount])==1)
				{
					int pid=fork();
					if(pid==0)
						Onlyredirection(temp[comcount]);
					if(pid>0)
						wait(NULL);
				}
				else
				{
					if(check(temp[comcount])==1 && comcount!=tolcount-1)
					{
						perror("Error");
						break;
					}
					if(check(temp[comcount])==1 && comcount==tolcount-1)
						continue;
					j=0;
					char *token;
					char* foretemp=malloc(10000);
					foretemp=temp[comcount]; 
					token = strtok(temp[comcount], " "); 
					while( token != NULL ) 
					{
						string[j] = token;
						token = strtok(NULL, " ");
						j++;
					}
					string[j] = NULL;
					int background=0;
					if(strcmp(string[j-1],"&")==0)
					{
						background=1;
						string[j-1]=NULL;
						if(builtin(string)==1)
						{
							background=0;
							j--;
						}
					}
					//printf("the background value of the current is %d\n",background);
					//printf("%s %s\n",string[0],string[1]);
					if(!background)
				   	{
				   		if(builtin(string)==0)
				   		{
				   			int id=fork();
					    	if(id!=0)
					    	{
					    		fname=malloc(10000);
					    		fname=foretemp;
					    		fpid=id;
						       	waitpid(-1,NULL,WUNTRACED);
						       	fpid=0;
					    	}
						    else
						    {
					 			execute(j,string);
						    }

						}
						else
							execute(j,string);	
				    }
				   	else
				    {
						int pid=fork();
				        if(pid==0)
				        {
				           	setpgid(0,0);
				           	execute(j-1,string);
				        }
				        else
				        {
					       	printf("started %s,with pid %d\n",string[0],pid);
					       	addjob(pid,temp[comcount]);
					       	//printf("%s\n",backgroundname[backgroundcount-1]);	
					   	}
					}
				}
			}
		}	
	}
}
void execute(int null,char *command[])
{
		if(null)
		{
			char absolute[1000];
			if(strcmp(command[0],"echo")==0)
				echo(command);
			else if(strcmp(command[0],"pwd")==0)
				pwd();
			else if(strcmp(command[0],"cd")==0)
				set=cd(command);
			else if(strcmp(command[0],"ls")==0)
				ls(null,command);
			else if(strcmp(command[0],"pinfo")==0)
				pinfo(command);
			else if(strcmp(command[0],"history")==0)
				history();
			else if(strcmp(command[0],"jobs")==0)
				displayjobs();
			else if(strcmp(command[0],"kjob")==0)
				killjob(command[1],command[2]);
			else if(strcmp(command[0],"setenv")==0)
				setenviron(command[1],command[2],null);
			else if(strcmp(command[0],"unsetenv")==0)
				unset(command[1],null);
			else if(strcmp(command[0],"overkill")==0)
				overkill();
			else if(strcmp(command[0],"fg")==0)
				fg(command[1]);
			else if(strcmp(command[0],"bg")==0)
				bg(command[1]);
			else
			{
				int error=execvp(command[0],command);
				if(error==-1)
					perror("Error");
				exit(0);
			}
			//exit(0);
		}
}