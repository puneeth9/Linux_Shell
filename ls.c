#include "headers.h"
#include "declaration.h" 
			void display(int l,int a,struct dirent ** namelist,int list,char present[])
			{
				struct passwd *user;
				struct group *grp;
				int total=0;
				for(int itr=0;itr<list;itr++)
				{
					struct stat mystat;
		        	char temp[1024];
					bzero(temp,sizeof(temp));
					strcat(temp,present);
					strcat(temp,"/");
					strcat(temp,namelist[itr]->d_name);
					stat(temp,&mystat);
					if(a==0)
					{
						if(namelist[itr]->d_name[0]=='.')
						continue;	
					}
					total=total+(mystat.st_blocks);
				}
				if(l==1)
					printf("total %d\n",total/2);
				for(int loop=0;loop<list;loop++)
		        {
		        	struct stat mystat;
		        	char temp[1024];
					bzero(temp,sizeof(temp));
					strcat(temp,present);
					strcat(temp,"/");
					strcat(temp,namelist[loop]->d_name);
					stat(temp,&mystat);
		        	if(a==0)
					{
						if(namelist[loop]->d_name[0]=='.')
						continue;	
					}
		            const char s[2] = " ";
					char *token;
					char *time[10];
					token = strtok(ctime(&mystat.st_mtime), s);
					int z=0; 
					while( token != NULL ) 
					{
						time[z] = token;
						token = strtok(0, s);
						z++;
					}
					
					time[z]=NULL;
					time[3][5]='\0';
		        	user=getpwuid(mystat.st_uid);
		        	grp=getgrgid(mystat.st_gid);
		        	char *username=user->pw_name;
		        	char *groupname=grp->gr_name;
		        	char permission[10];
		        	if(S_ISDIR(mystat.st_mode))
		        		permission[0]='d';
		        	else if(S_ISLNK(mystat.st_mode))
		        		permission[0]='l';
		        	else
		        		permission[0]='-';
		    		permission[1]=(mystat.st_mode & S_IRUSR) ? 'r' : '-';
		    		permission[2]=(mystat.st_mode & S_IWUSR) ? 'w' : '-';
		    		permission[3]=(mystat.st_mode & S_IXUSR) ? 'x' : '-';
		    		permission[4]=(mystat.st_mode & S_IRGRP) ? 'r' : '-';
		    		permission[5]=(mystat.st_mode & S_IWGRP) ? 'w' : '-';
		    		permission[6]=(mystat.st_mode & S_IXGRP) ? 'x' : '-';
		    		permission[7]=(mystat.st_mode & S_IROTH) ? 'r' : '-';
		    		permission[8]=(mystat.st_mode & S_IWOTH) ? 'w' : '-';
		    		permission[9]=(mystat.st_mode & S_IXOTH) ? 'x' : '-';
		    		if(l==1)
		    		{
		    		for(int k=0;k<=9;k++)
		    			printf("%c",permission[k]);
		    		long long int link=mystat.st_nlink;
		  	 		printf("%3lld",link);
		    		printf("%9s",username);
		    		printf("%9s",groupname);
		    		printf("%10ld",mystat.st_size);
		    		printf("%6s",time[1]);
		    		printf("%4s",time[2]);
		    		printf("%7s",time[3]);
		    		printf("  %s",namelist[loop]->d_name);
		    		printf("\n");
		    		}
		    		if(l==0)
		    			printf("%s\n",namelist[loop]->d_name);
		        }
		        //if(l==0)
		        	//printf("\n");
			}
void ls(int num,char *command[])
{
	int l=0,a=0,i=1,dircount=0;
	while(i<num)
	{
		if(strcmp(command[i],"-l")==0)
			l=1;
		else if(strcmp(command[i],"-a")==0)
			a=1;
		else if(strcmp(command[i],"-la")==0 || strcmp(command[i],"-al")==0)
			l=a=1;
		else
			dircount++;
		i++;
		if(strcmp(command[i-1],"~")==0)
			command[i-1]=home;
	}
	int count,nodir=0;
	if(dircount==0)
	{
		command[i]=".";
		num++;
		nodir=1;
	}
	for(count=1;count<num;count++)
	{
		struct dirent **namelist;
		if(strcmp(command[count],"-l")==0 || strcmp(command[count],"-a")==0 || strcmp(command[count],"-la")==0 || strcmp(command[count],"-al")==0)
		{
		
		}
		else
		{
			if(nodir==0)
				printf("%s :\n",command[count]);
			if(command[count][0]=='/')
			{
				int list=scandir(command[count],&namelist,NULL,alphasort);
				if(list==-1)
					perror("Error");
				else
					display(l,a,namelist,list,command[count]);
			}
			else
			{
			    char present[1024];
				getcwd(present,1024);
			    strcat(present,"/");
			    strcat(present,command[count]);
			    if(nodir==0)
			    	strcat(present,"/.");
				int list=scandir(present,&namelist,NULL,alphasort);
				if(list==-1)
					perror("Error");
			    display(l,a,namelist,list,present);
			}
		}
	}
}