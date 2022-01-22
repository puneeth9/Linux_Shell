#include "declaration.h"
#include "headers.h"
void Onlyredirection(char* string)
{
	int input=0,output=0,k=0,instream=0,outstream=0;
	char* token;
	char* stream[50];
	token=strtok(string," ");
	while(token!=NULL)
	{
		stream[k]=token;
		token=strtok(NULL," ");
		k++;
	}
	stream[k]=NULL;
	for(int j=0;j<k;j++)
	{
		if(strcmp(stream[j],"<")==0)
		{
			input=1;
			instream=j+1;
		}
		if(strcmp(stream[j],">")==0)
		{
			output=1;
			outstream=j+1;
		}
		if(strcmp(stream[j],">>")==0)
		{
			output=2;
			outstream=j+1;
		}
	}
	if(instream>0 && outstream==0)
	{
		int fd=open(stream[instream],O_RDONLY);
		if(fd==-1)
		{
			perror("FileError");
		}
		else
		{
			dup2(fd,STDIN_FILENO);
		}
		stream[instream-1]=NULL;
		execute(instream-1,stream);
		exit(0);
	}
	if(outstream>0 && instream==0)
	{
		int fd;
		if(fd==-1)
		{
			perror("FileError");
		}
		if(output==1)
			fd=open(stream[outstream],O_CREAT | O_TRUNC | O_WRONLY,0644);
		if(output==2)
			fd=open(stream[outstream],O_CREAT | O_APPEND | O_WRONLY,0644);
		dup2(fd,STDOUT_FILENO);
		stream[outstream-1]=NULL;
		execute(outstream-1,stream);
		exit(0);
	}
	if(outstream>0 && instream>0)
	{
		int fdin,fdout;
		if(output==1)
			fdout=open(stream[outstream],O_CREAT | O_TRUNC | O_WRONLY,0644);
		if(output==2)
			fdout=open(stream[outstream],O_CREAT | O_APPEND | O_WRONLY,0644);
		dup2(fdout,STDOUT_FILENO);
		fdin=open(stream[instream],O_RDONLY);
		if(fdin==-1)
		{
			perror("FileError");
		}
		else
		{
			dup2(fdin,STDIN_FILENO);
		}
		if(fdout==-1)
		{
			perror("FileError");
		}
		stream[instream-1]=NULL;
		execute(instream-1,stream);
		exit(0);
	}
}