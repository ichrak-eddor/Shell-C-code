#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_LINE 80 
#define MAX_HISTORY 10 
#define clear() printf("\033[H\033[J")
void execute_redirect(char *command);
int status;
int pipe_index = -1;
void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    

printf(

"\n───────▄▀▀▀▀▀▀▀▀▀▀▄▄"
"\n────▄▀▀░░░░░░░░░░░░░▀▄"
"\n──▄▀░░░░░░░░░░░░░░░░░░▀▄"
"\n──█░░░░░░░░░░░░░░░░░░░░░▀▄"
"\n─▐▌░░░░░░░░▄▄▄▄▄▄▄░░░░░░░▐▌"
"\n─█░░░░░░░░░░░▄▄▄▄░░▀▀▀▀▀░░█"
"\n▐▌░░░░░░░▀▀▀▀░░░░░▀▀▀▀▀░░░▐▌"
"\n█░░░░░░░░░▄▄▀▀▀▀▀░░░░▀▀▀▀▄░█"
"\n█░░░░░░░░░░░░░░░░▀░░░▐░░░░░▐▌"
"\n▐▌░░░░░░░░░▐▀▀██▄░░░░░░▄▄▄░▐▌"
"\n─█░░░░░░░░░░░▀▀▀░░░░░░▀▀██░░█"
"\n─▐▌░░░░▄░░░░░░░░░░░░░▌░░░░░░█"
"\n──▐▌░░▐░░░░░░░░░░░░░░▀▄░░░░░█"
"\n───█░░░▌░░░░░░░░▐▀░░░░▄▀░░░▐▌"
"\n───▐▌░░▀▄░░░░░░░░▀░▀░▀▀░░░▄▀"
"\n───▐▌░░▐▀▄░░░░░░░░░░░░░░░░█"
"\n───▐▌░░░▌░▀▄░░░░▀▀▀▀▀▀░░░█"
"\n───█░░░▀░░░░▀▄░░░░░░░░░░▄▀"
"\n──▐▌░░░░░░░░░░▀▄░░░░░░▄▀"
"\n─▄▀░░░▄▀░░░░░░░░▀▀▀▀█▀"
"\n▀░░░▄▀░░░░░░░░░░▀░░░▀▀▀▀▄▄▄▄▄");


    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t--");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
   // sleep(1);
    //clear();
}



char history[MAX_HISTORY][MAX_LINE]; 
int history_count = 0; 

