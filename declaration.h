#include "headers.h"
void prompt(int set);
int input();
void pwd();
void echo(char *command[]);
int cd(char *command[]);
void ls(int num,char *command[]);
void pinfo(char *command[]);
void execute(int null,char *command[]);
void history();
void displayjobs();
char* addspace(char* string);
void Onlyredirection(char* string);
void piping(char* string);
void controlc();
void killjob(char* jobstring,char* signalstring);
void overkill();
void setenviron(char* variable,char* value,int num);
void unset(char* variable,int num);
int checkIO(char* str);
void handler();
//global variables
char *user;
char host[1024];
char *command[1000];
char home[1024];
int set;
int backgroundcount;
int backgroundpid[10000];
int job[10000];
char *backgroundname[10000];
char current[1024];
char* past[1024];
int cdcount;
int runningfg;
struct job
{
	int pid;
	char* name;
	struct job* next;
	int state;
};
struct job* head;
void fg(char* jobstring);
void bg(char* jobstring);
void addjob(int pid,char* command);
void deletejob(int pid);
struct job* kthjob(int jobnumber);
struct job* newjob(int pid,char* cmd);
char* firstpart(char* cmd);
int fpid;
char* fname;
int totalnodes;