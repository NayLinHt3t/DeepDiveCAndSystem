#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(){
    char buffer[1024];
    while(1){
        char cwd[1024];
        getcwd(cwd,sizeof(cwd));
        printf("%s $",cwd);
        if(fgets(buffer,sizeof(buffer),stdin) == NULL){
            break;
        } 
        char *args[100];
        args[0] = strtok(buffer," \n");
        if(args[0] == NULL){
            continue;
        }
        int i=1;
        while((args[i] = strtok(NULL," \n")) != NULL){
            i++;
        }
        if(strcmp(args[0],"exit") == 0){
            break;
        }
        if(strcmp(args[0],"cd") == 0){
            if(args[1] == NULL){
                fprintf(stderr,"cd: missing argument\n");
            }else if(chdir(args[1]) != 0 ){
                perror("cd failed");
            }
            continue;
        }
        int pipe_index = -1;
        for(int j=0;args[j] != NULL;j++){
            if(strcmp(args[j],"|") == 0){
                pipe_index = j;
                args[j] = NULL;
                break;
            }
        }
        if(pipe_index != -1){
            char **left_arg = args;
            char **right_arg = &args[pipe_index+1];
            int fd[2];
            if(pipe(fd) == -1){
                perror("pipe failed");
                continue;
            }
            pid_t pid1 = fork();
            if(pid1 == 0){
                dup2(fd[1],STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                execvp(left_arg[0],left_arg);
                exit(1);
            }
            pid_t pid2 = fork();
            if(pid2 == 0){
                dup2(fd[0],STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
                execvp(right_arg[0],right_arg);
                exit(1);
            }
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
            continue;
        }
        char *output_file = NULL;
        for(int j=0;args[j] !=NULL;j++){
            if(strcmp(args[j],">") == 0){
                output_file = args[j+1];
                args[j] = NULL;
                break;
            }
        }
        pid_t rc = fork();
        if(rc == 0){
            if(output_file != NULL){
                int fd = open(output_file,O_WRONLY | O_CREAT | O_TRUNC,0644);
                dup2(fd,STDOUT_FILENO);
                close(fd);
            }
            execvp(args[0],args);
            exit(1);
        }
        else{
            wait(NULL);
        }
    }
    return 0;
}