void execute_command(char *command) {
     int semicolon_index = -1; 
     int and_index = -1;
    int or_index = -1; 
    int redirect_index = -1;

    char *args[MAX_LINE/2 + 1]; 

    int i = 0;
    char *token = strtok(command, " ");


     
    while (token != NULL) {
        if (strcmp(token, "|") == 0) {
            pipe_index = i;
        }
	else if (strcmp(token, ";") == 0) {
            semicolon_index = i;
        }
	else if (strcmp(token, "&&") == 0) {
            and_index = i;
        } else if (strcmp(token, "||") == 0) {
            or_index = i;
        }
	else if (strcmp(token, ">") == 0) {
          redirect_index = i;
       }
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (strcmp(args[0], "quit") == 0) {
        exit(0);
    } 


    else if (redirect_index != -1) {
        int fd;
        char *output_file = args[redirect_index+1];
        args[redirect_index] = NULL;

        if ((fd = open(output_file, O_CREAT|O_WRONLY|O_TRUNC, 0644)) < 0) {
            perror("open");
            //exit(1);
        }

        if (dup2(fd, 1) < 0) {
            perror("dup2");
            //exit(1);
        }

        close(fd);

        if (execvp(args[0], args) < 0) {
            perror("execvp");
           // exit(1);
        }
    } 


    else if (strcmp(command, "help") == 0) {
            printf("This is a simple shell program. Available commands are:\n");
            printf("- help: display this message\n");
            printf("- quit: exit the program\n");
            printf("- cd:  navigate through the Linux files and directories\n");
            printf("- mkdir:  create one or multiple directories at once \n");
            printf("- pwd: find the path of your current working directory \n");
	    printf("- cat: type cat followed by the file name and its extension\n");
            printf("- wc\n");
            printf("- history: the system will list up to 500 previously executed commands\n");
	    printf("-ls lists files and directories within a system \n");
        }
        
    
    else if (strcmp(args[0], "cd") == 0) {
              if (args[1] == NULL) {
            fprintf(stderr, "cd: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
    } 

    else if (strcmp(args[0], "wc") == 0) {
    if (access(args[1], F_OK) != -1) {
    	    char cmd[MAX_LINE] = "wc ";
        strcat(cmd, args[1]);
        FILE *fp = popen(cmd, "r");
        if (fp == NULL) {
            perror("wc");
        } else {
            char output[MAX_LINE];
            while (fgets(output, MAX_LINE, fp) != NULL) {
                printf("%s", output);
            }
            pclose(fp);
        }
    } else {
        printf("Error: specified file not found\n");
    }
}




     else if (strcmp(command, "mkdir") == 0) {
        printf("Enter the directory name: ");
        fgets(args[1], 128, stdin);
        args[1][strlen(args[1]) - 1] = '\0';
        args[0] = "mkdir";
        args[2] = NULL;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            exit(1);
        } else {
            waitpid(pid, &status, 0);
        }
    }
    else if (strcmp(args[0], "history") == 0) {
        int i;
        for (i = 0; i < history_count; i++) {
            printf("%d %s\n", i + 1, history[i]);
        }
    } 
    else if (args[0][0] == '!') {
        int command_index = atoi(&args[0][1]);
        if (command_index > 0 && command_index <= history_count) {
            strcpy(command, history[command_index - 1]);
            execute_command(command);
        } else {
            printf("Invalid commandi index\n");
        }
    }

    
    

    else if (strstr(command, "|") != NULL) {
        char *token = strtok(command, "|");
        args[0] = token;
        int i = 1;
        while (token != NULL) {
            token = strtok(NULL, "|");
            args[i] = token;
            i++;
        }
        args[i - 1] = NULL;
        int fd[2];
        pipe(fd);
        pid_t pid1 = fork();
        if (pid1 == 0) {
            dup2(fd[1], 1);
            execvp(args[0], args);
            close(fd[1]);
	    exit(1);
           
        } else {
            waitpid(pid1, &status, 0);
            close(fd[1]);
            dup2(fd[0], 0);
            execvp(args[2], &args[2]);
            close(fd[0]);
	    exit(1);
            
        }

    } 
    

    
    else if (pipe_index != -1) {
        
        int fd[2];
        if (pipe(fd) != 0) {
            perror("pipe");
            return;
        }

       
        args[pipe_index] = NULL;

        
        pid_t child1_pid = fork();
        if (child1_pid == 0) {
          
            close(fd[0]);
          
            dup2(fd[1], STDOUT_FILENO);
          
            close(fd[1]);
        
            execvp(args[0], args);
      
            perror("execvp");

	    exit(1);
           
        }
        pid_t child2_pid = fork();
        if (child2_pid == 0) {
          
            close(fd[1]);
           
            dup2(fd[0], STDIN_FILENO);
         
            close(fd[0]);
          
            char *new_args[] = {"wc", "-l", NULL};
            execvp("wc", new_args);
       
            perror("execvp");
	  //  fflush(stdout);
	    exit(0);
            
        }
	close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
//	int status;
   //     waitpid(child1_pid, &status, 0);
     //   waitpid(child2_pid, &status, 0);

}




 


/*
    else if (strcmp(command, "cat") == 0) {
        char file_name[100];
        scanf("%s", file_name);

        FILE *file = fopen(file_name, "r");
        if (file == NULL) {
            printf("Error: Could not open file.\n");
        } else {
            char c = fgetc(file);
            while (c != EOF) {
                printf("%c", c);
                c = fgetc(file);
            }
            fclose(file);
        }

    }
    */

    else if (strcmp(command, "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            printf("Error: Failed to get current working directory.\n");
        }
    }

  
    else{ 
        int child_status;
        pid_t child_pid = fork();
        if (child_pid == 0) {
            execvp(args[0], args);
        } else {
            waitpid(child_pid, &child_status, 0);
	}  
    }

      
}








void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
      printf("\n%s  ",cwd);
}





int main(void) {
    char command[MAX_LINE];
    init_shell();
    while (1) {
        printDir();
        printf("%% ");
        fflush(stdout);
        int bytes_read = read(STDIN_FILENO, command, MAX_LINE);
        command[bytes_read - 1] = '\0';

        strcpy(history[history_count % MAX_HISTORY], command);
        history_count++;

        execute_command(command);
    }



   

    return 0;
}




