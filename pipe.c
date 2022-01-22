#include "headers.h"
#include "declaration.h"
void piping(char* string)
{
	char* stream[500];
	int j=0,i;
	char* token;
	token=strtok(string,"|");
	while(token!=NULL)
	{
		stream[j]=token;
		//fprintf(stderr,"stream : %s\n",stream[j]);
		token=strtok(NULL,"|");
		j++;
	}
	stream[j]=NULL;
	int in = 0, out = 1;
	for(i=0;i<j;i++)
	{
		//printf("%s\n",stream[i]);
		//printf("%d\n",j);
		int fd[2];
        pipe(fd);
        pid_t pid = fork();
        if (pid < 0)
            perror("Fork error");
        else if (pid != 0) //error handling
        {
        	wait(NULL);
            close(fd[1]);
            out = fd[1];
            in = fd[0];
        }
        else
        {
        	if (i != j- 1)
                dup2(fd[1], 1);
            dup2(in, 0);
            int check = checkIO(stream[i]);
            close(fd[0]);
            if (check != 0)
            {
                Onlyredirection(stream[i]);
                exit(1); 
            } 
            else 
            {
            	char *temp[40];
				char* tolon=strtok(stream[i]," ");
				int var=0;
				while(tolon!=NULL)
				{
					temp[var]=tolon;
					tolon=strtok(NULL," ");
					var++;
				}
				temp[var]=NULL;
            	execute(var,temp);
            }
            exit(1);
        }
	}	
}