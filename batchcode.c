#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>

void parse(char* p,char** q,int);
void exec_cmd(char** q);


char *cmd[100];
pid_t parent_pid,pid;
int status,r,child_Count=0;


void  exec_cmd(char** q){
    pid = fork();
    if(pid == 0) {

        if(execvp(*q,q) < 0) {
        	printf("exec return:%d\n",r);
            printf("Warning: Invalid command. exec failed.\n");
            exit(1);
        }
    }
}


void parse(char* p, char** q,int exit_Sh){
	int semi=0,semi_good=0,exit_shell=exit_Sh;
	char **t;
	t=q;

	while(*p != '\0'){
		q=t;
		while(semi == 0 && *p != '\0'){
			while(*p == ' ' || *p == '\n' || *p == '\t' || *p == ';'){
				if(*p == ';' && semi_good == 1){
					semi = 1;
					*p = '\0';
			           	p++;
					break;
				}

				*p = '\0';
				p++;
			}
			if(semi == 1 || *p == '\0'){
				break;
			}
			*q = p;
			semi_good = 1;
			q++;

			while(*p!='\0' && *p!='\t' && *p!=' ' && *p!='\n'){
				if(*p == ';'){
					semi = 1;
					*p = '\0';
					p++;
					break;
				}
				p++;
			}

		}
		if(semi_good == 1){
			*q = '\0';
			if(strcmp(cmd[0], "quit") == 0)
				exit_shell = 1;

            if(strcmp(cmd[0], "quit") != 0){
            	child_Count+=1;
			    exec_cmd(cmd);

            }
			semi = 0;
			semi_good = 0;
			if(exit_shell == 1 && *p == '\0'){
	            exit(0);
			}
		}
		else
			printf("Improper command format. Please corect.\n");
	}
}

int main( int argc, char *argv[] )  {
	parent_pid = getpid();
	FILE *f;
	char usr_cmd[250];
	int batch_mode=0;
	int ip_Return,exit_Sh=0;
	char prompt_show[11];


	if(argc>=2){
		printf("\nBatch file being executed:%s\n",argv[1]);
		batch_mode=1;

		f = fopen(argv[1],"r");
		if (f == NULL){
			 printf("Unsuccessful file open............................ \n");
			 exit(0);
		}

		while(fgets(usr_cmd,250,f) != NULL)
		{
			usr_cmd[strlen(usr_cmd)-1]='\0';
			printf("\nbatch cmd line being executed:%s\n\n",usr_cmd);
			parse(usr_cmd, cmd, 0);
		}

	}


	while(batch_mode == 0 && parent_pid==getpid()) {
		sprintf(prompt_show, "Prompt -> ");
		write(1, prompt_show, strlen(prompt_show));
		memset(&usr_cmd[0], 0, sizeof(usr_cmd));
		ip_Return = scanf("%[^\n]%*c", usr_cmd);
		if(ip_Return < 0)
			exit(1);
		int len=strlen(usr_cmd);
		if(len == 0 && usr_cmd[0] == '\0') {
			while((getchar())!='\n');
		}
		parse(usr_cmd, cmd,exit_Sh);
		for(int x=1;x<=child_Count;x++)
		wait(0);
	}
	fclose(f);
	return 0;
}
